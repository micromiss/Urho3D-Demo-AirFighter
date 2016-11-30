#pragma once

#include <Urho3D/Scene/LogicComponent.h>

#include "GameObject.h"

using namespace Urho3D;

class Box : public GameObject
{
	URHO3D_OBJECT(Box, LogicComponent);

private:
	/// Member varible
	Node* node_;
	RigidBody2D* rigibody2d_;
	CollisionBox2D* collisionbox2d_;

public:
	/// Function
	Box::Box(Context* context);

	/// LifeCycle Function
	void Start();
	void FixedUpdate(float timeStep);
	/// Register object factory and attributes.
	static void RegisterObject(Context* context);

	/// Game event
	void Damaged(float damage);
	void Destoryed();

	/// Handle Event(never used)
	void HandleHit(StringHash eventType, VariantMap& eventData);

};
