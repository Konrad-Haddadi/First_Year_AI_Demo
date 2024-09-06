#include "State.h"

#include "Composite.h"
#include "Behaviour.h"

State::State(Behaviour* _b)
{
	if(!m_current)
		m_current = _b;

	m_behaviours.push_back(_b);
}

State::~State()
{
	for (Behaviour* b : m_behaviours)
		delete b;

	for (Transition t : m_transition)
		delete t.condition;
}

void State::Enter(Agent* _agent)
{
	for (Behaviour* b : m_behaviours)
		b->Enter(_agent);
}

int State::Update(Agent* _agent, float _dt)
{
	for (Behaviour* b : m_behaviours)
		return b->Update(_agent, _dt);

	return Composite::Success;
}

void State::Exit(Agent* _agent)
{
	for (Behaviour* b : m_behaviours)
		b->Exit(_agent);
}

void State::AddTransition(Condition* _condition, State* _targetState)
{
	m_transition.push_back({ _condition, _targetState });
}
