#include "Agent.h"
#include "PathAgent.h"
#include "NodeMap.h"
#include "Node.h"

#include <raylib/raylib.h>

Agent::Agent(NodeMap* _nodeMap, Color _color, int _speed)
	:  m_nodeMap(_nodeMap), m_pathAgent(_color, _speed, _nodeMap)
{
	
}

void Agent::Load()
{
	
}

void Agent::Update(float _dt)
{
	m_pathAgent.Update(_dt);
}

void Agent::Draw()
{
	m_pathAgent.Draw();
}

void Agent::GoTo(vec2 _point)
{
	Node* end = nullptr;
	end = m_nodeMap->GetClosestNode(_point);
	m_pathAgent.GoToNode(end);
}
