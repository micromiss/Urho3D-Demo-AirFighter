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
#include"Effect_Blink.h"
#include"Toolkit.h"


Effect_Blink::Effect_Blink(Context *context) :
	Effect(context)
{
	cal_duration_ = 0;
}

void Effect_Blink::RegisterObject(Context *context)
{
	context->RegisterFactory<Effect_Blink>();
}

void Effect_Blink::Start()
{
	ResourceCache* cache = GetSubsystem<ResourceCache>();
	BlinkNode = GetNode();
	ParticleEffect2D* particleEffect = cache->GetResource<ParticleEffect2D>("Urho2D/blink.pex");
	if (!particleEffect) return;
	ParticleEmitter2D* particleEmitter = BlinkNode->CreateComponent<ParticleEmitter2D>();
	particleEmitter->SetEffect(particleEffect);
	particleEffect->SetMaxRadius(0.1f);
	// Random particles cnt
	//particleEmitter->SetMaxParticles((int)Random(0, 100));
}

void Effect_Blink::Update(float timeStep)
{
	//Toolkit::Print("Blink"+String(Random(1.0f)));
	cal_duration_ += timeStep;
	if (cal_duration_ > duration_)
		Stop();
}

void Effect_Blink::FixedUpdate(float timeStep)
{

}

void Effect_Blink::Stop()
{
	// Remove the blink node(created by the Skill_Blink)
	BlinkNode->Remove();
}