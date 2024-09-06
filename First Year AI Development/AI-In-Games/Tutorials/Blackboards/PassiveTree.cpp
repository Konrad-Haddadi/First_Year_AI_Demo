#include "PassiveTree.h"

#include "CovenantBaseAgent.h"
#include "Selector.h"
#include "Sequence.h"
#include "DistanceCondition.h"
#include "NotDecorator.h"
#include "SearchTransition.h"
#include "GroupTransition.h"
#include "HuntCondition.h"
#include "HuntTransition.h"
PassiveTree::PassiveTree()
{
	m_behaviour =
		(new Selector)
		->Add((new Sequence)
			->Add(new HuntCondition)
			->Add(new HuntTransition))
		->Add((new Sequence)
			->Add(new DistanceCondition)
			->Add(new SearchTransition))		
		->Add((new Sequence)
			->Add(new NotDecorator(new DistanceCondition))
			->Add(new GroupTransition));
}

int PassiveTree::Update(CovenantBaseAgent* _agent, float _dt)
{
	return m_behaviour->Update(_agent, _dt);
}