#pragma once
#include <raylib/raylib.h>

#include "Behaviour.h"
#include "PathAgent.h"
#include "Selector.h"

class Behaviour;
class NodeMap;

class Agent
{
public:	
	Agent(NodeMap* _nodeMap, Behaviour* _behaviour, Color _color, int _speed);
		
	~Agent();

	virtual void Load();
	virtual void Update(float _dt);
	virtual void Draw();
	
	void GoTo(vec2 _point);
	
	bool PathComplete() { return GetPath().empty(); }
	void SetCurrentNode(Node* _node) { m_pathAgent.currentNode = _node; }
	void SetTarget(Agent* _agent) { m_pathAgent.target = _agent; }
	void SetColor(Color _color) { m_pathAgent.color = _color; }
	void SetPos(vec2 _pos) { m_pathAgent.SetPos(_pos); }
	
	void Reset() { GetPath().clear(); }

	
	vector<Node*> GetPath() { return m_pathAgent.GetPath(); }
	vec2 GetPos() { return m_pathAgent.GetPos(); }
	Node* GetCurrentNode() { return m_pathAgent.GetCurrentNode(); }
	PathAgent* GetPathAgent() { return &m_pathAgent; }
	NodeMap* GetMap() { return m_map; }	
	Agent* GetTarget() { return m_pathAgent.target; }

private:
	Behaviour* m_behaviours;
	PathAgent m_pathAgent;
	NodeMap* m_map;
};