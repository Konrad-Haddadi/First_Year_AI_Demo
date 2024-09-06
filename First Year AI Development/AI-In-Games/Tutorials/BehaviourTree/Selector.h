#pragma once

#include "Composite.h"

class Selector : public Composite
{
public:
	Selector() {}
	virtual ~Selector() { }

	virtual void Enter(Agent* _agent) override;
	virtual int Update(Agent* _agent, float _dt) override;
	virtual void Exit(Agent* _agent) override;

	
};