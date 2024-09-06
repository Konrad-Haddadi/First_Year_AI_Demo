#include "../GroupTree.h"
#include "../../TestingSystems/AddngWeapons/Behaviour/BehaviourTree/Composite/Selector.h"
#include "../../TestingSystems/AddngWeapons/Behaviour/BehaviourTree/Composite/Sequence.h"
#include "../../TestingSystems/AddngWeapons/Behaviour/BehaviourTree/Conditions/GroupCondition.h"
#include "../../TestingSystems/AddngWeapons/Behaviour/BehaviourTree/Transition/PassiveTransition.h"
#include "../../TestingSystems/AddngWeapons/Behaviour/BehaviourTree/Transition/SearchTransition.h"
#include "../../TestingSystems/AddngWeapons/Behaviour/WanderBehaviour.h"
#include "../../TestingSystems/AddngWeapons/Behaviour/BehaviourTree/Composite/NotDecorator.h"

GroupTree::GroupTree()
{
	m_behaviour =
		(new Selector)
		->Add((new Sequence)
			->Add(new GroupCondition)
			->Add(new SearchTransition))
		->Add((new Selector)
			->Add(new NotDecorator(new WanderBehaviour))
			->Add(new PassiveTransition));		
}

int GroupTree::Update(CovenantAgent* _agent, float _dt)
{
	return m_behaviour->Update(_agent, _dt);
}