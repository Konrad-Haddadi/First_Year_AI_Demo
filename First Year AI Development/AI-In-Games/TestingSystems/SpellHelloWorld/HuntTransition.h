#pragma once

#include "Behaviour.h"

class BehaviourTree;

class HuntTransition : public Behaviour
{
public:
	HuntTransition() { };
	~HuntTransition() { }
	virtual int Update(CovenantAgent* _agent, float _dt) override;
	virtual int Update(Agent* _agent, float _dt) override;
};