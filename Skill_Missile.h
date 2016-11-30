#pragma once

#include <Urho3D/Scene/LogicComponent.h>

#include "Skill.h"
#include "Missile.h"

using namespace Urho3D;

class Skill_Missile : public Skill
{
	URHO3D_OBJECT(Skill_Missile, LogicComponent);
	
private:
	/// Context
	Context* context_;
	/// Cooldown timer
	float cooldownTimer_;
	/// Initial velocity of the missile
	float initialVelocity_;

	/// Get and Set functions
public:
	float GetInitialVelocity() { return initialVelocity_; }
	void SetInitialVelocity(float m_initialVelocity) { initialVelocity_ = m_initialVelocity; }

	/// Life-cycle function
public:
	/// Construct.
	Skill_Missile(Context* context);
	/// Register object factory and attributes.
	static void RegisterObject(Context* context);
	/// Handle startup. Called by LogicComponent base class.
	void Start();
	/// Handle physics world update. Called by LogicComponent base class.
	void FixedUpdate(float timeStep);
	/// Handle update
	void Update(float timeStep);
};