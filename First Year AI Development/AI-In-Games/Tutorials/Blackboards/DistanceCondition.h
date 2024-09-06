#pragma once

#include "Behaviour.h"

class CovenantBaseAgent;

class DistanceCondition : public Behaviour
{
public:
	DistanceCondition() { }
	virtual int Update(CovenantBaseAgent* _agent, float _dt) override;
	virtual int Update(Agent* _agent, float _dt) override;
};