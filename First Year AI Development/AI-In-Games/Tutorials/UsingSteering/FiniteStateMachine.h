#pragma once
#include "Behaviour.h"
#include <vector>

using std::vector;

class State;
class Agent;

class FiniteStateMachine : public Behaviour
{
public:
	FiniteStateMachine(State* _state) : m_currentState(_state), m_newState(nullptr) { }
	virtual ~FiniteStateMachine();

	void AddState(State* _state);
	virtual void Enter(Agent* _agent);
	virtual int Update(Agent* _agent, float _dt);
	virtual void Exit(Agent* _agent);

private:
	vector<State*> m_states;

	State* m_currentState;
	State* m_newState;
};

