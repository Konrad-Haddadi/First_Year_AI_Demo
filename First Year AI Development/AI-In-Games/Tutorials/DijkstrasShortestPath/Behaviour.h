#pragma once

class Agent;

class Behaviour
{
public:
	virtual void Enter(Agent* _agent) = 0;
	virtual void Update(Agent* _agent, float _dt) = 0;
	virtual void Exit(Agent* _agent) = 0;

};