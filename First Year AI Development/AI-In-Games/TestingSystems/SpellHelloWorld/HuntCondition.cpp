#include "HuntCondition.h"
#include "CovenantAgent.h"
#include "Spartan.h"
#include "Composite.h"
#include "Agent.h"
#include <list>

using std::list;

int HuntCondition::Update(CovenantAgent* _agent, float _dt)
{
	vector<vec2> leftRightPoints = _agent->GetSteeringAgent()->GetTrianglePoints();
	int quad = _agent->GetCurrentQuad();
	int frontQuad = _agent->GetHashTable()->CheckQuad(_agent->GetSteeringAgent()->GetFurthestPoint());
	int leftQuad = _agent->GetHashTable()->CheckQuad(leftRightPoints[1]);
	int rightQuad = _agent->GetHashTable()->CheckQuad(leftRightPoints[2]);


	list<Spartan*> group = *_agent->GetHashTable()->GetSpartan(quad);
	
	for (auto a : *_agent->GetHashTable()->GetSpartan(frontQuad))
		group.push_back(a);
	
	if (leftQuad != frontQuad &&  leftQuad != _agent->GetCurrentQuad())
	{
		for (auto a : *_agent->GetHashTable()->GetSpartan(leftQuad))
			group.push_back(a);
	}

	if (rightQuad != frontQuad && rightQuad != _agent->GetCurrentQuad())
	{
		for (auto a : *_agent->GetHashTable()->GetSpartan(rightQuad))
			group.push_back(a);
	}

	for (Spartan* a : group)
	{
		if (!_agent->GetSpartanTarget())
		{
			vector<vec2> tri = _agent->GetSteeringAgent()->GetTrianglePoints();
			if (CheckCollisionPointTriangle({ a->Transform()->Position().x, a->Transform()->Position().y },
				{ tri[0].x, tri[0].y }, { tri[1].x, tri[1].y }, { tri[2].x, tri[2].y }) ||
				CheckCollisionPointTriangle({ a->GetPathAgent()->GetPos().x, a->GetPathAgent()->GetPos().y },
					{ tri[0].x, tri[0].y }, { tri[1].x, tri[1].y }, { tri[2].x, tri[2].y }))
			{
				_agent->enemyColor = ORANGE;
				_agent->SetTargetEnemy(a);
				return Composite::Success;
			}
			
		}
	}

	return Composite::Failure;
}

int HuntCondition::Update(Agent* _agent, float _dt)
{
	return 0;
}