#include "SearchTransition.h"

#include "Composite.h"
#include "Agent.h"
#include "CovenantAgent.h"
#include "SearchTree.h"

int SearchTransition::Update(Agent* _agent, float _dt)
{
	_agent->SetNextBehaviour(new SearchTree);

	return Composite::Success;
}

int SearchTransition::Update(CovenantAgent* _agent, float _dt)
{
	_agent->SetNextBehaviour(new SearchTree);

	return Composite::Success;
}