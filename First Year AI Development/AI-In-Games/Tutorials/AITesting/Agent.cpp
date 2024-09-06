#include "Agent.h"
#include "Behaviour.h"
#include "PathAgent.h"
#include "NodeMap.h"
#include "Node.h"

#include <raylib/raylib.h>

Agent::Agent(NodeMap* _nodeMap, Behaviour* _behaviour, Color _color, int _speed)
	: m_current(_behaviour), m_map(_nodeMap), m_pathAgent(_color, _speed) 
{
	
}

void Agent::Load()
{
	m_current->Enter(this);
}

void Agent::Update(float _dt)
{
	m_current->Update(this, _dt);
	m_pathAgent.Update(_dt);
}

void Agent::Draw()
{
	m_pathAgent.Draw();
}

void Agent::GoTo(vec2 _point)
{
	Node* end = nullptr;
	end = m_map->GetClosestNode(_point);
	m_pathAgent.GoToNode(end);
}
