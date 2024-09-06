#pragma once

#include "Behaviour.h"

class GotoPointBehaviour : public Behaviour
{
public:
	GotoPointBehaviour() {}
	~GotoPointBehaviour() {}

	virtual int Update(CovenantBaseAgent* _agent, float _dt) override;
	virtual int Update(Agent* _agent, float _dt) override;
};