#include "SelectAgent.h"

#include "State.h"
#include "NodeMap.h"
#include "DistanceCondition.h"
#include "WanderBehaviour.h"
#include "FollowBehavoiur.h"
#include "FiniteStateMachine.h"

SelectAgent::SelectAgent(NodeMap* _nodeMap, Color _color, int _speed)
	:	Agent(_nodeMap, nullptr, _color, _speed)
{
		
}

void SelectAgent::Load()
{
	DistanceCondition* closerThan5 = new DistanceCondition(5.0f * GetMap()->GetCellSize(), true);
	DistanceCondition* futherThan7 = new DistanceCondition(5.0f * GetMap()->GetCellSize(), false);

	State* wanderState = new State(new WanderBehaviour);
	State* followState = new State(new FollowBehavoiur);

	wanderState->AddTransition(closerThan5, followState);
	followState->AddTransition(futherThan7, wanderState);

	FiniteStateMachine* fsm = new FiniteStateMachine(wanderState);
	fsm->AddState(wanderState);
	fsm->AddState(followState);

	SetBehaviour(fsm);
	GetBehaviour()->Enter(this);
}


