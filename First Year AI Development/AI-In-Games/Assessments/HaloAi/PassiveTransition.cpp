#include "PassiveTransition.h"
#include "Composite.h"
#include "Agent.h"
#include "CovenantBaseAgent.h"
#include "PassiveTree.h"

int PassiveTransition::Update(Agent* _agent, float _dt)
{
	_agent->SetBehaviour(new PassiveTree);

	return Composite::Success;
}

int PassiveTransition::Update(CovenantBaseAgent* _agent, float _dt)
{
	_agent->SetBehaviour(new PassiveTree);

	return Composite::Success;
}