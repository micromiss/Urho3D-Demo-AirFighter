#pragma once

#include <Urho3D/Scene/LogicComponent.h>

#include "Skill.h"

using namespace Urho3D;

class Skill_Blink : public Skill
{
	URHO3D_OBJECT(Skill_Blink, LogicComponent);

private:
	/// Cooldown timer
	float cooldownTimer_;
	/// Blink range
	float blinkRange_;

	/// Get and Set functions
public:
	float GetBlinkRange() { return blinkRange_; }
	void SetBlinkRange(float m_blinkrange) { blinkRange_ = m_blinkrange; }

	/// Life-cycle function
public:
	/// Construct.
	Skill_Blink(Context* context);
	/// Register object factory and attributes.
	static void RegisterObject(Context* context);
	/// Handle startup. Called by LogicComponent base class.
	void Start();
	/// Handle physics world update. Called by LogicComponent base class.
	void FixedUpdate(float timeStep);
	/// Handle update
	void Update(float timeStep);
};