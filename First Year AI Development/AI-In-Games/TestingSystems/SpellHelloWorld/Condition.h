#pragma once

#include "Agent.h"

class Condition
{
public: 
	virtual bool IsTrue(Agent* _agent) = 0;
};

