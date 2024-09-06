#pragma once

#include "Node.h"
#include <glm/vec2.hpp>
#include <vector>
#include <raylib/raylib.h>


using std::vector;
using glm::vec2;
using AITesting::Node;

class Agent;

class PathAgent
{
public:
	PathAgent(Color _color, int _speed);
	~PathAgent();

	void SetPos(vec2 _pos) { pos = _pos; }
	void Update(float _dt);
	void GoToNode(Node* _end);
	void Draw();

	void SetTarget(Agent* _agent) { target = _agent; }

	vec2 GetPos() { return pos; }	
	Node* GetCurrentNode() { return currentNode;  }
	vector<Node*> GetPath() { return path; }
	
	vector<Node*> Dijkstras(Node* _start, Node* _end);

	bool IsEmpty() { return path.empty(); }
	
	Node* currentNode;
	Agent* target;
	Color color;

private:
	int currentIndex;
	float speed;

	vec2 pos;
	vector<Node*> path;
};