#pragma once

#include "Behaviour.h"
#include "Spartan.h"

class FleeBehaviour : public Behaviour
{
public:
	FleeBehaviour() {}
	~FleeBehaviour() {}

	virtual int Update(Agent* _agent, float _dt) override;
	virtual int Update(CovenantAgent* _agent, float _dt) override;
};

