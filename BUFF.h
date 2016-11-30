#pragma once

#include <Urho3D/Scene/LogicComponent.h>

using namespace Urho3D;

class BUFF : public LogicComponent {

	URHO3D_OBJECT(BUFF, LogicComponent);

	/// Attributes of the GameObject
private:
	// Type of the buff
	int type;
	// Duration of the buff(-1 means forever)
	float duration;
	// Lasting time left for the buff 
	float timeleft;
	// The owner of the buff
	SharedPtr<Node> owner_;
	
	/// Custom function
public:
	int GetType() { return type; }
	void SetType(int m_type) { type = m_type; }
	float GetDuration() { return duration; }
	void SetDuration(float m_duration) { duration = m_duration; }
	float GetTimeleft() { return timeleft; }
	void SetTimeleft(float m_timeleft) { timeleft = m_timeleft; }
	SharedPtr<Node>GetOwner() { return owner_; }
	void SetOwner(SharedPtr<Node>m_owner_) { owner_ = m_owner_; }	

	/// Life-cycle function
public:
	/// Construct.
	BUFF(Context* context);
	/// Register object factory and attributes.
	static void RegisterObject(Context* context);
	/// Handle startup. Called by LogicComponent base class.
	virtual void Start();
	/// Handle physics world update. Called by LogicComponent base class.
	virtual void Update(float timeStep);


};