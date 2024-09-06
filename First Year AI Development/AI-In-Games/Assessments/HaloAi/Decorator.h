#pragma once

#include "Behaviour.h"

class CovenantBaseAgent;

class Decorator : public Behaviour 
{
public:
	Decorator(Behaviour* _condition) : m_condition(_condition) {}
	virtual ~Decorator() { delete m_condition; }

	virtual int Update(CovenantBaseAgent* _agent, float _dt) = 0;
	virtual int Update(Agent* _agent, float _dt) = 0;

protected:
	Behaviour* m_condition;
};

