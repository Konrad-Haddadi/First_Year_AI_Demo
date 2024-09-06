#include "State.h"

#include "Behaviour.h"

State::State(Behaviour* _b)
{
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

void State::Update(Agent* _agent, float _dt)
{
	for (Behaviour* b : m_behaviours)
		b->Update(_agent, _dt);
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
