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

#include <Urho3D/Urho2D/Sprite2D.h>
#include <Urho3D/Urho2D/AnimatedSprite2D.h>
#include <Urho3D/Urho2D/AnimationSet2D.h>

#include "Box.h"
#include "BUFF.h"
#include "HeatSource.h"

Box::Box(Context* context) : GameObject(context)
{
	/// Set origin status
	SetMaxHp(100.f);
	SetHp(GetMaxHp());
	SetCollisionSize(Vector2(0.32f, 0.32f));
	SetInvincible(false);
}

void Box::RegisterObject(Context* context)
{
	context->RegisterFactory<Box>();
}

void Box::Start()
{
	Node* node = GetNode();

	/// Set Sprite
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	Sprite2D* sprite = cache->GetResource<Sprite2D>("Urho2D/Box.png");

	/// Create box
	StaticSprite2D* staticsprite = node->CreateComponent<StaticSprite2D>();
	staticsprite->SetBlendMode(BLEND_ALPHA);
	staticsprite->SetColor(Color(Random(1.0f), Random(1.0f), Random(1.0f)));
	staticsprite->SetSprite(sprite);

	/// Add rigidbody
	rigibody2d_ = node->CreateComponent<RigidBody2D>();
	rigibody2d_->SetBodyType(BT_DYNAMIC);

	/// Add collisionbox
	collisionbox2d_ = node->CreateComponent<CollisionBox2D>();
	collisionbox2d_->SetSize(GetCollisionSize());
	/// Set the collisionbox to a trigger
	collisionbox2d_->SetTrigger(true);

	//4test
	HeatSource* heatSource_ = node->CreateComponent<HeatSource>();
	heatSource_->SetAttraction(3.0f);
	heatSource_->SetOwner(SharedPtr<Node>(node));

	/// Subscribe Events
	//SubscribeToEvent(node, E_NODEBEGINCONTACT2D, URHO3D_HANDLER(Box, HandleHit));
}

void Box::Damaged(float damage)
{
	float newHP = GetHp() - damage;
	if (newHP > GetMaxHp()) SetHp(GetMaxHp());
	else if (newHP < 0) SetHp(0);
	else SetHp(newHP);
}

void Box::Destoryed()
{
	Node* node = GetNode();
	node->Remove();
}

void Box::FixedUpdate(float timeStep)
{
	if (GetHp() <= 0) Destoryed();
}

/// never used
void Box::HandleHit(StringHash eventType, VariantMap& eventData)
{
	using namespace NodeBeginContact2D;
	Node* otherNode = static_cast<Node*>(eventData[P_OTHERNODE].GetPtr());
	RigidBody2D* otherBody = otherBody->GetComponent<RigidBody2D>();
	if (!otherBody) return;
	if (!otherBody->IsBullet()) return;

}
