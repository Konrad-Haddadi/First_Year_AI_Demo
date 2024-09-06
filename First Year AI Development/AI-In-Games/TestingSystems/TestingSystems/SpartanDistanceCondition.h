#pragma once

#include "Behaviour.h"

class CovenantBaseAgent;

class SpartanDistanceCondition : public Behaviour
{
public:
	SpartanDistanceCondition() { }
	virtual int Update(CovenantBaseAgent* _agent, float _dt) override;
	virtual int Update(Agent* _agent, float _dt) override;
};
