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
#include "Skill.h"
#include "Effect_Flare.h"
#include "Skill_Flare.h"
#include "Toolkit.h"

Skill_Flare::Skill_Flare(Context* context) : Skill(context)
{	
	SetDuration(2.0f);
	SetCooldown(7.0f);
}

void Skill_Flare::RegisterObject(Context* context)
{
	context->RegisterFactory<Skill_Flare>();
}

void Skill_Flare::Start()
{
	// Initiate the timer
	cooldownTimer_ = 0;
	// Fighter node
	SharedPtr<Node>node(GetNode());
	SetOwner(node);
}

void Skill_Flare::Update(float timeStep)
{
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
	node->CreateComponent<Effect_Flare>();
	// Reset the cooldowntimer
	cooldownTimer_ = GetCooldown();
}

void Skill_Flare::FixedUpdate(float timeStep)
{
	
}