#include "Agent.h"
#include "Behaviour.h"
#include "PathAgent.h"
#include "NodeMap.h"
#include "Node.h"

#include <raylib/raylib.h>

Agent::Agent(NodeMap* _nodeMap, Behaviour* _behaviour, Color _color, int _speed)
	:  m_map(_nodeMap), m_pathAgent(_nodeMap, _color, _speed), m_behaviours(_behaviour)
{
	
}

Agent::~Agent()
{	
	delete m_behaviours;	
}

void Agent::Load()
{
	m_behaviours->Enter(this);	
}

void Agent::Update(float _dt)
{
	m_behaviours->Update(this, _dt);
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
