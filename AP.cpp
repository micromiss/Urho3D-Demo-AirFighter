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

#include "AP.h"
#include "GameObject.h"
#include "Box.h"

#include "Toolkit.h"

AP::AP(Context* context) : Bullet(context)
{
	SetUpdateEventMask(USE_FIXEDUPDATE);

	/// Set some parameter
	SetCollisionSize(Vector2(0.005f, 0.01f));
	SetMass(0.0001f);
	SetDamage(3.0f);
}

void AP::RegisterObject(Context* context)
{
	context->RegisterFactory<AP>();
}

void AP::Start()
{
	/// Scene node
	Node* node = GetNode();

	/// Set sprite
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	Sprite2D* sprite = cache->GetResource<Sprite2D>("Urho2D/bullet_1.png");
	StaticSprite2D* staticsprite = node->CreateComponent<StaticSprite2D>();
	staticsprite->SetSprite(sprite);
	staticsprite->SetBlendMode(BLEND_ALPHA);
	//staticsprite->SetColor(Color(Random(1.0f), Random(1.0f), Random(1.0f)));

	/// Set rigidbody
	RigidBody2D* rigidbody2d = node->CreateComponent<RigidBody2D>();
	rigidbody2d->SetBodyType(BT_DYNAMIC);
	rigidbody2d->SetMass(GetMass());
	rigidbody2d->SetBullet(true);
	CollisionBox2D* collisionbox2D = node->CreateComponent<CollisionBox2D>();
	collisionbox2D->SetSize(GetCollisionSize());
	/// Set bullet to a trigger
	collisionbox2D->SetTrigger(true);

	/// Subscribe collision event
	SubscribeToEvent(node, E_NODEBEGINCONTACT2D, URHO3D_HANDLER(AP, HandleContactBegin));
}

void AP::FixedUpdate(float timeStep)
{

}

void AP::End()
{
	/// The node of the component
	Node* node = GetNode();
	/// Remove the node frome the scene
	node->Remove();
}

void AP::HandleContactBegin(StringHash eventType, VariantMap& eventData)
{
	using namespace NodeBeginContact2D;

	Node* othernode = static_cast<Node*>(eventData[P_OTHERNODE].GetPtr());
	// Notice that we use "GetDerivedComponent<>()" here instead of "GetComponent<>()"
	GameObject* otherobject = othernode->GetDerivedComponent<GameObject>();

	/// Avoid the bullets' collision with bullets and the user's fighter
	//4test
	if (othernode->GetDerivedComponent<Bullet>()) return;
	if (othernode == GetProducer()) return;

	/// If the object which has been contacted is not a GameObject
	if (!otherobject) {
		this->End();
		/// Actually, it will not be executed,
		return;
	}
	/// If it's a GameObject, Damage the target
	else {
		Toolkit::Print(othernode->GetName());
		otherobject->Damaged(GetDamage());
		this->End();
	}

}