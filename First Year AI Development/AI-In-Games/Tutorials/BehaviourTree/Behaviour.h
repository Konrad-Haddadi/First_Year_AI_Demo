#pragma once

class Agent;

class Behaviour
{
public:
	Behaviour() {}
	virtual ~ Behaviour() {}

	virtual void Enter(Agent* _agent) { };
	virtual int Update(Agent* _agent, float _dt) = 0;
	virtual void Exit(Agent* _agent) {};

};