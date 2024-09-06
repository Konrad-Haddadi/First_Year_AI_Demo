#pragma once

#include "Composite.h"

class Selector : public Composite
{
public:
	Selector() {}
	virtual ~Selector();

	virtual int Update(CovenantBaseAgent* _agent, float _dt) override;	
	virtual int Update(Agent* _agent, float _dt) override;	
};