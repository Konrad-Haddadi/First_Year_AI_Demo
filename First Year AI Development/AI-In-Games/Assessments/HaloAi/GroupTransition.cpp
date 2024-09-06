#include "GroupTransition.h"

#include "Composite.h"
#include "Agent.h"
#include "CovenantBaseAgent.h"
#include "GroupTree.h"

int GroupTransition::Update(Agent* _agent, float _dt)
{
	_agent->SetBehaviour(new GroupTree);

	return Composite::Success;
}

int GroupTransition::Update(CovenantBaseAgent* _agent, float _dt)
{
	_agent->SetBehaviour(new GroupTree);

	return Composite::Success;
}