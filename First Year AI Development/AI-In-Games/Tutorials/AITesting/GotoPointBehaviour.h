#pragma once

#include "Behaviour.h"

class GotoPointBehaviour : public Behaviour
{
public:
	virtual void Enter(Agent* _agent) override;
	virtual void Update(Agent* _agent, float _dt) override;	
	virtual void Exit(Agent* _agent) override;
};