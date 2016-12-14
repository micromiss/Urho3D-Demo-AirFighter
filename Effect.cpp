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
#include <Urho3D/Urho2D/ParticleEffect2D.h>
#include <Urho3D/Urho2D/ParticleEmitter2D.h>

#include <Urho3D/Network/Network.h>
#include <Urho3D/Network/NetworkEvents.h>

#include"Effect.h"
#include"Toolkit.h"

Effect::Effect(Context *context) :
	LogicComponent(context)
{

}

void Effect::RegisterObject(Context *context)
{
	context->RegisterFactory<Effect>();
}

void Effect::Start()
{

}

void Effect::Update(float timeStep)
{

}

void Effect::FixedUpdate(float timeStep)
{

}

