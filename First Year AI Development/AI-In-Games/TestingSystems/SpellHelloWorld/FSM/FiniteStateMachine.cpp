#include "FiniteStateMachine.h"
#include "..\Condition.h"
#include "State.h"

FiniteStateMachine::~FiniteStateMachine()
{
	for (State* s : m_states)
		delete s;
}

void FiniteStateMachine::AddState(State* _state)
{
	m_states.push_back(_state);
}

int FiniteStateMachine::Update(Agent* _agent, float _dt)
{
	m_newState = nullptr;

	for (State::Transition t : m_currentState->GetTransitions())
	{
		if (t.targetState != m_currentState)
		{
			if (t.condition->IsTrue(_agent))
				m_newState = t.targetState;
		}	
	}
	
	if (m_newState != nullptr && m_newState != m_currentState)
		m_currentState = m_newState;	

	return	m_currentState->Update(_agent, _dt);
}

int FiniteStateMachine::Update(CovenantAgent* _agent, float _dt)
{
	return 0;
}
