#pragma once

#include <glm/vec2.hpp>
#include "Behaviour.h"

using glm::vec2;

class FollowSpartanBehaviour : public Behaviour
{
public:
	FollowSpartanBehaviour() : lastTargetPos({ 0,0 }) { };

	virtual int Update(CovenantAgent* _agent, float _dt) override;
	virtual int Update(Agent* _agent, float _dt) override;

public:
	vec2 lastTargetPos;

	
};

