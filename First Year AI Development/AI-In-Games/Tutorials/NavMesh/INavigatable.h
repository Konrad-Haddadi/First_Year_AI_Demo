#pragma once

#include "NavMeshNode.h"
#include <glm/vec2.hpp>

class PathAgent;

class INavigatable
{
public:
	virtual void Draw() = 0;
	virtual NavMeshNode* GetClosestNode(vec2 _worldPos) = 0;

	virtual float GetCellSize() { return 32; }
	virtual NavMeshNode* GetRandomNode() = 0;
	virtual void SmoothPath(PathAgent* _agent, vec2 _end) = 0;

	
};

