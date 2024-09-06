#include "Transition.h"
#include "BehaviourTree.h"
#include "Agent.h"
#include "CovenantAgent.h"
#include "Composite.h"

Transition::Transition(BehaviourTree* _next)
	: m_next(_next)
{
	
}

int Transition::Update(Agent* _agent, float _dt)
{
	_agent->SetNextBehaviour(m_next);

	return Composite::Success;
}
int Transition::Update(CovenantAgent* _agent, float _dt)
{
	_agent->SetNextBehaviour(m_next);

	return Composite::Success;
}