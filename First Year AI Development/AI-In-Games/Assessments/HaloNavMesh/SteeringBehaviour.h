#pragma once

class SteeringAgent;

class SteeringBehaviour
{
public:
	SteeringBehaviour() {}
	~SteeringBehaviour() {}

	virtual int Update(SteeringAgent* _agent, float _dt) = 0;
};