// PAY ATTENTION that this effect will destory the node in the scene!!!
#pragma once

#include <Urho3D/Scene/LogicComponent.h>
#include "Effect.h"

using namespace Urho3D;

class Effect_Boom : public Effect
{
	URHO3D_OBJECT(Effect_Boom, LogicComponent);

public:
	/// Construct.
	Effect_Boom(Context* context);
	/// Register object factory and attributes.
	static void RegisterObject(Context* context);
	/// Handle startup. Called by LogicComponent base class.
	void Start();
	/// Handle update
	void Update(float timeStep);
	/// Handle physics world update. Called by LogicComponent base class.
	void FixedUpdate(float timeStep);
	/// Called when the component is detached from a scene node, usually on destruction. Note that you will no longer have access to the node and scene at that point.
	void Stop();

private:
	/// Scene node
	SharedPtr<Node> node;
	/// FlareNode
	SharedPtr<Node> BoomNode;
	/// The time Effect_Boom lasting
	float duration_;
	/// Time calculation
	float cal_duration_;
};
