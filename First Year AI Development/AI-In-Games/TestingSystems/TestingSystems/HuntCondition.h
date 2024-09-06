#pragma once

#include "Behaviour.h"

class Agent;
class CovenantBaseAgent;

class HuntCondition : public Behaviour
{
public:
	HuntCondition() { }
	virtual int Update(CovenantBaseAgent* _agent, float _dt) override;
	virtual int Update(Agent* _agent, float _dt) override;

};