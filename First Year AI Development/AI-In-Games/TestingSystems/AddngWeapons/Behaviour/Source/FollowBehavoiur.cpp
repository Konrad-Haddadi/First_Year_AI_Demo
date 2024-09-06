#include "../FollowBehavoiur.h"
#include "../../Agents/CovenantAgent.h"	
#include "../../Agents/Spartan.h"
#include "../../Agents/Agent.h"
#include "../BehaviourTree/Composite/Composite.h"
#include <glm/glm.hpp>
#include <raylib/raylib.h>
#include <Azimuth/GameObjects/ATransform.h>

int FollowBehavoiur::Update(CovenantAgent* _agent, float _dt)
{	
	CovenantAgent* target = _agent->GetCovenantTarget();
	
	float dist = glm::distance(target->Transform()->Position(), lastTargetPos);

	if (dist > 40)
	{
		lastTargetPos = target->Transform()->Position();
		_agent->GoTo(lastTargetPos);
	}
	
	return Composite::Success;	
}

int FollowBehavoiur::Update(Agent* _agent, float _dt)
{
	Spartan* target = _agent->GetSpartanTarget();

	float dist = glm::distance(target->Transform()->Position(), lastTargetPos);

	if (dist > 40)
	{
		lastTargetPos = target->Transform()->Position();
		_agent->GoTo(lastTargetPos);
	}

	_agent->SetColor(GREEN);
	return Composite::Success;
}
