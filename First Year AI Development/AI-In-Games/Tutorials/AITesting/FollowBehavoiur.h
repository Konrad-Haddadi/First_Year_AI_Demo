#pragma once

#include <glm/vec2.hpp>
#include "Behaviour.h"
#include "Node.h"

using glm::vec2;
using AITesting::Node;

class FollowBehavoiur : public Behaviour
{
public:
	virtual void Enter(Agent* _agent) override;
	virtual void Update(Agent* _agent, float _dt) override;
	virtual void Exit(Agent* _agent) override;
	
	vec2 lastTargetPos;
};

