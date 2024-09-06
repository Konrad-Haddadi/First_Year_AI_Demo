#pragma once

#include "../../Behaviour.h"

class BehaviourTree : public Behaviour
{
public:
	BehaviourTree() : m_behaviour(nullptr) { }	
	virtual int Update(Agent* _agent, float _dt) { return 0; }
	virtual int Update(CovenantAgent* _agent, float _dt) = 0;

protected:
	Behaviour* m_behaviour;
};

