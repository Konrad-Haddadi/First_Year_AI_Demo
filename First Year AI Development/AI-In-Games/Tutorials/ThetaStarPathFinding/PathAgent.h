#pragma once

#include "Node.h"
#include <glm/vec2.hpp>
#include <vector>
#include <raylib/raylib.h>
#include "NodeMap.h"

using std::vector;
using glm::vec2;
using AITesting::Node;

class Agent;

class PathAgent
{
public:
	PathAgent(NodeMap* _map, Color _color, int _speed);
	~PathAgent();

	void SetPos(vec2 _pos) { m_pos = _pos; }
	void Update(float _dt);
	void GoToNode(Node* _end);
	void Draw();

	void SetTarget(Agent* _agent) { target = _agent; }

	vec2 GetPos() { return m_pos; }	
	vec2 GetCurrentNode() { return currentNode;  }
	vector<vec2> GetPath() { return m_smoothPath; }
	vector<Node*> AStarSearch(Node* _start, Node* _end);

	bool LineOfSight(vec2 _lhs, vec2 _rhs);
	bool IsEmpty() { return m_smoothPath.empty(); }

	vector<vec2> GetSmoothPath(vector<Node*> _path);
	float DistHeuristic(vec2 _posA, vec2 _posB);
	float ManHattanHeuristic(vec2 _posA, vec2 _posB);
	float ManHattan8WayHeuristic(Node* _current, Node* _end);
	
	vec2 currentNode;
	Agent* target;
	Color color;

private:
	int m_currentIndex;
	float m_speed;
	NodeMap* m_nodeMap;
	vec2 m_pos;
	vector<vec2> m_smoothPath;
	vector<Node*> m_path;
};