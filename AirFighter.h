#include "Sample.h"

#pragma once
namespace Urho3D
{
	class Node;
	class Scene;
	class Button;
	class LineEdit;
	class Text;
}

/// Urho2D sprite example.
/// This sample demonstrates:
///     - Creating a 2D scene with sprite
///     - Displaying the scene using the Renderer subsystem
///     - Handling keyboard to move and zoom 2D camera
class AirFighter : public Sample
{
	URHO3D_OBJECT(AirFighter, Sample);

public:
	/// Construct.
	AirFighter(Context* context);

	/// Setup after engine initialization and before running the main loop.
	virtual void Start();

protected:
	/// Return XML patch instructions for screen joystick layout for a specific sample app, if any.
	virtual String GetScreenJoystickPatchString() const {
		return
			"<patch>"
			"    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/attribute[@name='Is Visible']\" />"
			"    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Zoom In</replace>"
			"    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button0']]\">"
			"        <element type=\"Text\">"
			"            <attribute name=\"Name\" value=\"KeyBinding\" />"
			"            <attribute name=\"Text\" value=\"PAGEUP\" />"
			"        </element>"
			"    </add>"
			"    <remove sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/attribute[@name='Is Visible']\" />"
			"    <replace sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]/element[./attribute[@name='Name' and @value='Label']]/attribute[@name='Text']/@value\">Zoom Out</replace>"
			"    <add sel=\"/element/element[./attribute[@name='Name' and @value='Button1']]\">"
			"        <element type=\"Text\">"
			"            <attribute name=\"Name\" value=\"KeyBinding\" />"
			"            <attribute name=\"Text\" value=\"PAGEDOWN\" />"
			"        </element>"
			"    </add>"
			"</patch>";
	}

private:

	/// Start singleplayer game
	void StartSingleplayerGame();
	/// Start multiplayer game
	void StartMultiplayerGame();
	/// Construct the empty scene (for connection parameter)
	void CreateEmptyScene(Context* context);
	/// Initiate the game map
	void InitiateGameMap(Scene* scene);
	/// Subscribe to application-wide logic update events.
	void SubscribeToEvents();
	/// Handle the logic update event.
	void HandleUpdate(StringHash eventType, VariantMap& eventData);
	/// Handle the collisiton event
	//void HandleCollision(StringHash eventType, VariantMap& eventData);

	/// Create obstacle(Box)
	void CreateBox(Vector3 position);

	/// Acceleration
	float acc = 3.0f;
	/// Move speed
	float speed = 0.0f;
	/// Turning velocity
	float turnV = 6.0f;
	/// The distance between 2 sprites
	float distance = 0.3f;
	/// Move dir
	Vector3 dir = Vector3(0.0f, 1.0f, 0.0f);

	/// The time boom lasts
	int BoomLast = 50;
	// cnt for boom lasts
	int cnt4boom = 0;

	/// Multiplayer support
	bool runServer = false;
	bool runClient = false;


	///UI
private:
	/// Create UI
	void CreateUI();
	// Button Contaniner
	SharedPtr<UIElement> buttonContainer_;
	// Buttons
	SharedPtr<Button> singleplayerButton_;
	SharedPtr<Button> connectButton_;
	SharedPtr<Button> disconnectButton_;
	SharedPtr<Button> startServerButton_;
	// LineEdit
	SharedPtr<LineEdit> IdentityEdit_;
	// Create a button to the button container.
	Button* CreateButton(SharedPtr<UIElement> buttoncontainer, const String& text, int width);
	// Create a flag to show text(3d)
	SharedPtr<Node>CreateFlag(Scene* scene, const String& text, float x, float y);
	// Create a flag as one's child
	SharedPtr<Node>CreateFlag(SharedPtr<Node> parent, const String& text, float x, float y);

	/// Character(Fighter) Info Container
	SharedPtr<UIElement> characterInfoContainer_;
	// Hp display
	SharedPtr<Text> hpText_;
	SharedPtr<Sprite> hpSprite_;
	// Create player UI
	void CreatePlayerUI(String username);
	// Update player UI
	void UpdatePlayerUI(String username);

	/// Handle events
	/// Handle pressing the singleplayer button
	void HandleSinglePlayerButton(StringHash eventType, VariantMap& eventData);
	/// Handle pressing the connect button.
	void HandleConnectButton(StringHash eventType, VariantMap& eventData);
	/// Handle pressing the disconnect button.
	void HandleDisconnectButton(StringHash eventType, VariantMap& eventData);
	/// Handle pressing the start server button.
	void HandleStartServerButton(StringHash eventType, VariantMap& eventData);
	/// Handle the event when get a new comer's identity
	void HandleClientIdentity(StringHash eventType, VariantMap& eventData);

	/// Handle remote events
	/// Handle the remote event when player is spawned by the server
	void HandleRePlayerSpawned(StringHash eventType, VariantMap& eventData);

	/// Singleplayer game
private:
	///If we are playing a singleplayer game
	bool singleplayerFlag_;

	/// Multiplayer game
private:
	//Vector<Node*> fighters_;
	/// Map the username of the client to its own fighter node.
	VariantMap fightersmap_;
	/// Controls information(Only for clients)
	Controls controls_;
	/// Client Identity(Only for clients)
	String username_;

	///About Multiplayer game
private:
	/// Spawn a fighter and a camera for singleplayer game
	SharedPtr<Node>SpawnPlayer();
	/// Spawn a fighter and a camera which follows the fighter to a new player
	Node* SpawnPlayer(Connection* connection);
	/// Initiate viewport (Create a camera)
	void InitiateViewport(Context* context, Scene* scene, Node* parent);
	/// Initiate viewport (Use a camera already existed)
	void InitiateViewport(Context* context, Scene* scene, Camera* camera);
	/// Update the controls information according to the input (only for clients)
	void UpdateControls(Controls& controls);

	///Network Events
private:
	/// Handle connection status change
	// Handle the connection to server (on client)
	void HandleServerConnected(StringHash eventType, VariantMap& eventData);
	// Handle the connection to clients (on server)
	//void HandleConnectiontoClients(StringHash eventType, VariantMap& eventData);
	// Handle the disconnection to server (on client)
	void HandleServerDisconnected(StringHash eventType, VariantMap& eventData);
	// Handle the disconnection to clients (on server)
	void HandleClientDisconnected(StringHash eventType, VariantMap& eventData);

	// Handle the processing when client has sent its identity(on server)
	void HandleGetClientIdentity(StringHash eventType, VariantMap& eventData);

	// Handle the camera and viewport creation when playerspawned (on client)
	void HandlePlayerSpawned(StringHash eventType, VariantMap& eventData);


};

