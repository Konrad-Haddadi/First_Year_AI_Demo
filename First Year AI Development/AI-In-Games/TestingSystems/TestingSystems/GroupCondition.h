#pragma once

#include "Behaviour.h"

class Agent;
class CovenantBaseAgent;

class GroupCondition : public Behaviour
{
public:
	GroupCondition() { }
	virtual int Update(CovenantBaseAgent* _agent, float _dt) override;
	virtual int Update(Agent* _agent, float _dt) override;

};