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

#include"HeatSource.h"
#include"Effect.h"
#include"Effect_Flare.h"
#include"Toolkit.h"


Effect_Flare::Effect_Flare(Context *context) :
	Effect(context)
{
	duration_ = 2.0f;
	cal_duration_ = 0;
}

void Effect_Flare::RegisterObject(Context *context)
{
	context->RegisterFactory<Effect_Flare>();
}

void Effect_Flare::Start()
{
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	node = GetNode();
	//SharedPtr<Node> FlareNode(node->CreateChild("Flare"));
	FlareNode = node->CreateChild("Flare");
	ParticleEffect2D* particleEffect = cache->GetResource<ParticleEffect2D>("Urho2D/sun.pex");
	if (!particleEffect) return;
	ParticleEmitter2D* particleEmitter = FlareNode->CreateComponent<ParticleEmitter2D>();
	particleEmitter->SetEffect(particleEffect);
	// Random particles cnt
	particleEmitter->SetMaxParticles((int)Random(100, 300));

	// Reduce the attraction of the heatsource of the fighter
	HeatSource* fightersource_ = node->GetComponent<HeatSource>();
	fightersource_->SetAttraction(fightersource_->GetAttraction()*0.2f);	
	
}

void Effect_Flare::Update(float timeStep)
{
	cal_duration_ += timeStep;
	if (cal_duration_ > duration_)
		Stop();
}

void Effect_Flare::FixedUpdate(float timeStep)
{

}

void Effect_Flare::Stop()
{
	// Resume the attraction of the heatsource of the fighter
	HeatSource* fightersource_ = node->GetComponent<HeatSource>();
	fightersource_->SetAttraction(fightersource_->GetAttraction()*5.0f);
	// Stop Flareing (animation)
	FlareNode->Remove();
	// Remove the component
	Remove();
}