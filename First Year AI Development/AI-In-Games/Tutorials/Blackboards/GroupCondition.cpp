#include "GroupCondition.h"
#include "CovenantBaseAgent.h"
#include "Composite.h"
#include "Agent.h"
#include <list>

using std::list;

int GroupCondition::Update(CovenantBaseAgent* _agent, float _dt)
{
	int quad = _agent->GetCurrentQuad();

	list<CovenantBaseAgent*>* group = _agent->GetHashTable()->GetCovenant(quad);

	for (CovenantBaseAgent* a : *group) {

		if (a->GetRank() > _agent->GetRank())
		{
			_agent->SetTarget(a);
			a->AddToSquad(_agent);
			return Composite::Success;
		}
	}
	return Composite::Failure;
}

int GroupCondition::Update(Agent* _agent, float _dt)
{
	return 0;
}
