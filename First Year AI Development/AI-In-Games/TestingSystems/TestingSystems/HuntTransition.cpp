#include "HuntTransition.h"

#include "Composite.h"
#include "Agent.h"
#include "CovenantBaseAgent.h"
#include "HuntTree.h"

int HuntTransition::Update(Agent* _agent, float _dt)
{
	_agent->SetBehaviour(new HuntTree);

	return Composite::Success;
}

int HuntTransition::Update(CovenantBaseAgent* _agent, float _dt)
{
	_agent->SetBehaviour(new HuntTree);

	return Composite::Success;
}