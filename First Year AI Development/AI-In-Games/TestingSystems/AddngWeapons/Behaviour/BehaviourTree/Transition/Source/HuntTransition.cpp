#include "HuntTransition.h"

#include "Composite.h"
#include "Agent.h"
#include "CovenantAgent.h"
#include "HuntTree.h"

int HuntTransition::Update(Agent* _agent, float _dt)
{
	_agent->SetNextBehaviour(new HuntTree);

	return Composite::Success;
}

int HuntTransition::Update(CovenantAgent* _agent, float _dt)
{
	_agent->SetNextBehaviour(new HuntTree);

	return Composite::Success;
}