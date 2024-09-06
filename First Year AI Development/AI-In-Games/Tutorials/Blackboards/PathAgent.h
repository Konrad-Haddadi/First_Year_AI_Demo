#pragma once

#include <glm/vec2.hpp>
#include <vector>
#include <raylib/raylib.h>

class Node;
class NodeMap;
class CovenantBaseAgent;

using std::vector;
using glm::vec2;

class PathAgent
{
public:
	PathAgent(NodeMap* _map, int _speed, Color _color);
	~PathAgent();

	void Update(float _dt);
	void GoToNode(Node* _end);
	void Draw();
	
	vector<Node*> AStarSearch(Node* _start, Node* _end);
	
	bool IsEmpty() { return path.empty(); }
public:
	Color color;
	int currentIndex;	

	bool devMode;

	float speed;
	NodeMap* map;

	CovenantBaseAgent* target;
	vec2 currentNode;
	vector<Node*> path;
	vec2 pos;
};
	