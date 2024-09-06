#pragma once

class Agent;

class Condition
{
public: 
	virtual bool IsTrue(Agent* _agent) = 0;
};

