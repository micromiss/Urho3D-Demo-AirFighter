#include <Urho3D/Core/Context.h>
#include <Urho3D/Graphics/AnimationController.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/IO/MemoryBuffer.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Urho2D/Sprite2D.h>
#include <Urho3D/Urho2D/CollisionBox2D.h>
#include <Urho3D/Urho2D/PhysicsWorld2D.h>
#include <Urho3D/Urho2D/PhysicsEvents2D.h>
#include <Urho3D/Urho2D/RigidBody2D.h>
#include <Urho3D/Network/Network.h>
#include <Urho3D/Network/NetworkEvents.h>
#include <Urho3D/Core/Timer.h>

#include <Urho3D/Urho2D/Sprite2D.h>
#include <Urho3D/Urho2D/AnimatedSprite2D.h>
#include <Urho3D/Urho2D/AnimationSet2D.h>

#include "ControlsList.h"
#include "Fighter.h"
#include "Skill_Missile.h"
#include "Toolkit.h"

Skill_Missile::Skill_Missile(Context* context) : Skill(context)
{
	context_ = context;
	SetCooldown(5.0f);
	SetInitialVelocity(2.0f);
}

void Skill_Missile::RegisterObject(Context* context)
{
	context->RegisterFactory<Skill_Missile>();
}

void Skill_Missile::Start()
{
	// Initiate the timer
	cooldownTimer_ = 0;
	// Fighter node
	SharedPtr<Node>node(GetNode());
	SetOwner(node);
}

void Skill_Missile::Update(float timeStep)
{
	
}

void Skill_Missile::FixedUpdate(float timeStep)
{
	/// Clients should not update the component on its own
	Network* network = GetSubsystem<Network>();
	if (!network->IsServerRunning()) {
		return;
	}

	// Fighter node
	SharedPtr<Node>node(GetNode());
	// Monitor whether the trigger key is down
	Controls controls = node->GetComponent<Fighter>()->GetControls();
	// If the key to the skill is not set, then return.
	if (!GetTriggerKey()) return;
	// Whether the skill is in cooldown time
	if (cooldownTimer_ > 0) {
		cooldownTimer_ -= timeStep;
		return;
	}
	// Whether the key to the skill is triggered
	if (!controls.IsDown(GetTriggerKey())) return;
	// Trigger the skill
	Scene* scene = GetScene();
	Node* missile0 = scene->CreateChild("missile", REPLICATED);

	//Missile* missile = new Missile(context_, node);
	//missile0->AddComponent(missile, 0, REPLICATED);
	missile0->CreateComponent<Missile>(LOCAL);
	missile0->GetComponent<Missile>()->SetProducer(node);
	missile0->GetComponent<Missile>()->SetProducerid(node->GetID());

	// Set the position and rotation of the missile
	Vector3 towards = node->GetComponent<Fighter>()->GetTowards();
	missile0->SetWorldPosition(node->GetPosition() + towards.Normalized()*0.2f);
	missile0->SetWorldRotation(Quaternion(Vector3::UP, towards));
	// Initial velocity of the missile
	missile0->GetComponent<RigidBody2D>()->SetLinearVelocity(Vector2(towards.x_, towards.y_).Normalized() * GetInitialVelocity());	
	// Reset the cooldowntimer
	cooldownTimer_ = GetCooldown();
}