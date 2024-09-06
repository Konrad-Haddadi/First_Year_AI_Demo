#pragma once

#include "Behaviour.h"

class CovenantBaseAgent;

class SquadAmountCondition : public Behaviour
{
public:
	SquadAmountCondition() { }
	virtual int Update(CovenantBaseAgent* _agent, float _dt) override;
	virtual int Update(Agent* _agent, float _dt) override;
};