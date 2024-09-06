#include "FollowBehavoiur.h"
#include "NodeMap.h"
#include "Agent.h"
#include "Composite.h"
#include <glm/glm.hpp>
#include <raylib/raylib.h>

void FollowBehavoiur::Enter(Agent* _agent)
{
	_agent->SetColor(RED);	
}

int FollowBehavoiur::Update(Agent* _agent, float _dt)
{	
	Agent* target = _agent->GetTarget();

	float dist = glm::distance({ target->GetPos().x + 55, target->GetPos().y + 55 }, lastTargetPos);
	if (dist > _agent->GetMap()->GetCellSize() * 2)
	{
		lastTargetPos = { target->GetPos().x + 55, target->GetPos().y + 55 };
		_agent->GoTo(lastTargetPos);
		return Composite::Pending;
	}	
	else
		return Composite::Failure;
}

void FollowBehavoiur::Exit(Agent* _agent)
{
	_agent->GetPath().clear();
}
