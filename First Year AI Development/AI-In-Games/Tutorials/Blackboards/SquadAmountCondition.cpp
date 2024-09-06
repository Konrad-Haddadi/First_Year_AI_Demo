#include "SquadAmountCondition.h"
#include "CovenantBaseAgent.h"
#include "glm/glm.hpp"
#include "Composite.h"

int SquadAmountCondition::Update(CovenantBaseAgent* _agent, float _dt)
{
	int fleeAmount = 0;
	int fear = 6 - _agent->GetRank() * 2;

	if (_agent->GetTarget())
	{
		fleeAmount = _agent->GetTarget()->GetSquad().size() + _agent->GetSquad().size();

		for (auto a : _agent->GetSquad())
		{
			fleeAmount += a->GetSquad().size();
		}
	}
	else
	{
		fleeAmount = _agent->GetSquad().size();
		for (auto a : _agent->GetSquad())
		{
			fleeAmount += a->GetSquad().size();
		}
	}
 
	if (fear <= fleeAmount)
		return Composite::Success;
	else
	{
		if (_agent->GetTarget())
		{
			_agent->GetTarget()->RemoveFromSquad(_agent);
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
