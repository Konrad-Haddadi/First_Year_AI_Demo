#pragma once

#include "SteeringBehaviour.h"

class SteeringAgent;

class AvoidingBehaviour : public SteeringBehaviour
{
public:
	AvoidingBehaviour() {}
	~AvoidingBehaviour() {}

	virtual int Update(SteeringAgent* _agent, float _dt) override;
};