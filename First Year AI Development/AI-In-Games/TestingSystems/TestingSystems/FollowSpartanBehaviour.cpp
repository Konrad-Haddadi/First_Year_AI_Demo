#include "FollowSpartanBehaviour.h"
#include "NodeMap.h"
#include "CovenantBaseAgent.h"
#include "SpartanAgent.h"
#include "Composite.h"
#include <glm/glm.hpp>
#include <raylib/raylib.h>


int FollowSpartanBehaviour::Update(CovenantBaseAgent* _agent, float _dt)
{
	SpartanAgent* target = _agent->GetTargetEnemy();

	float dist = glm::distance(target->GetPos(), lastTargetPos);

	if (dist > 40)
	{
		lastTargetPos = target->GetPos();
		_agent->GoTo(lastTargetPos);
	}

	return Composite::Pending;
}

int FollowSpartanBehaviour::Update(Agent* _agent, float _dt)
{
	return 0;
}
