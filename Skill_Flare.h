#pragma once

#include <Urho3D/Scene/LogicComponent.h>

#include "Skill.h"
#include "Missile.h"

using namespace Urho3D;

class Skill_Flare : public Skill
{
	URHO3D_OBJECT(Skill_Flare, LogicComponent);

private:
	/// Cooldown timer
	float cooldownTimer_;

	/// Get and Set functions
public:


	/// Life-cycle function
public:
	/// Construct.
	Skill_Flare(Context* context);
	/// Register object factory and attributes.
	static void RegisterObject(Context* context);
	/// Handle startup. Called by LogicComponent base class.
	void Start();
	/// Handle physics world update. Called by LogicComponent base class.
	void FixedUpdate(float timeStep);
	/// Handle update
	void Update(float timeStep);
};