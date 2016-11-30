#pragma once

#include "Bullet.h"
class AP : public Bullet
{
	/// Life-cycle function
public:
	/// Construct.
	AP(Context* context);
	/// Register object factory and attributes.
	static void RegisterObject(Context* context);
	/// Handle startup. Called by LogicComponent base class.
	void Start();
	/// Handle physics world update. Called by LogicComponent base class.
	void FixedUpdate(float timeStep);
	/// Remove from the scene(not system function)
	void End();

	/// Events handlers
public:
	void HandleContactBegin(StringHash eventType, VariantMap& eventData);
};