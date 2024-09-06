#pragma once

#include "Behaviour.h"

class BehaviourTree;

class SearchTransition : public Behaviour
{
public:
	SearchTransition() { };
	~SearchTransition() { }
	virtual int Update(CovenantBaseAgent* _agent, float _dt) override;
	virtual int Update(Agent* _agent, float _dt) override;
};