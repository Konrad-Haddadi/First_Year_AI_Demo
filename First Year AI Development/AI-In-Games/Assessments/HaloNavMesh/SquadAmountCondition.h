#pragma once

#include "Behaviour.h"

class CovenantAgent;

class SquadAmountCondition : public Behaviour
{
public:
	SquadAmountCondition() { }
	virtual int Update(CovenantAgent* _agent, float _dt) override;
	virtual int Update(Agent* _agent, float _dt) override;
};