#include "PassiveTransition.h"
#include "Composite.h"
#include "Agent.h"
#include "CovenantAgent.h"
#include "PassiveTree.h"

int PassiveTransition::Update(Agent* _agent, float _dt)
{
	_agent->SetNextBehaviour(new PassiveTree);

	return Composite::Success;
}

int PassiveTransition::Update(CovenantAgent* _agent, float _dt)
{
	_agent->SetNextBehaviour(new PassiveTree);

	return Composite::Success;
}