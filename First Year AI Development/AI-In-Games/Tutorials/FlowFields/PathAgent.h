#pragma once

#include "Node.h"
#include <glm/vec2.hpp>
#include <vector>
#include <raylib/raylib.h>


using std::vector;
using glm::vec2;
using AITesting::Node;

class NodeMap;
class Agent;

class PathAgent
{
public:
	PathAgent(Color _color, int _speed, NodeMap* _nodeMap);
	~PathAgent();

	void SetPos(vec2 _pos) { pos = _pos; }
	void Update(float _dt);
	void GoToNode(Node* _end);
	void Draw();

	vec2 GetPos() { return pos; }	
	vec2 GetCurrentNode() { return dir;  }

	
	vec2 dir;
	Color color;
	NodeMap* nodeMap;

	int currentIndex;
	float speed;
	vec2 pos;
	
};