#pragma once

#include <Urho3D/Scene/LogicComponent.h>

using namespace Urho3D;

class Effect : public LogicComponent
{

	URHO3D_OBJECT(Effect, LogicComponent);

private:
	/// The owner of the effect
	SharedPtr<Node> producer_;

public:
	/// The owner of the bullet
	virtual SharedPtr<Node> GetProducer() { return producer_; }
	virtual void SetProducer(SharedPtr<Node> m_producer) { producer_ = m_producer; }

	/// Life-cycle function
public:
	/// Construct.
	Effect(Context* context);
	/// Register object factory and attributes.
	static void RegisterObject(Context* context);
	/// Handle startup. Called by LogicComponent base class.
	virtual void Start();
	/// Handle update
	virtual void Update(float timeStep);
	/// Handle physics world update. Called by LogicComponent base class.
	virtual void FixedUpdate(float timeStep);

};