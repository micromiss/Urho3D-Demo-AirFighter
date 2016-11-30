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
#include <Urho3D/Urho2D/PhysicsWorld2D.h>
#include <Urho3D/Urho2D/PhysicsEvents2D.h>
#include <Urho3D/Urho2D/RigidBody2D.h>

#include <Urho3D/Urho2D/Sprite2D.h>
#include <Urho3D/Urho2D/AnimatedSprite2D.h>
#include <Urho3D/Urho2D/AnimationSet2D.h>

#include "HeatSource.h"
#include "BUFFList.h"
#include "Toolkit.h"

HeatSource::HeatSource(Context *context) :
	BUFF(context)
{
	//SetUpdateEventMask(USE_UPDATE);
	SetType(BUFF_HEATSOURCE);
	SetDuration(-1);	
}

void HeatSource::RegisterObject(Context* context)
{
	context->RegisterFactory<HeatSource>();
}

void HeatSource::Start()
{

}

void HeatSource::Update(float timeStep)
{
	
}