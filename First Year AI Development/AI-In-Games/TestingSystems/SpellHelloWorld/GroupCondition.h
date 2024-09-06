#pragma once

#include "Behaviour.h"

class Agent;
class CovenantAgent;

class GroupCondition : public Behaviour
{
public:
	GroupCondition() { }
	virtual int Update(CovenantAgent* _agent, float _dt) override;
	virtual int Update(Agent* _agent, float _dt) override;

};