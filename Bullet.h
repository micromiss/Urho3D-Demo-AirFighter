#pragma once

#include <Urho3D/Scene/LogicComponent.h>

using namespace Urho3D;

class Bullet : public LogicComponent
{

	URHO3D_OBJECT(Bullet, LogicComponent);

private:
	/// The flying speed of the bullet
	float speed;
	/// The damage of the damage when it hits a GameObject
	float damage;
	/// The mass of the bullet
	float mass;
	/// The size of collision Box
	Vector2 collisionSize;
	/// The owner of the bullet
	Node* producer;


public:
	/// About speed
	virtual float GetSpeed() { return speed; }
	virtual void SetSpeed(float m_speed) { speed = m_speed; }

	/// About damage
	virtual float GetDamage() { return damage; }
	virtual void SetDamage(float m_damage) { damage = m_damage; }

	/// Get collisionSize
	virtual Vector2 GetCollisionSize() { return collisionSize; }
	virtual void SetCollisionSize(Vector2 m_collisionSize) { collisionSize = m_collisionSize; }

	/// Get mass
	virtual float GetMass() { return mass; }
	virtual void SetMass(float m_mass) { mass = m_mass; }

	/// The owner of the bullet
	virtual Node* GetProducer() { return producer; }
	virtual void SetProducer(Node* m_producer) { producer = m_producer; }

	/// Life-cycle function
public:
	/// Construct.
	Bullet(Context* context);
	/// Register object factory and attributes.
	static void RegisterObject(Context* context);
	/// Handle startup. Called by LogicComponent base class.
	virtual void Start();
	/// Handle physics world update. Called by LogicComponent base class.
	virtual void FixedUpdate(float timeStep);

};