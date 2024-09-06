#pragma once

#include "Behaviour.h"

class CovenantAgent;

class SpartanDistanceCondition : public Behaviour
{
public:
	SpartanDistanceCondition() { }
	virtual int Update(CovenantAgent* _agent, float _dt) override;
	virtual int Update(Agent* _agent, float _dt) override;
};
