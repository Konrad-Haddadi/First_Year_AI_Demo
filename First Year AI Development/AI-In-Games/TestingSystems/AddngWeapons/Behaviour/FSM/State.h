#pragma once

#include "..\Behaviour.h"
#include "..\Agent.h"
#include <vector>

using std::vector;

class Condition;

class State
{
public:
	struct Transition
	{
		Condition* condition;
		State* targetState;
	};

	State(Behaviour* _b);
	~State();

	virtual int Update(Agent* _agent, float _dt);

	vector<Transition> GetTransitions() { return m_transition;  }
	void AddTransition(Condition* _condition, State* _targetState);

private:
	vector<Behaviour*> m_behaviours;
	vector<Transition> m_transition;

};

