#include "SquadAmountCondition.h"
#include "CovenantAgent.h"
#include "glm/glm.hpp"
#include "Composite.h"

int SquadAmountCondition::Update(CovenantAgent* _agent, float _dt)
{
	int sqaudAmount = 0;
	int fear = 10 - _agent->GetRank() * 4;

	if (_agent->GetCovenantTarget())
		sqaudAmount = _agent->GetCovenantTarget()->CheckSquadSize();
	else
		sqaudAmount = _agent->CheckSquadSize();
 
	if (fear <= sqaudAmount)
		return Composite::Success;
	else
	{
		if (_agent->GetCovenantTarget())
		{
			_agent->GetCovenantTarget()->RemoveFromSquad(_agent);
			_agent->SetTarget(nullptr);			
		}
		_agent->Reset();
		return Composite::Failure;
	}
}

int SquadAmountCondition::Update(Agent* _agent, float _dt)
{
	return 0;
}
