#pragma once
#include <raylib/raylib.h>

#include "PathAgent.h"

class Behaviour;
class NodeMap;

class Agent
{
public:	
	Agent(NodeMap* _nodeMap, Behaviour* _behaviour, Color _color, int _speed);
		
	~Agent() { delete m_current;  }

	void Load();
	void Update(float _dt);
	void Draw();
	
	void GoTo(vec2 _point);
	
	bool PathComplete() { return GetPath().empty(); }
	void SetCurrentNode(Node* _node) { m_pathAgent.currentNode = _node; }
	void SetTarget(Agent* _agent) { m_pathAgent.target = _agent; }
	void SetColor(Color _color) { m_pathAgent.color = _color; }
	void SetBehaviour(Behaviour* _b) { m_current = _b; }
	void Reset() { GetPath().clear(); }

	vector<Node*> GetPath() { return m_pathAgent.GetPath(); }
	vec2 GetPos() { return m_pathAgent.GetPos(); }

	Behaviour* GetBehaviour() { return m_current; }
	PathAgent* GetPathAgent() { return &m_pathAgent; }
	NodeMap* GetNodeMap() { return m_nodeMap; }	
	Agent* GetTarget() { return m_pathAgent.target; }

private:
	PathAgent m_pathAgent;
	Behaviour* m_current;
	NodeMap* m_nodeMap;
};