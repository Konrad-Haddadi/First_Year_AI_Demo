#pragma once
#include "..\Behaviour.h"
#include <vector>

using std::vector;

class State;
class Agent;

class FiniteStateMachine : public Behaviour
{
public:
	FiniteStateMachine(State* _state) : m_currentState(_state), m_newState(nullptr) { m_states.push_back(_state); }
	virtual ~FiniteStateMachine();

	void AddState(State* _state);
	virtual int Update(Agent* _agent, float _dt) override;
	virtual int Update(CovenantAgent* _agent, float _dt) override;

private:
	vector<State*> m_states;

	State* m_currentState;
	State* m_newState;	
};

