#include "Transition.h"
#include "BehaviourTree.h"
#include "Agent.h"
#include "Composite.h"

Transition::Transition(BehaviourTree* _next)
	: m_next(_next)
{
	
}

int Transition::Update(Agent* _agent, float _dt)
{
	_agent->SetBehaviour(m_next);

	return Composite::Success;
}