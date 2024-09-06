#pragma once

#include <glm/vec2.hpp>
#include "Behaviour.h"

using glm::vec2;

class FollowBehavoiur : public Behaviour
{
public:
	virtual void Enter(Agent* _agent) override;
	virtual void Update(Agent* _agent, float _dt) override;
	virtual void Exit(Agent* _agent) override;
	
	vec2 lastTargetPos;
};

