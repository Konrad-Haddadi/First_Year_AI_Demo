#include "HuntCondition.h"
#include "CovenantBaseAgent.h"
#include "SpartanAgent.h"
#include "Composite.h"
#include "Agent.h"
#include <list>

using std::list;

int HuntCondition::Update(CovenantBaseAgent* _agent, float _dt)
{
	int quad = _agent->GetCurrentQuad();

	list<SpartanAgent*>* group = _agent->GetHashTable()->GetSpartan(quad);

	for (SpartanAgent* a : *group)
	{
		if (!_agent->GetTargetEnemy())
		{
			_agent->SetTargetEnemy(a);
			return Composite::Success;
		}
	}

	return Composite::Failure;
}

int HuntCondition::Update(Agent* _agent, float _dt)
{
	return 0;
}