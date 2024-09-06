#pragma once

#include "Composite.h"

class Sequence : public Composite
{
public:
	Sequence() {}
	virtual ~Sequence();

	virtual int Update(CovenantAgent* _agent, float _dt) override;
	virtual int Update(Agent* _agent, float _dt) override;
};