#include "State.h"
#include "..\Behaviour.h"

State::State(Behaviour* _b)
{
	m_behaviours.push_back(_b);
}

State::~State()
{
	for (int i = m_behaviours.size() - 1; i >= 0; i--)
	{
		delete m_behaviours[i];
		m_behaviours[i] = nullptr;
	}
}

int State::Update(Agent* _agent, float _dt)
{
	for (Behaviour* b : m_behaviours)
		b->Update(_agent, _dt);

	return 0;
}

void State::AddTransition(Condition* _condition, State* _targetState)
{
	m_transition.push_back({ _condition, _targetState });
}
