#include "Agent.h"
#include "Behaviour.h"
#include "PathAgent.h"
#include "NavMesh.h"

#include <raylib/raylib.h>

Agent::Agent(INavigatable* _nodeMap, Behaviour* _behaviour, Color _color, int _speed)
	: m_current(_behaviour), m_map(_nodeMap), m_pathAgent(_color, _speed, _nodeMap) 
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
	NavMeshNode* end = m_map->GetClosestNode(_point);

	if (CheckCollisionPointTriangle({ _point.x, _point.y }, { end->verticies[0].x, end->verticies[0].y }, { end->verticies[1].x, end->verticies[1].y },
		{ end->verticies[2].x, end->verticies[2].y }))
	{
		m_pathAgent.GoToNode(_point);
	}
	else
		m_pathAgent.GoToNode(end->pos);

	
}
