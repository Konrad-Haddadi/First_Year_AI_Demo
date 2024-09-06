#include "SearchTransition.h"

#include "Composite.h"
#include "Agent.h"
#include "CovenantBaseAgent.h"
#include "SearchTree.h"

int SearchTransition::Update(Agent* _agent, float _dt)
{
	_agent->SetBehaviour(new SearchTree);

	return Composite::Success;
}

int SearchTransition::Update(CovenantBaseAgent* _agent, float _dt)
{
	_agent->SetBehaviour(new SearchTree);

	return Composite::Success;
}