#pragma once

#include <Urho3D/Scene/LogicComponent.h>
#include "BUFF.h"

using namespace Urho3D;

class HeatSource : public BUFF {
	URHO3D_OBJECT(HeatSource, LogicComponent);

private:
	/// Max range that the heat source can be tracked
	//float trackedRange;
	/// The attraction of the heat source
	float attraction;

public:
	//float GetTrackedRange() { return trackedRange; }
	//void SetTrackedRange(float m_trackedRange) { trackedRange = m_trackedRange; }
	float GetAttraction() { return attraction; }
	void SetAttraction(float m_attraction) { attraction = m_attraction; }
	
	/// Life-cycle function
public:
	/// Construct.
	HeatSource(Context* context);
	/// Register object factory and attributes.
	static void RegisterObject(Context* context);
	/// Handle startup. Called by LogicComponent base class.
	void Start();
	/// Handle physics world update. Called by LogicComponent base class.
	void Update(float timeStep);



};