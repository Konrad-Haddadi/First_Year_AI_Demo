#pragma once

#include "NavMeshNode.h"
#include "INavigatable.h"
#include "Line.h"
#include <glm/vec2.hpp>
#include <vector>
#include <raylib/raylib.h>


using std::vector;
using glm::vec2;

class Agent;

class PathAgent
{
public:
	PathAgent(Color _color, int _speed, INavigatable* _nodeMap);
	~PathAgent();

	void Update(float _dt);
	void GoToNode(vec2 _end);
	void Draw();

	vector<NavMeshNode*> AStarSearch(NavMeshNode* _start, NavMeshNode* _end);
	bool IsEmpty() { return m_path.empty(); }
	void Reset() { m_path.clear(); m_smoothPath.clear(); }
	// Setters
	void SetPos(vec2 _pos) { pos = _pos; currentNode = _pos; }
	void SetTarget(Agent* _agent) { target = _agent; }
	void SetCurrentIndex(int _num) { currentIndex = _num; }
	void SetPath(vector<NavMeshNode*> _path) { m_path = _path; }
	void SetPortalPath(vector<Line> _portals) { m_portals = _portals; }
	// Getters
	Agent* GetTarget() { return target;  }
	vec2 GetPos() { return pos; }	
	vec2 GetCurrentNode() { return currentNode;  }
	vector<NavMeshNode*>& GetPath() { return m_path; }
	vector<vec2>& GetSmoothPath() { return m_smoothPath; }
	bool CanSeePoint();

public:
	Color color;

private:
	Agent* target;
	INavigatable* m_nodeMap;

	vec2 currentNode;
	int currentIndex;
	float speed;

	vec2 pos;
	vector<NavMeshNode*> m_path;
	vector<Line> m_portals;
	vector<vec2> m_smoothPath;
};