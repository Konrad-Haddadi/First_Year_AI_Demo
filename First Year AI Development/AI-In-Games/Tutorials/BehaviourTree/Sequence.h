#pragma once

#include "Composite.h"

class Sequence : public Composite
{
public:
	Sequence() {}
	virtual ~Sequence() {}

	virtual void Enter(Agent* _agent) override;
	virtual int Update(Agent* _agent, float _dt) override;
	virtual void Exit(Agent* _agent) override;
};