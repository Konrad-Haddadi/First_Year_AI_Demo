#pragma once

#include "Behaviour.h"
#include <vector>

using std::vector;

class Composite : public Behaviour
{
public:
	enum Results
	{
		Failure,
		Success,
		Pending
	};

	vector<Behaviour*> children;
	Behaviour* pendingChild = nullptr;
	int index;

	Composite* Add(Behaviour* _b) { children.push_back(_b); return this; }
	int Update(Agent* _agent, float _dt) = 0;
};