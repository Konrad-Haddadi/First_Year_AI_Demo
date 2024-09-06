#include "../HuntTree.h"
#include "../../TestingSystems/AddngWeapons/Behaviour/BehaviourTree/Composite/Selector.h"
#include "../../TestingSystems/AddngWeapons/Behaviour/BehaviourTree/Composite/Sequence.h"
#include "../../TestingSystems/AddngWeapons/Behaviour/BehaviourTree/Conditions/SpartanDistanceCondition.h"
#include "../../TestingSystems/AddngWeapons/Behaviour/BehaviourTree/Conditions/SeeSpartanCondition.h"
#include "../../TestingSystems/AddngWeapons/Behaviour/BehaviourTree/Conditions/SquadAmountCondition.h"
#include "../../TestingSystems/AddngWeapons/Behaviour/BehaviourTree/Transition/PassiveTransition.h"
#include "../../TestingSystems/AddngWeapons/Behaviour/BehaviourTree/Transition/SearchTransition.h"
#include "../../TestingSystems/AddngWeapons/Behaviour/FollowSpartanBehaviour.h"
#include "../../TestingSystems/AddngWeapons/Behaviour/FleeBehaviour.h"
#include "../../TestingSystems/AddngWeapons/Behaviour/WanderBehaviour.h"
#include "../../TestingSystems/AddngWeapons/Behaviour/BehaviourTree/Composite/NotDecorator.h"

HuntTree::HuntTree()
{
	m_behaviour =
		(new Selector)
		->Add((new Sequence)
			->Add(new SpartanDistanceCondition)
			->Add(new SquadAmountCondition)
			->Add(new FollowSpartanBehaviour))
		->Add((new Sequence)
			->Add(new NotDecorator(new SquadAmountCondition))
			->Add(new FleeBehaviour)
			->Add(new PassiveTransition))
		->Add((new Sequence)
			->Add(new NotDecorator(new SeeSpartanCondition))
			->Add(new SearchTransition));
}

int HuntTree::Update(CovenantAgent* _agent, float _dt)
{
	return m_behaviour->Update(_agent, _dt);
}

