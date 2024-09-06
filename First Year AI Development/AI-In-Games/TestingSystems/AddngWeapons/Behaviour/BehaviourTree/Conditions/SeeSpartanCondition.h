#pragma once

#include "Behaviour.h"

class CovenantAgent;

class SeeSpartanCondition : public Behaviour
{
public:
	SeeSpartanCondition() { }
	virtual int Update(CovenantAgent* _agent, float _dt) override;
	virtual int Update(Agent* _agent, float _dt) override;
};