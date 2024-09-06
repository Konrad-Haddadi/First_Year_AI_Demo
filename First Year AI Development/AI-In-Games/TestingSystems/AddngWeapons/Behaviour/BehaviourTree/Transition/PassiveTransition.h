#pragma once

#include "Behaviour.h"

class BehaviourTree;

class PassiveTransition : public Behaviour
{
public:
	PassiveTransition() { };
	~PassiveTransition() { }
	virtual int Update(Agent* _agent, float _dt) override;
	virtual int Update(CovenantAgent* _agent, float _dt) override;


};