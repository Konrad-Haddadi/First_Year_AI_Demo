#include "GroupTransition.h"

#include "Composite.h"
#include "Agent.h"
#include "CovenantAgent.h"
#include "GroupTree.h"

int GroupTransition::Update(Agent* _agent, float _dt)
{
	_agent->SetNextBehaviour(new GroupTree);

	return Composite::Success;
}

int GroupTransition::Update(CovenantAgent* _agent, float _dt)
{
	_agent->SetNextBehaviour(new GroupTree);

	return Composite::Success;
}