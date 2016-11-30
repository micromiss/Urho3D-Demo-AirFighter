#pragma once

#include <Urho3D/Scene/LogicComponent.h>
#include "Effect.h"

using namespace Urho3D;

class Effect_Blink : public Effect
{
	URHO3D_OBJECT(Effect_Blink, LogicComponent);

public:
	/// Construct.
	Effect_Blink(Context* context);
	/// Register object factory and attributes.
	static void RegisterObject(Context* context);
	/// Handle startup. Called by LogicComponent base class.
	virtual void Start();
	/// Handle update
	virtual void Update(float timeStep);
	/// Handle physics world update. Called by LogicComponent base class.
	virtual void FixedUpdate(float timeStep);
	/// Called when the component is detached from a scene node, usually on destruction. Note that you will no longer have access to the node and scene at that point.
	virtual void Stop();

private:
	/// BlinkNode
	SharedPtr<Node> BlinkNode;
	/// The time Effect_Flare lasting
	float duration_;
	/// Time calculation
	float cal_duration_;

	/// Get and Set functions
public:
	float GetDuration() { return duration_; }
	void SetDuration(float m_duration) { duration_ = m_duration; }
};