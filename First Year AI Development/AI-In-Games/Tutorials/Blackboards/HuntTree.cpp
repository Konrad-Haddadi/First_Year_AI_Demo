#include "HuntTree.h"

#include "Selector.h"
#include "Sequence.h"
#include "SpartanDistanceCondition.h"
#include "FollowSpartanBehaviour.h"
#include "Transition.h"
#include "NotDecorator.h"
#include "Composite.h"
#include "SearchTransition.h"
#include "PassiveTransition.h"
#include "SquadAmountCondition.h"
#include "FleeBehaviour.h"
HuntTree::HuntTree()
{
	m_behaviour =
		(new Selector)
		->Add((new Sequence)
			->Add(new SpartanDistanceCondition)
			->Add(new SquadAmountCondition)
			->Add(new FollowSpartanBehaviour)
			->Add(new SearchTransition))
		->Add((new Sequence)
			->Add(new NotDecorator(new SquadAmountCondition))
			->Add(new FleeBehaviour)
			->Add(new PassiveTransition))
		->Add((new Sequence)
			->Add(new NotDecorator(new SpartanDistanceCondition))
			->Add(new SearchTransition));
}

int HuntTree::Update(CovenantBaseAgent* _agent, float _dt)
{
	return m_behaviour->Update(_agent, _dt);
}

