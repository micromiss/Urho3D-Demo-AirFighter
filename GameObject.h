#pragma once
#pragma once

#include <Urho3D/Scene/LogicComponent.h>

using namespace Urho3D;

class GameObject : public LogicComponent {

	URHO3D_OBJECT(GameObject, LogicComponent);

	/// Attributes of the GameObject
private:
	/// Max HP
	float maxHp;
	/// Current HP
	float hp;
	/// The size of collision Box
	Vector2 collisionSize;
	/// Cannot be damaged
	bool isInvincible;

	/// Custom function
public:
	/// Return current HP
	virtual float GetHp() { return hp; }
	/// Set current HP
	virtual void SetHp(float t_hp) { hp = t_hp; }
	/// Return max HP
	virtual float GetMaxHp() { return maxHp; }
	/// Set max Hp
	virtual void SetMaxHp(float t_MaxHp) { maxHp = t_MaxHp; }
	/// Get collisionSize
	virtual Vector2 GetCollisionSize() { return collisionSize; }
	/// Set collisionSize
	virtual void SetCollisionSize(Vector2 co) { collisionSize = co; }
	/// Set isInvincible
	virtual void SetInvincible(bool invincible) { isInvincible = invincible; }
	/// Handle the collisiton event(when the box is hitted by bullets)
	//virtual void HandleHit(StringHash eventType, VariantMap& eventData);
	/// HP =  HP-x
	virtual void Damaged(float damage);
	/// Be destoryed(remove from the scene)
	virtual void Destoryed();

	/// Life-cycle function
public:
	/// Construct.
	GameObject(Context* context);
	/// Register object factory and attributes.
	static void RegisterObject(Context* context);
	/// Handle startup. Called by LogicComponent base class.
	virtual void Start();
	/// Handle Update
	virtual void Update(float timeStep);
	/// Handle physics world update. Called by LogicComponent base class.
	virtual void FixedUpdate(float timeStep);

};