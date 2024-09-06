#pragma once

class Agent;
class CovenantAgent;

class Behaviour
{
public:
	Behaviour() {}
	virtual ~ Behaviour() {}
	
	virtual int Update(Agent* _agent, float _dt) = 0;
	virtual int Update(CovenantAgent* _agent, float _dt) = 0;

};