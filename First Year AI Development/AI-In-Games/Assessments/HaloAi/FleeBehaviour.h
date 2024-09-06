#pragma once

#include "Behaviour.h"

class FleeBehaviour : public Behaviour
{
public:
	FleeBehaviour() {}
	~FleeBehaviour() {}

	virtual int Update(Agent* _agent, float _dt) override;
	virtual int Update(CovenantBaseAgent* _agent, float _dt) override;
};

