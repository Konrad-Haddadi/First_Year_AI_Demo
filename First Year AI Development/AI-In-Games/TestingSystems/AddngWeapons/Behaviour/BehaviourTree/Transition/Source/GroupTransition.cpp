#include "../GroupTransition.h"

#include "../../TestingSystems/AddngWeapons/Behaviour/BehaviourTree/Composite/Composite.h"
#include "../../TestingSystems/AddngWeapons/Agents/Agent.h"
#include "../../TestingSystems/AddngWeapons/Agents/CovenantAgent.h"
#include "../../TestingSystems/AddngWeapons/Behaviour/BehaviourTree/Tree/GroupTree.h"

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