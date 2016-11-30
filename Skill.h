#pragma once

#include <Urho3D/Scene/LogicComponent.h>

using namespace Urho3D;

class Skill : public LogicComponent
{
	URHO3D_OBJECT(Skill, LogicComponent);

	/// Some private paramters
private:
	/// Owner of the skill
	SharedPtr<Node>owner_;
	/// Whether the skill is activated (Only to continuous skills)
	bool activated;
	/// Trigger key of the skill
	unsigned int triggerKey;
	/// Duration of the skill (Only to continuous skills)
	float duration;
	/// Cooldown
	float cooldown;
	
	/// Get and set function of the variables
public:
	SharedPtr<Node>GetOwner() { return owner_; }
	void SetOwner(SharedPtr<Node> m_owner) { owner_ = m_owner; }
	bool GetActivated() { return activated; }
	void SetActivated(bool m_activated) { activated = m_activated; }
	int GetTriggerKey() { return triggerKey; }
	void SetTriggerKey(int m_triggerKey) { triggerKey = m_triggerKey; }
	float GetDuration() { return duration; }
	void SetDuration(float m_duration) { duration = m_duration; }
	float GetCooldown() { return cooldown; }
	void SetCooldown(float m_cooldown) { cooldown = m_cooldown; }

	/// Life-cycle function
public:
	/// Construct.
	Skill(Context* context);
	/// Register object factory and attributes.
	static void RegisterObject(Context* context);
	/// Handle startup. Called by LogicComponent base class.
	virtual void Start();
	/// Handle physics world update. Called by LogicComponent base class.
	virtual void FixedUpdate(float timeStep);
	/// Handle update
	virtual void Update(float timeStep);

};