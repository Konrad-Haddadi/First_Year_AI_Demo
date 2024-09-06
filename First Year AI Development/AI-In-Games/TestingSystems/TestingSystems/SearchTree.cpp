#include "SearchTree.h"

#include "Selector.h"
#include "Sequence.h"
#include "DistanceCondition.h"
#include "FollowBehavoiur.h"
#include "Transition.h"
#include "NotDecorator.h"
#include "Composite.h"
#include "PassiveTransition.h"
#include "HuntCondition.h"
#include "HuntTransition.h"

SearchTree::SearchTree()
{
	m_behaviour =
		(new Selector)
		->Add((new Sequence)
			->Add(new HuntCondition)
			->Add(new HuntTransition))
		->Add((new Sequence)
			->Add(new DistanceCondition)
			->Add(new FollowBehavoiur))
		->Add((new Sequence)
			->Add(new NotDecorator(new DistanceCondition))
			->Add(new PassiveTransition));
}

int SearchTree::Update(CovenantBaseAgent* _agent, float _dt)
{
	return m_behaviour->Update(_agent, _dt);
}

