#pragma once

#include "../Core/Nodes/NavMesh.h"
#include "../Core/Nodes/INavigatable.h"
#include <glm/vec2.hpp>
#include <vector>
#include <raylib/raylib.h>
#include <Azimuth/GameObjects/ATransform.h>

using std::vector;
using glm::vec2;

class Agent;
class CovenantAgent;

class PathAgent
{
public:
	PathAgent(ATransform* _transform, Color _color, int _speed, INavigatable* _nodeMap);
	~PathAgent();

	void Update(float _dt);
	void GoToNode(vec2 _end);
	void Draw();

	vector<NavMeshNode*> AStarSearch(NavMeshNode* _start, NavMeshNode* _end);
	bool IsEmpty() { return m_path.empty(); }
	void Reset() { m_path.clear(); m_smoothPath.clear(); }

	// Setters
	void SetPos(vec2 _pos) { m_pos = _pos; m_currentNode = _pos; }
	void SetTarget(CovenantAgent* _agent) { m_target = _agent; }
	void SetCurrentIndex(int _num) { m_currentIndex = _num; }
	void SetPath(vector<NavMeshNode*> _path) { m_path = _path; }
	void SetSpeed(int _speed) { m_speed = _speed; }

	// Getters
	CovenantAgent* GetTarget() { return m_target;  }
	vec2 GetVelocity() { return m_velocity; }
	vec2 GetPos() { return m_pos; }	
	vec2 GetCurrentNode() { return m_currentNode;  }
	vector<NavMeshNode*>& GetPath() { return m_path; }
	vector<vec2>& GetSmoothPath() { return m_smoothPath; }
	int GetSpeed() { return m_speed;  }

public:
	Color color;

private:
	CovenantAgent* m_target;
	INavigatable* m_nodeMap;
	ATransform* m_transform;

	vec2 m_currentNode;
	vec2 m_velocity;
	int m_currentIndex;
	float m_speed;
	vec2 m_pos;
	vector<NavMeshNode*> m_path;
	vector<vec2> m_smoothPath;
};