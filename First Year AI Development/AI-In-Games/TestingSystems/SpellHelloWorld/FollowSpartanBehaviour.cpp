#include "FollowSpartanBehaviour.h"
#include "CovenantAgent.h"
#include "Spartan.h"
#include "Composite.h"
#include <glm/glm.hpp>
#include <raylib/raylib.h>
#include <Azimuth/GameObjects/ATransform.h>


int FollowSpartanBehaviour::Update(CovenantAgent* _agent, float _dt)
{
	Spartan* target = _agent->GetSpartanTarget();
	float distFromLTP = glm::distance(target->Transform()->Position(), lastTargetPos);

	float distFromAgent = glm::distance(target->Transform()->Position(), _agent->Transform()->Position());
	
	if (distFromLTP > 50)
	{
		lastTargetPos = target->Transform()->Position();
		_agent->GoTo(lastTargetPos);
	}

	return Composite::Success;	
}

int FollowSpartanBehaviour::Update(Agent* _agent, float _dt)
{
	return 0;
}
