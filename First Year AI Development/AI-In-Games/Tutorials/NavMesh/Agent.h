#pragma once
#include <raylib/raylib.h>

#include "PathAgent.h"


class Behaviour;
class INavigatable;

class Agent
{
public:	
	Agent(INavigatable* _nodeMap, Behaviour* _behaviour, Color _color, int _speed);
		
	~Agent() { delete m_current;  }

	void Load();
	void Update(float _dt);
	void Draw();
	
	void GoTo(vec2 _point);
	
	void SetCurrentNode(vec2 _node) { m_pathAgent.GetCurrentNode() = _node; }
	void SetTarget(Agent* _agent) { m_pathAgent.SetTarget(_agent); }
	void SetColor(Color _color) { m_pathAgent.color = _color; }
	void SetBehaviour(Behaviour* _b) { m_current = _b; }
	void SetPos(vec2 _pos) { m_pathAgent.SetPos(_pos); }
	void Reset() { GetSmoothPath().clear(); }

	bool PathComplete() { return GetPath().empty(); }

	vector<vec2> GetSmoothPath() { return m_pathAgent.GetSmoothPath(); }
	vec2 GetPos() { return m_pathAgent.GetPos(); }
	vector<NavMeshNode*> GetPath() { return m_pathAgent.GetPath(); }

	Behaviour* GetBehaviour() { return m_current; }
	PathAgent* GetPathAgent() { return &m_pathAgent; }
	INavigatable* GetMap() { return m_map; }
	Agent* GetTarget() { return m_pathAgent.GetTarget(); }

private:
	PathAgent m_pathAgent;
	Behaviour* m_current;
	INavigatable* m_map;
};