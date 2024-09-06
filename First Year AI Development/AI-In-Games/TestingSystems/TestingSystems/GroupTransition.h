#pragma once

#include "Behaviour.h"

class BehaviourTree;

class GroupTransition : public Behaviour
{
public:
	GroupTransition() { };
	~GroupTransition() { }
	virtual int Update(Agent* _agent, float _dt) override;
	virtual int Update(CovenantBaseAgent* _agent, float _dt) override;
};