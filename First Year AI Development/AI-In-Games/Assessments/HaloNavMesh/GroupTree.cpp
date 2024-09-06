#include "GroupTree.h"
#include "Selector.h"
#include "Sequence.h"
#include "GroupCondition.h"
#include "PassiveTransition.h"
#include "SearchTransition.h"
#include "WanderBehaviour.h"
#include "NotDecorator.h"

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