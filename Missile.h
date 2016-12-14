#pragma once

#include <Urho3D/Scene/LogicComponent.h>
#include "GameObject.h"

using namespace Urho3D;

class Missile : public GameObject
{
	URHO3D_OBJECT(Missile, LogicComponent);

private:
	/// Rocket thrust of the missile
	float thrust;
	/// The detection range of the missile
	float detectionRange;
	/// I really dont know how to describe this in English. Just boom range!!!
	float boomRange;
	/// Boom Damage
	float damage;
	/// Missile Node
	SharedPtr<Node>node_;
	/// Target Node
	Vector<SharedPtr<Node>>targetnodes_;
	/// Owner of the missile
	SharedPtr<Node>producer_;
	/// Owner'ID of the missile
	int producerid_;
	/// Time the node has lasted for
	float duration_;

public:
	float GetThrust() { return thrust; }
	void SetThrust(float m_thrust) { thrust = m_thrust; }
	float GetDetectionRange() { return detectionRange; }
	void SetDetectionRange(float m_detectionRange) { detectionRange = m_detectionRange; }
	float GetBoomRange() { return boomRange; }
	void SetBoomRange(float m_boomRange) { boomRange = m_boomRange; }
	float GetDamage() { return damage; }
	void SetDamage(float m_damage) { damage = m_damage; }
	SharedPtr<Node> GetProducer() { return producer_; }
    void SetProducer(SharedPtr<Node> m_producer) { producer_ = m_producer; }
	int GetProducerid() { return producerid_; }
	void SetProducerid(int m_producerid) { producerid_ = m_producerid; }

	/// Life-cycle function
public:
	/// Construct.
	Missile(Context* context);
	Missile(Context* context, SharedPtr<Node>producer);
	/// Register object factory and attributes.
	static void RegisterObject(Context* context);
	/// Handle startup. Called by LogicComponent base class.
	void Start();
	/// Handle physics world update. Called by LogicComponent base class.
	void FixedUpdate(float timeStep);
	/// Handle update
	void Update(float timeStep);

	/// Event handle functions
public:
	/// When the missile has detected some heatsource, add it into the tracking queue.
	void HandleContactBegin(StringHash eventType, VariantMap& eventData);
	/// When the missle lost the target
	void HandleContactEnd(StringHash eventType, VariantMap& eventData);

};