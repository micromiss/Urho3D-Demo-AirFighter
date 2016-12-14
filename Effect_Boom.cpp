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

#include"HeatSource.h"
#include"Effect.h"
#include"Effect_Boom.h"
#include"Toolkit.h"

// PAY ATTENTION that this effect will destory the node in the scene!!!
Effect_Boom::Effect_Boom(Context *context) :
	Effect(context)
{
	duration_ = 1.5f;
	cal_duration_ = 0;
}

void Effect_Boom::RegisterObject(Context *context)
{
	context->RegisterFactory<Effect_Boom>();
}

void Effect_Boom::Start()
{
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	node = GetNode();
	ParticleEffect2D* particleEffect = cache->GetResource<ParticleEffect2D>("Urho2D/sun.pex");
	if (!particleEffect) return;
	ParticleEmitter2D* particleEmitter = node->CreateComponent<ParticleEmitter2D>();
	particleEmitter->SetEffect(particleEffect);
	particleEmitter->SetMaxParticles((int)Random(0, 5));
}

void Effect_Boom::Update(float timeStep)
{
	/// Clients should not update the component on its own
	Network* network = GetSubsystem<Network>();
	if (!network->IsServerRunning()) {
		return;
	}

	cal_duration_ += timeStep;
	if (cal_duration_ > duration_)
		Stop();
}

void Effect_Boom::FixedUpdate(float timeStep)
{

}

void Effect_Boom::Stop()
{
	// Stop Flareing (animation)
	node->Remove();
	// Remove the component
	Remove();
}