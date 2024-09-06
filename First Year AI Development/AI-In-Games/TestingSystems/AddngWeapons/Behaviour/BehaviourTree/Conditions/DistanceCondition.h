#pragma once

#include "../../Behaviour.h"

class CovenantAgent;

class DistanceCondition : public Behaviour
{
public:
	DistanceCondition() { }
	virtual int Update(CovenantAgent* _agent, float _dt) override;
	virtual int Update(Agent* _agent, float _dt) override;
};