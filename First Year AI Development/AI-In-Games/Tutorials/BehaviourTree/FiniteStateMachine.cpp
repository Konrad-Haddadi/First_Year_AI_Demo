#include "FiniteStateMachine.h"
#include "Composite.h"
#include "Condition.h"
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

void FiniteStateMachine::Enter(Agent* _agent)
{
	m_currentState->Enter(_agent);
}

int FiniteStateMachine::Update(Agent* _agent, float _dt)
{
	m_newState = nullptr;

	for (State::Transition t : m_currentState->GetTransitions())
	{
		if (t.condition->IsTrue(_agent))
			m_newState = t.targetState;
	}
	
	if (m_newState != nullptr && m_newState != m_currentState)
	{
		m_currentState->Exit(_agent);
		m_currentState = m_newState;
		m_currentState->Enter(_agent);
	}

	m_currentState->Update(_agent, _dt);

	return Composite::Success;
}

void FiniteStateMachine::Exit(Agent* _agent)
{
	m_currentState->Exit(_agent);
}
