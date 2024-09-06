#pragma once

#include "Behaviour.h"

class CovenantAgent;

class Decorator : public Behaviour 
{
public:
	Decorator(Behaviour* _condition) : m_condition(_condition) {}
	virtual ~Decorator() { }

	virtual int Update(CovenantAgent* _agent, float _dt) = 0;
	virtual int Update(Agent* _agent, float _dt) = 0;

protected:
	Behaviour* m_condition;
};

