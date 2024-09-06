#include "FollowBehavoiur.h"
#include "INavigatable.h"
#include "Agent.h"
#include <glm/glm.hpp>
#include <raylib/raylib.h>

void FollowBehavoiur::Enter(Agent* _agent)
{
	_agent->SetColor(RED);
}

void FollowBehavoiur::Update(Agent* _agent, float _dt)
{	
	Agent* target = _agent->GetTarget();

	float dist = glm::distance({ target->GetPos().x, target->GetPos().y }, lastTargetPos);
	if (dist > _agent->GetMap()->GetCellSize())
	{
		lastTargetPos = { target->GetPos().x, target->GetPos().y };
		_agent->GoTo(lastTargetPos);
	}

	
}

void FollowBehavoiur::Exit(Agent* _agent)
{
	_agent->GetPath().clear();
}
