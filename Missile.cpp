#include <Urho3D/Core/Context.h>
#include <Urho3D/Graphics/AnimationController.h>
#include <Urho3D/Graphics/Graphics.h>
#include <Urho3D/Resource/ResourceCache.h>
#include <Urho3D/Physics/PhysicsEvents.h>
#include <Urho3D/Physics/PhysicsWorld.h>
#include <Urho3D/Physics/RigidBody.h>
#include <Urho3D/Scene/Scene.h>
#include <Urho3D/Input/Input.h>
#include <Urho3D/Scene/SceneEvents.h>
#include <Urho3D/IO/Log.h>
#include <Urho3D/Urho2D/Sprite2D.h>
#include <Urho3D/Urho2D/CollisionBox2D.h>
#include <Urho3D/Urho2D/CollisionCircle2D.h>
#include <Urho3D/Urho2D/PhysicsWorld2D.h>
#include <Urho3D/Urho2D/PhysicsEvents2D.h>
#include <Urho3D/Urho2D/RigidBody2D.h>
#include <Urho3D/Container/Vector.h>

#include <Urho3D/Network/Network.h>
#include <Urho3D/Network/NetworkEvents.h>

#include <Urho3D/Urho2D/Sprite2D.h>
#include <Urho3D/Urho2D/AnimatedSprite2D.h>
#include <Urho3D/Urho2D/AnimationSet2D.h>

#include "GameObject.h"
#include "Missile.h"
#include "BUFFList.h"
#include "Toolkit.h"

#include "HeatSource.h"

Missile::Missile(Context* context) : GameObject(context)
{
	SetThrust(2.0f);
	SetDetectionRange(3.0f);
	SetBoomRange(0.3f);
	SetDamage(20.0f);
	duration_ = 0.0f;
}

Missile::Missile(Context* context, SharedPtr<Node>producer) : GameObject(context)
{
	SetProducer(producer);
	SetThrust(2.0f);
	SetDetectionRange(3.0f);
	SetBoomRange(0.3f);
	SetDamage(20.0f);
	duration_ = 0.0f;
}

void Missile::RegisterObject(Context* context)
{
	context->RegisterFactory<Missile>();
}

void Missile::Start()
{
	// Scene node
	node_ = GetNode();
	/// Set sprite
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	Sprite2D* sprite = cache->GetResource<Sprite2D>("Urho2D/missile.png");
	StaticSprite2D* staticsprite = node_->CreateComponent<StaticSprite2D>();
	staticsprite->SetSprite(sprite);
	staticsprite->SetBlendMode(BLEND_ALPHA);
	// Rigidbody
	RigidBody2D* rigidbody2d = node_->CreateComponent<RigidBody2D>();
	rigidbody2d->SetBodyType(BT_DYNAMIC);
	// The detection circle of the missile
	CollisionCircle2D* detectionCircle = node_->CreateComponent<CollisionCircle2D>();
	detectionCircle->SetRadius(GetDetectionRange());
	detectionCircle->SetTrigger(true);
	// Subscribe the collision event
	SubscribeToEvent(node_, E_NODEBEGINCONTACT2D, URHO3D_HANDLER(Missile, HandleContactBegin));
	SubscribeToEvent(node_, E_NODEENDCONTACT2D, URHO3D_HANDLER(Missile, HandleContactEnd));
}

void Missile::Update(float timeStep)
{

}

void Missile::FixedUpdate(float timeStep)
{
	/// Update the duration
	duration_ += timeStep;
	// Clear the missiles 
	if (duration_ > 10.0f) node_->Remove();

	RigidBody2D* rigidbody2d = node_->GetComponent<RigidBody2D>();
	// Set Rotation
	Vector2 velocity = rigidbody2d->GetLinearVelocity();
	node_->SetWorldRotation(Quaternion(Vector3::UP, velocity));
	// Apply thrust to the missile
	rigidbody2d->ApplyForceToCenter(velocity.Normalized()*thrust,true);
	// Tracking targets
	if (targetnodes_.Empty()) return;
	for (int i = 0; i < targetnodes_.Size(); i++)
	{
		//Toolkit::Print(targetnodes_[i]->GetName());
		HeatSource* heatsource = targetnodes_[i]->GetComponent<HeatSource>();
		float attraction = heatsource->GetAttraction();
		// Calculate the force
		Vector2 force = targetnodes_[i]->GetPosition2D() - node_->GetPosition2D();
		force.Normalize();
		// Track it!
		rigidbody2d->ApplyForce(force*attraction, Vector2(0.0f, 0.0f), true);
		// If the target is in the boomrange,then boom!
		float distance = (node_->GetPosition2D() - targetnodes_[i]->GetPosition2D()).Length();		
		if (distance < GetBoomRange()) {
			GameObject* targetobject = targetnodes_[i]->GetDerivedComponent<GameObject>();
			targetobject->Damaged(GetDamage());
			UnsubscribeFromAllEvents();
			node_->Remove();
		}
		
	}

}

void Missile::HandleContactBegin(StringHash eventType, VariantMap& eventData)
{	
	/// Clients should not update the component on its own
	using namespace NodeBeginContact2D;	
	SharedPtr<Node>othernode(static_cast<Node*>(eventData[P_OTHERNODE].GetPtr()));
	// Do not track the launcher and the launcher's flare
	//if (othernode == GetProducer()) return;
	HeatSource* otherSource = othernode->GetComponent<HeatSource>();	
	//If the other node is not a heatsource then return
	if (!otherSource)return;
	//Toolkit::Print("Source:" + otherSource->GetNode()->GetName()+" Fighter:"+GetProducer()->GetName());
	//Toolkit::Print("target:" + String(otherSource->GetOwner()->GetID()));
	if (otherSource->GetOwner() == GetProducer()) return;	
	// If othernode is a heatsource then push it into the targetqueue;
	targetnodes_.Push(othernode);	
	//Toolkit::Print("got you!");
}

void Missile::HandleContactEnd(StringHash eventType, VariantMap& eventData)
{
	/// Clients should not update the component on its own
	Network* network = GetSubsystem<Network>();
	if (!network->IsServerRunning()) {
		return;
	}

	using namespace Urho3D;
	// If the target is out of tracking range, then erase it.
	using namespace NodeEndContact2D;
	SharedPtr<Node>othernode(static_cast<Node*>(eventData[P_OTHERNODE].GetPtr()));
	HeatSource* heatsource = othernode->GetComponent<HeatSource>();
	if (!heatsource) return;
	//4test Find it in the queue and erase it
	if(targetnodes_.Contains(othernode))	targetnodes_.Erase(	targetnodes_.Find(othernode));
	//Toolkit::Print("lost you!");
}

