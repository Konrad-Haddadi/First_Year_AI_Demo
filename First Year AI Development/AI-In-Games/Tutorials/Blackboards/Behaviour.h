#pragma once

class Agent;
class CovenantBaseAgent;

class Behaviour
{
public:
	Behaviour() {}
	virtual ~ Behaviour() {}
	
	virtual int Update(Agent* _agent, float _dt) = 0;
	virtual int Update(CovenantBaseAgent* _agent, float _dt) = 0;
	

};