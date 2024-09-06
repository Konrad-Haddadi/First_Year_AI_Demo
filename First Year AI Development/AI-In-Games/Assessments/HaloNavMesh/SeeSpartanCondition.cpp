#include "SeeSpartanCondition.h"
#include "CovenantAgent.h"
#include "Spartan.h"
#include "glm/glm.hpp"
#include "Composite.h"
#include <vector>

using std::vector;

int SeeSpartanCondition::Update(CovenantAgent* _agent, float _dt)
{
	Spartan* target = _agent->GetSpartanTarget();

	if (target)
	{
		vector<vec2> tri = _agent->GetSteeringAgent()->GetTrianglePoints();

		if (CheckCollisionPointTriangle({ target->Transform()->Position().x, target->Transform()->Position().y }, 
			{ tri[0].x, tri[0].y },	{ tri[1].x, tri[1].y }, { tri[2].x, tri[2].y }) ||
			CheckCollisionPointTriangle({ target->GetPathAgent()->GetPos().x, target->GetPathAgent()->GetPos().y },
				{ tri[0].x, tri[0].y }, { tri[1].x, tri[1].y }, { tri[2].x, tri[2].y }))
		{
			_agent->Reset();
			return Composite::Success;
		}
		else
		{
			_agent->SetTargetEnemy(nullptr);
			return Composite::Failure;
		}
	}
	else
	{
		return Composite::Failure;
	}
}

int SeeSpartanCondition::Update(Agent* _agent, float _dt)
{
	return 0;
}
