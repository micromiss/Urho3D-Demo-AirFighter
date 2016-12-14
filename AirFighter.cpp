#include <Urho3D/Core/CoreEvents.h>
#include <Urho3D/Engine/Engine.h>
#include <Urho3D/Graphics/Camera.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Graphics/Octree.h>
#include <Urho3D/Graphics/Renderer.h>
#include <Urho3D/Graphics/Zone.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Resource/Image.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/UI/Font.h>
#include <Urho3D/UI/Text.h>
#include <Urho3D/UI/Text3D.h>
#include <Urho3D/UI/Button.h>
#include <Urho3D/UI/UIEvents.h>
#include <Urho3D/UI/LineEdit.h>
#include <Urho3D/Urho2D/AnimatedSprite2D.h>
#include <Urho3D/Urho2D/AnimationSet2D.h>
#include <Urho3D/Urho2D/Sprite2D.h>
#include <Urho3D/Urho2D/CollisionBox2D.h>
#include <Urho3D/Urho2D/PhysicsWorld2D.h>
#include <Urho3D/Urho2D/PhysicsEvents2D.h>
#include <Urho3D/Urho2D/RigidBody2D.h>
#include <Urho3D/Urho2D/ConstraintDistance2D.h>
#include <Urho3D/Urho2D/ConstraintFriction2D.h>
#include <Urho3D/Urho2D/ConstraintWeld2D.h>
#include <Urho3D/Urho2D/ParticleEffect2D.h>
#include <Urho3D/Urho2D/ParticleEmitter2D.h>
#include <Urho3D/Network/Network.h>
#include <Urho3D/Network/NetworkEvents.h>
#include <Urho3D/DebugNew.h>

#include "AirFighter.h"

#include"GameObject.h"
#include"Box.h"
#include"Fighter.h"
#include"Missile.h"

#include"Bullet.h"
#include"AP.h"

#include"Effect.h"
#include"Effect_Flare.h"
#include"Effect_Blink.h"
#include"Effect_Boom.h"

#include"Skill.h"
#include"Skill_Missile.h"
#include"Skill_Flare.h"
#include"Skill_Blink.h"

#include"ControlsList.h"
#include"RemoteEvents.h"
#include"Toolkit.h"

#include"BUFF.h"
#include"HeatSource.h"


using namespace Urho3D;

// UDP port we will use
const unsigned short GAME_SERVER_PORT = 2345;

URHO3D_DEFINE_APPLICATION_MAIN(AirFighter)

AirFighter::AirFighter(Context* context) :
	Sample(context)
{
	// Register factory and attributes for the Character component so it can be created via CreateComponent, and loaded / saved
	GameObject::RegisterObject(context);
	Box::RegisterObject(context);
	Fighter::RegisterObject(context);
	Missile::RegisterObject(context);

	Bullet::RegisterObject(context);
	AP::RegisterObject(context);

	Effect::RegisterObject(context);
	Effect_Flare::RegisterObject(context);
	Effect_Blink::RegisterObject(context);	
	Effect_Boom::RegisterObject(context);

	Skill::RegisterObject(context);
	Skill_Missile::RegisterObject(context);
	Skill_Flare::RegisterObject(context);
	Skill_Blink::RegisterObject(context);

	BUFF::RegisterObject(context);
	HeatSource::RegisterObject(context);

}

void AirFighter::Start()
{
	// Execute base class startup
	Sample::Start();

	// Create UI
	CreateUI();

	// Create scene(empty) for the connecting parameter
	CreateEmptyScene(context_);

	// Set the mouse mode to use in the sample
	Sample::InitMouseMode(MM_FREE);
}

void AirFighter::CreateUI()
{
	// We need the full rendering window
	SetLogoVisible(false);

	Graphics* graphics = GetSubsystem<Graphics>();
	UIElement* root = GetSubsystem<UI>()->GetRoot();
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	XMLFile* uiStyle = cache->GetResource<XMLFile>("UI/DefaultStyle.xml");
	// Set style to the UI root so that elements will inherit it
	root->SetDefaultStyle(uiStyle);

	/// Set Button Container
	buttonContainer_ = root->CreateChild<UIElement>();
	buttonContainer_->SetFixedSize(graphics->GetWidth(), 20);
	buttonContainer_->SetPosition(0, graphics->GetHeight() - 20);
	buttonContainer_->SetLayoutMode(LM_HORIZONTAL);
	// Create buttons
	singleplayerButton_ = CreateButton(buttonContainer_, "SinglePlayer", 150);
	connectButton_ = CreateButton(buttonContainer_, "Connect", 90);
	disconnectButton_ = CreateButton(buttonContainer_, "Disconnect", 100);
	startServerButton_ = CreateButton(buttonContainer_, "Start Server", 110);
	// Create LineEdit
	IdentityEdit_ = buttonContainer_->CreateChild<LineEdit>();
	IdentityEdit_->SetStyleAuto();
	// Subscribe Buttons Events
	SubscribeToEvent(singleplayerButton_, E_RELEASED, URHO3D_HANDLER(AirFighter, HandleSinglePlayerButton));
	SubscribeToEvent(connectButton_, E_RELEASED, URHO3D_HANDLER(AirFighter, HandleConnectButton));
	SubscribeToEvent(disconnectButton_, E_RELEASED, URHO3D_HANDLER(AirFighter, HandleDisconnectButton));
	SubscribeToEvent(startServerButton_, E_RELEASED, URHO3D_HANDLER(AirFighter, HandleStartServerButton));

}

void AirFighter::CreatePlayerUI(String username)
{
	Graphics* graphics = GetSubsystem<Graphics>();
	UIElement* root = GetSubsystem<UI>()->GetRoot();
	ResourceCache* cache = GetSubsystem<ResourceCache>();

	/// Set character info ui
	characterInfoContainer_ = root->CreateChild<UIElement>();
	characterInfoContainer_->SetFixedSize(graphics->GetWidth(), 20);
	characterInfoContainer_->SetPosition(10, 10);
	characterInfoContainer_->SetLayoutMode(LM_HORIZONTAL);
	// Hp display
	Font* font = cache->GetResource<Font>("Fonts/Anonymous Pro.ttf");
	hpText_ = characterInfoContainer_->CreateChild<Text>();
	hpText_->SetFont(font, 12);
	hpText_->SetAlignment(HA_LEFT, VA_TOP);
	hpText_->SetText("HP");

	Texture2D* texture = new Texture2D(context_);
	texture->SetFilterMode(TextureFilterMode::FILTER_TRILINEAR);
	texture->SetNumLevels(1);
	texture->SetSize(10, 1, Graphics::GetRGBAFormat(), TEXTURE_STATIC);
	texture->SetData(cache->GetResource<Image>("Urho2D/hp.png"));

	hpSprite_ = characterInfoContainer_->CreateChild<Sprite>();
	hpSprite_->SetTexture(texture);
	hpSprite_->SetHotSpot(0.0f, 0.0f);
	hpSprite_->SetAlignment(HA_LEFT, VA_TOP);
	hpSprite_->SetPosition(Vector2(30.0f, 0.0f));

}

void AirFighter::UpdatePlayerUI(String username)
{
	Node* playernode = scene_->GetChild(username);
	if (!playernode) return;
	Fighter* fighter = playernode->GetComponent<Fighter>();
	if (!fighter) return;
	float hpscale = fighter->GetHp() / fighter->GetMaxHp();
	if (!hpSprite_) return;
	hpSprite_->SetScale(Vector2(hpscale, 1.0f));

}

// Create a flag to show text
SharedPtr<Node>AirFighter::CreateFlag(Scene* scene, const String& text, float x, float y) // Used to create Tex3D flags
{
	SharedPtr<Node>flagNode(scene->CreateChild("Flag"));
	flagNode->SetPosition(Vector3(x, y, 0.0f));
	Text3D* flag3D = flagNode->CreateComponent<Text3D>();
	flag3D->SetText(text);
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	flag3D->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);
	return flagNode;
}
// Create a flag as one's child
SharedPtr<Node>AirFighter::CreateFlag(SharedPtr<Node> parent, const String& text, float x, float y)
{
	SharedPtr<Node>flagNode(parent->CreateChild("Flag"));
	flagNode->SetPosition(Vector3(x, y, 0.0f));
	Text3D* flag3D = flagNode->CreateComponent<Text3D>();
	flag3D->SetText(text);
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	flag3D->SetFont(cache->GetResource<Font>("Fonts/Anonymous Pro.ttf"), 15);
	return flagNode;
}

Button* AirFighter::CreateButton(SharedPtr<UIElement> buttoncontainer, const String &text, int width)
{
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	Font* font = cache->GetResource<Font>("Fonts/Anonymous Pro.ttf");

	Button* button = buttoncontainer->CreateChild<Button>();
	button->SetStyleAuto();
	button->SetFixedWidth(width);

	Text* buttonText = button->CreateChild<Text>();
	buttonText->SetFont(font, 12);
	buttonText->SetAlignment(HA_CENTER, VA_CENTER);
	buttonText->SetText(text);

	return button;
}

void AirFighter::CreateEmptyScene(Context* context)
{
	scene_ = new Scene(context);
	scene_->SetName("MainScene");
	scene_->CreateComponent<Octree>();
}

void AirFighter::InitiateGameMap(Scene* scene)
{
	// Make a non-gravity physics world
	PhysicsWorld2D* physicsworld2d = scene->CreateComponent<PhysicsWorld2D>();
	physicsworld2d->SetGravity(Vector2(0.0f, 0.0f));
	// Initiate Map
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	Sprite2D* sprite2d = cache->GetResource<Sprite2D>("Urho2D/background_fate.jpg");
	SharedPtr<Node> background(scene->CreateChild("background", REPLICATED));
	StaticSprite2D* staticsprite2d = background->CreateComponent<StaticSprite2D>();
	staticsprite2d->SetSprite(sprite2d);
	background->SetPosition(Vector3(0.0f, 0.0f, 10.0f));
	// Initiate partical emitter background
	SharedPtr<Node> particleBackgroundNode_(scene->CreateChild("particleBackground",REPLICATED));
	ParticleEffect2D* particleEffect = cache->GetResource<ParticleEffect2D>("Urho2D/background.pex");
	if (!particleEffect)
		return;
	particleBackgroundNode_ = scene->CreateChild("ParticleEmitter2D");
	ParticleEmitter2D* particleEmitter = particleBackgroundNode_->CreateComponent<ParticleEmitter2D>();
	particleEmitter->SetEffect(particleEffect);
	//(4test) Create some boxes for test
	Node* box0 = scene->CreateChild("box0", REPLICATED);
	box0->SetPosition(Vector3(0.0f, 3.0f, 0.0f));
	box0->CreateComponent<Box>(LOCAL);
}

void AirFighter::InitiateViewport(Context* context, Scene* scene, Node* parent)
{
	Graphics* graphics = GetSubsystem<Graphics>();
	cameraNode_ = parent->CreateChild("Camera");
	cameraNode_->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
	Camera* camera = cameraNode_->CreateComponent<Camera>();
	camera->SetOrthographic(true);
	// Camera height
	camera->SetOrthoSize((float)graphics->GetHeight() * PIXEL_SIZE * 1.0f);
	Renderer* renderer = GetSubsystem<Renderer>();
	// Set up a viewport to the Renderer subsystem so that the 3D scene can be seen
	SharedPtr<Viewport> viewport(new Viewport(context, scene, cameraNode_->GetComponent<Camera>()));
	renderer->SetViewport(0, viewport);
}

void AirFighter::InitiateViewport(Context* context, Scene* scene, Camera* camera)
{
	Renderer* renderer = GetSubsystem<Renderer>();
	SharedPtr<Viewport> viewport(new Viewport(context, scene, camera));
	renderer->SetViewport(0, viewport);
}

void AirFighter::StartSingleplayerGame()
{
	// Set the flag of singleplayer game to true
	singleplayerFlag_ = true;
	// Create game map
	InitiateGameMap(scene_);
	// Create the player and viewport
	SharedPtr<Node> fighterNode(SpawnPlayer());
	// Fighter component
	Fighter* fighter = fighterNode->GetComponent<Fighter>();
	if (!fighter) { Toolkit::Print("Fighter component not found!"); return; }
	// Create player UI
	CreatePlayerUI("migu");
	// Start whole logic
	SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(AirFighter, HandleUpdate));
}

void AirFighter::StartMultiplayerGame()
{
	// Set the flag of singleplayer game to false
	singleplayerFlag_ = false;
	Network* network = GetSubsystem<Network>();
	// If we are running a server
	if (network->IsServerRunning())
	{
		// Initiate game map for multiplayer game
		InitiateGameMap(scene_);
		//InitiateViewport(context_, scene_, scene_);
		// Spawn the player to server itself
		SpawnPlayer();
		// Create Player UI
		CreatePlayerUI("migu");
		// Subscribe for the newcomer recognition
		SubscribeToEvent(E_CLIENTIDENTITY, URHO3D_HANDLER(AirFighter, HandleClientIdentity));
		// Subscribe the update event for the whole logic
		SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(AirFighter, HandleUpdate));
		// Subscribe for the client disconnection
		SubscribeToEvent(E_CLIENTDISCONNECTED, URHO3D_HANDLER(AirFighter, HandleClientDisconnected));

		// Register the remote event 'playerspawned'
		network->RegisterRemoteEvent(RemoteEventes::RE_PLAYERSPAWNED);
	}
	// if we are running a client
	else if (network->GetServerConnection())
	{
		// Register the remote event 'playerspawned'
		network->RegisterRemoteEvent(RemoteEventes::RE_PLAYERSPAWNED);
		// Subscribe for the remote event 'playerspawned'
		SubscribeToEvent(RemoteEventes::RE_PLAYERSPAWNED, URHO3D_HANDLER(AirFighter, HandleRePlayerSpawned));
	}

}

// Update
void AirFighter::HandleUpdate(StringHash eventType, VariantMap& eventData)
{
	Network* network = GetSubsystem<Network>();
	// If we are running a server
	if (network->IsServerRunning()) {
		//Update the server's fighter
		SharedPtr<Node> fighternode = (SharedPtr<Node>)scene_->GetChild("migu");
		if (fighternode) {
			UpdateControls(controls_);
			UpdatePlayerUI("migu");
			Fighter* fighter = fighternode->GetComponent<Fighter>();
			fighter->SetControls(controls_);
		}
		// Get connections from the player
		Vector<SharedPtr<Connection>> allConnections = network->GetClientConnections();
		// Process each connection
		for (int i = 0; i < allConnections.Size(); i++) {
			SharedPtr<Connection> connection = allConnections[i];
			//4test
			//connection->SetScene(scene_);
			// Get controls from the client
			Controls playerControls = connection->GetControls();
			// Control the object which belongs to the player
			VariantMap userIdentity = connection->GetIdentity();
			String username = String(userIdentity["username"]);
			if (username.Empty()) { Toolkit::Print("Username not found!"); continue; }
			// Find the fighter object according to the userIdentity
			Node* fighter = scene_->GetChild(username);
			if (!fighter) { Toolkit::Print("Fighter not found!"); continue; }
			// Give the controls information to the fighter
			fighter->GetComponent<Fighter>()->SetControls(playerControls);

		}

	}
	// If we are running a client
	else if (network->GetServerConnection()) {
		// Get connection from the server
		Connection* connection = network->GetServerConnection();
		// Update the controls information according to the input
		UpdateControls(controls_);
		// Update player UI (It doesn't work and I don't know why)
		UpdatePlayerUI(username_);
		// Send the controls information to the server
		connection->SetControls(controls_);
	}
	// If we are playing singleplayer game
	else if (singleplayerFlag_ == true) {
		SharedPtr<Node> fighternode = (SharedPtr<Node>)scene_->GetChild("migu");
		if (fighternode) {
			UpdateControls(controls_);
			UpdatePlayerUI("migu");
			Fighter* fighter = fighternode->GetComponent<Fighter>();
			fighter->SetControls(controls_);
		}
	}
}

// Spawn a fighter , a camera and a viewport to singleplayer game and the server of a multiplayer game
SharedPtr<Node> AirFighter::SpawnPlayer()
{
	/// 1.Create a new fighter for the player
	SharedPtr<Node> fighter(scene_->CreateChild("migu"));
	fighter->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	fighter->CreateComponent<Fighter>();
	/// 1.5 Create the label of the fighter
	CreateFlag(fighter, "migu", -0.15f, 0.4f);	
	/// 2.Create a new camera	follows the fighter
	Graphics* graphics = GetSubsystem<Graphics>();
	String cameraname = "camera_migu";
	SharedPtr<Node>cameraNode(fighter->CreateChild(cameraname));
	cameraNode->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
	Camera* camera = cameraNode->CreateComponent<Camera>();
	camera->SetOrthographic(true);
	camera->SetOrthoSize((float)graphics->GetHeight() * PIXEL_SIZE * 1.0f);
	/// 3.Create the viewport
	InitiateViewport(context_, scene_, camera);
	/// 4.Returen the fighter node
	return fighter;
}

// Spawn a fighter and a camera to a new player
Node* AirFighter::SpawnPlayer(Connection* connection)
{
	/// 1.Get the username of ther newcomer
	VariantMap identity = connection->GetIdentity();
	String username = String(identity["username"]);
	/// 2.Create a new fighter for the client
	SharedPtr<Node>fighter(scene_->CreateChild(username, REPLICATED));
	fighter->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
	fighter->CreateComponent<Fighter>();
	/// 2.5 Create the label of the fighter
	CreateFlag(fighter, username, -0.15f, 0.4f);
	// Push the new comer into the map
	fightersmap_[username] = fighter;
	// Send remote event
	connection->SendRemoteEvent(RemoteEventes::RE_PLAYERSPAWNED, true);
	// Give the ownership to the client
	fighter->SetOwner(connection);
	/// 3.Create a new camera	follows the fighter
	Graphics* graphics = GetSubsystem<Graphics>();
	String cameraname = "camera_" + username;
	Node* cameraNode = fighter->CreateChild(cameraname, REPLICATED);
	//Node* cameraNode = scene_->CreateChild(cameraname, REPLICATED);
	cameraNode->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
	Camera* camera = cameraNode->CreateComponent<Camera>();
	camera->SetOrthographic(true);
	camera->SetOrthoSize((float)graphics->GetHeight() * PIXEL_SIZE * 1.0f);
	// Give the ownership to the client
	cameraNode->SetOwner(connection);
	/// 4.Returen the fighter node
	return fighter;
}

// Update the controls information according to the input(only for clients)
void AirFighter::UpdateControls(Controls& controls)
{
	// Get input information
	Input* input = GetSubsystem<Input>();
	// Clear the controls information
	controls.Reset();
	// update the controls information
	if (input->GetKeyDown(KEY_UP))  controls.Set(CTRL_UP, true);
	if (input->GetKeyDown(KEY_DOWN)) controls.Set(CTRL_DOWN, true);
	if (input->GetKeyDown(KEY_LEFT)) controls.Set(CTRL_LEFT, true);
	if (input->GetKeyDown(KEY_RIGHT)) controls.Set(CTRL_RIGHT, true);
	if (input->GetKeyDown(KEY_SPACE)) controls.Set(CTRL_SPACE, true);
	if (input->GetKeyDown(KEY_Q)) controls.Set(CTRL_Q, true);
	if (input->GetKeyDown(KEY_W)) controls.Set(CTRL_W, true);
	if (input->GetKeyDown(KEY_E)) controls.Set(CTRL_E, true);
	if (input->GetKeyDown(KEY_R)) controls.Set(CTRL_R, true);
}

//////////////////////////////////////////////////////////////
///Events Handles
// Buttons events handles
void AirFighter::HandleSinglePlayerButton(StringHash eventType, VariantMap& eventData)
{
	StartSingleplayerGame();
}

void AirFighter::HandleStartServerButton(StringHash eventType, VariantMap& eventData)
{
	Network* network = GetSubsystem<Network>();
	network->StartServer(GAME_SERVER_PORT);
	StartMultiplayerGame();
}

void AirFighter::HandleConnectButton(StringHash eventType, VariantMap& eventData)
{
	Network* network = GetSubsystem<Network>();

	/// Identity & IP address (format:  'username:ip' , e.g 'Alex:192.168.150.132')
	VariantMap identity;
	//String name_ip = IdentityEdit_->GetText();
	String name_ip = "Alex:192.168.150.132";
	/// Identity(username)
	identity["UserName"] = Toolkit::CutStringBeforeChar(name_ip, ':');
	username_ = Toolkit::CutStringBeforeChar(name_ip, ':');
	/// ip address
	String address = Toolkit::CutStringAfterChar(name_ip, ':');

	/// Connect
	network->Connect(address, GAME_SERVER_PORT, scene_, identity);
	/// Subscribe the ServerConnected Event
	SubscribeToEvent(E_SERVERCONNECTED, URHO3D_HANDLER(AirFighter, HandleServerConnected));
}

void AirFighter::HandleDisconnectButton(StringHash eventType, VariantMap& eventData)
{
	Network* network = GetSubsystem<Network>();
	// If we are running a server
	if (network->IsServerRunning()) {
		// Send a remote 	event to the clients.
		Vector<SharedPtr<Connection>> clientConnections = network->GetClientConnections();
		for (int i = 0; i < clientConnections.Size(); i++) {
			//...

		}
		// Stop server
		network->StopServer();
	}
	// If we are connected to a server

}

void AirFighter::HandleClientIdentity(StringHash eventType, VariantMap& eventData)
{
	using namespace ClientIdentity;
	// Get connection from the client
	Connection* connection = static_cast<Connection*>(eventData[P_CONNECTION].GetPtr());
	if (!connection) { Toolkit::Print("Lost connection request!"); return; }
	Toolkit::Print("Newcomer:" + String(connection->GetIdentity()["username"]));
	SpawnPlayer(connection);
	// Send scene to the client
	connection->SetScene(scene_);
}

void AirFighter::HandleClientDisconnected(StringHash eventType, VariantMap& eventData)
{
	using namespace ClientConnected;
	Connection* client = static_cast<Connection*>(eventData[P_CONNECTION].GetPtr());
	String username = String(client->GetIdentity()["username"]);
	if (username.Empty()) return;
	Node* fighter = scene_->GetChild(username);
	if (!fighter) return;
	fighter->Remove();

}

void AirFighter::HandleServerConnected(StringHash eventType, VariantMap& eventData)
{
	StartMultiplayerGame();
	// For safe
	UnsubscribeFromEvent(E_SERVERCONNECTED);
}

void AirFighter::HandleServerDisconnected(StringHash eventType, VariantMap& eventData)
{

}

void AirFighter::HandleRePlayerSpawned(StringHash eventType, VariantMap& eventData)
{
	// UnScribeRemoteEvents
	UnsubscribeFromEvent(RemoteEventes::RE_PLAYERSPAWNED);

	//4test
	Toolkit::Print("Get my player!");

	Network* network = GetSubsystem<Network>();
	Connection* connection = network->GetServerConnection();
	// Find my fighter
	Node* fighter = scene_->GetChild(username_);
	if (!fighter) {
		Toolkit::Print("Fighter not found!");
		return;
	}
	// Create player UI
	CreatePlayerUI(username_);
	// Set the camera and viewport
	InitiateViewport(context_, scene_, fighter->GetChild("camera_" + username_)->GetComponent<Camera>());
	//InitiateViewport(context_, scene_, scene_);
	// Subscribe the update event for the whole logic
	SubscribeToEvent(E_UPDATE, URHO3D_HANDLER(AirFighter, HandleUpdate));
}
