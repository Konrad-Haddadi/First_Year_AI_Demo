#pragma once

#include <vector>

using std::vector;

class Condition;
class Behaviour;
class Agent;

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

	virtual void Enter(Agent* _agent);
	virtual void Update(Agent* _agent, float _dt);
	virtual void Exit(Agent* _agent);

	vector<Transition> GetTransitions() { return m_transition;  }
	void AddTransition(Condition* _condition, State* _targetState);

private:
	vector<Behaviour*> m_behaviours;
	vector<Transition> m_transition;

};

