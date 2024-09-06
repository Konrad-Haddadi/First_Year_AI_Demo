#pragma once

#include "Behaviour.h"
#include "Node.h"

using AITesting::Node;

class WanderBehaviour : public Behaviour
{
public:
	virtual void Enter(Agent* _agent) override;
	virtual int Update(Agent* _agent, float _dt) override;
	virtual void Exit(Agent* _agent) override;
};

