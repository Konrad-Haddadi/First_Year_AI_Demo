
#pragma once

#include "Decorator.h"

class CovenantBaseAgent;

class NotDecorator : public Decorator
{
public:
	NotDecorator(Behaviour* _condition) : Decorator(_condition) { }
	virtual ~NotDecorator() { delete m_condition; }

	virtual int Update(CovenantBaseAgent* _agent, float _dt);
	virtual int Update(Agent* _agent, float _dt);

};