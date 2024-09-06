#pragma once
#include <raylib/raylib.h>

#include "PathAgent.h"

class Behaviour;
class NodeMap;

class Agent
{
public:	
	Agent(NodeMap* _nodeMap, Color _color, int _speed);
		
	~Agent() {  }

	void Load();
	void Update(float _dt);
	void Draw();	
	void GoTo(vec2 _point);	
	void SetColor(Color _color) { m_pathAgent.color = _color; }
	void SetPos(vec2 _pos) { m_pathAgent.pos = _pos; }

	vec2 GetPos() { return m_pathAgent.GetPos(); }
	PathAgent* GetPathAgent() { return &m_pathAgent; }
	NodeMap* GetNodeMap() { return m_nodeMap; }	

private:
	PathAgent m_pathAgent;
	NodeMap* m_nodeMap;
};