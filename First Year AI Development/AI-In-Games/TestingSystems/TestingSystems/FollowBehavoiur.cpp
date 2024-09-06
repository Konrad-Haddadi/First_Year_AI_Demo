#include "FollowBehavoiur.h"
#include "NodeMap.h"
#include "CovenantBaseAgent.h"
#include "Composite.h"
#include <glm/glm.hpp>
#include <raylib/raylib.h>


int FollowBehavoiur::Update(CovenantBaseAgent* _agent, float _dt)
{	
	CovenantBaseAgent* target = _agent->GetTarget();
	
	float dist = glm::distance(target->GetPos(), lastTargetPos);

	if (dist > 40)
	{
		lastTargetPos = target->GetPos();
		_agent->GoTo(lastTargetPos);
	}
	
	return Composite::Success;	
}

int FollowBehavoiur::Update(Agent* _agent, float _dt)
{
	return 0;
}
