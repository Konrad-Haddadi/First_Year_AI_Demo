#pragma once

#include "Behaviour.h"

class WanderBehaviour : public Behaviour
{
public:
	WanderBehaviour() {}
	~WanderBehaviour() {}

	virtual int Update(Agent* _agent, float _dt) override;
	virtual int Update(CovenantAgent* _agent, float _dt) override;

	
};

