#pragma once

#include <Urho3D/Scene/LogicComponent.h>

#include "GameObject.h"

using namespace Urho3D;

class Fighter : public GameObject
{
	URHO3D_OBJECT(Fighter, LogicComponent);

	/// parameter
private:
	float mass_;
	float speed_;
	float maxSpeed_;
	float damping_;
	float acceleration_;
	float brake_;
	Vector3 towards_;
	Vector2 towards2d_;
	float turningVelocity_;
	/// test
	int testcnt_;
	/// 4test
	int nettest1209_;

private:
	/// Member varible
	Node* node_;
	RigidBody2D* rigibody2d_;
	CollisionBox2D* collisionbox2d_;
	/// Player Controls
	Controls controls_;
	/// Bullets
	//Vector<Bullet*> bullets_;
	String bulletType_;

	///LIfe-cycle functions
public:
	void Start();
	void Update(float timeStep);
	void FixedUpdate(float timeStep);

	/// Customized functions
public:
	void Destoryed();

	/// parameter function
public:
	float GetMass() { return mass_; }
	void SetMass(float m_mass) { mass_ = m_mass; }

	Controls GetControls() { return controls_; }
	void SetControls(Controls m_controls) { controls_ = m_controls; }

	float GetSpeed() { return speed_; }
	void SetSpeed(float m_speed) { speed_ = m_speed; }

	float GetMaxSpeed() { return maxSpeed_; }
	void SetMaxSpeed(float m_maxSpeed) { maxSpeed_ = m_maxSpeed; }

	float GetDamping() { return damping_; }
	void SetDamping(float m_damping) { damping_ = m_damping; }
	void Damping() { speed_ -= damping_; if (speed_ <= 0) speed_ = 0; }

	float GetAcceleration() { return acceleration_; }
	void SetAcceleration(float m_acceleration) { acceleration_ = m_acceleration; }
	void Accelerate() { speed_ += acceleration_; if (speed_ > maxSpeed_) speed_ = maxSpeed_; }

	float GetBrake() { return brake_; }
	void SetBrake(float m_brake) { brake_ = m_brake; }
	void Brake() { speed_ -= brake_; if (speed_ < 0) speed_ = 0; }

	Vector3 GetTowards() { return towards_; }
	void SetTowards(Vector3 m_towards) { towards_ = m_towards; }

	float GetTurningVelocity() { return turningVelocity_; }
	void SetTurningVelocity(float m_turningVelocity) { turningVelocity_ = m_turningVelocity; }

	String GetBulletType() { return bulletType_; }
	void SetBulletType(String m_bulletType) { bulletType_ = m_bulletType; }

	///Fight
public:
	void Fire();

public:
	/// Function
	Fighter::Fighter(Context* context);
	/// Register
	static void RegisterObject(Context* context);
	/// initiate weapons
	void InitiateWeapons();
};