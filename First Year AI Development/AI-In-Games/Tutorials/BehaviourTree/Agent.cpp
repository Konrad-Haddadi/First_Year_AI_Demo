#include "Agent.h"
#include "Behaviour.h"
#include "PathAgent.h"
#include "NodeMap.h"
#include "Node.h"

#include <raylib/raylib.h>

Agent::Agent(NodeMap* _nodeMap, Behaviour* _behaviour, Color _color, int _speed)
	:  m_map(_nodeMap), m_pathAgent(_color, _speed) 
{
	if(_behaviour)
		m_behaviours.children.push_back(_behaviour);
}

Agent::~Agent()
{
	for (int i = 0; i < m_behaviours.children.size(); i++)
	{
		delete m_behaviours.children[i];
	}	
}

void Agent::Load()
{
	m_behaviours.Enter(this);	
}

void Agent::Update(float _dt)
{
	m_behaviours.Update(this, _dt);
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

	if(end)
		m_pathAgent.GoToNode(end);
}
