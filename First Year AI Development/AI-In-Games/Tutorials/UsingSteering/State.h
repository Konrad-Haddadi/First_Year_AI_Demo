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
	virtual int Update(Agent* _agent, float _dt);
	virtual void Exit(Agent* _agent);

	Behaviour* GetBehaviour() { return m_current; }
	vector<Behaviour*> GetBehaviours() { return m_behaviours; }
	vector<Transition> GetTransitions() { return m_transition;  }
	void AddTransition(Condition* _condition, State* _targetState);

private:
	Behaviour* m_current;
	vector<Behaviour*> m_behaviours;
	vector<Transition> m_transition;

};

