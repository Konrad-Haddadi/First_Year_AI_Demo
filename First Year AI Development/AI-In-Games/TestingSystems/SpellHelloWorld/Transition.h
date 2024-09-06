#pragma once

#include "BehaviourTree.h"

class Transition : public Behaviour
{
public:
	Transition(BehaviourTree* _next);
	~Transition() { delete m_next; }
	virtual int Update(Agent* _agent, float _dt) override;
	virtual int Update(CovenantAgent* _agent, float _dt) override;
	
private:
	BehaviourTree* m_next;
};

