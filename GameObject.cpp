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

#include "GameObject.h"

GameObject::GameObject(Context *context) :
	LogicComponent(context)
{
	SetUpdateEventMask(USE_FIXEDUPDATE);

}

void GameObject::RegisterObject(Context* context)
{
	context->RegisterFactory<GameObject>();
}

void GameObject::Start()
{

}

void GameObject::FixedUpdate(float timeStep)
{
	//Tell if the object should be destoryed
	if (hp <= 0) this->Destoryed();

}

void GameObject::Damaged(float damage)
{
	hp -= damage;
	if (hp > maxHp) hp = maxHp;
	if (hp < 0)hp = 0;
}

void GameObject::Destoryed()
{

}