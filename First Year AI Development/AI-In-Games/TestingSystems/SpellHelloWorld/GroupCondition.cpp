#include "GroupCondition.h"
#include "CovenantAgent.h"
#include "Composite.h"
#include "Agent.h"
#include <list>

using std::list;

bool CanSee(CovenantAgent* _agent, CovenantAgent* _target);

int GroupCondition::Update(CovenantAgent* _agent, float _dt)
{
	int quad = _agent->GetCurrentQuad();
	int frontQuad = _agent->GetHashTable()->CheckQuad(_agent->GetSteeringAgent()->GetFurthestPoint());
	
	list<CovenantAgent*> group = *_agent->GetHashTable()->GetCovenant(quad);

	for (auto a : *_agent->GetHashTable()->GetCovenant(frontQuad))
	{
		group.push_back(a);
	}

	if (!_agent->GetCovenantTarget())
	{
		for (CovenantAgent* a : group) 
		{
			if (a->GetRank() > _agent->GetRank() && CanSee(_agent, a))
			{
				_agent->SetTarget(a);
				a->AddToSquad(_agent);
				return Composite::Success;
			}
		}
	}
	return Composite::Failure;
}

int GroupCondition::Update(Agent* _agent, float _dt)
{
	return 0;
}

bool CanSee(CovenantAgent* _agent, CovenantAgent* _target)
{
	vector<vec2> tri = _agent->GetSteeringAgent()->GetTrianglePoints();

	if (CheckCollisionPointTriangle({ _target->Transform()->Position().x, _target->Transform()->Position().y },
		{ tri[0].x, tri[0].y }, { tri[1].x, tri[1].y }, { tri[2].x, tri[2].y }))
		return true;
	else
		return false;	
}