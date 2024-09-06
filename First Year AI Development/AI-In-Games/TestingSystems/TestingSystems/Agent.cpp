#include "Agent.h"
#include "Behaviour.h"
#include "GotoPointBehaviour.h"
#include "NodeMap.h"

#include <Azimuth/GameObjects/GameObject.h>

Agent::Agent(const char* _name, QuadTree* _quadTree, NodeMap* _map, Behaviour* _behaviour, int _speed, Color _color, GameStateManager* _gsMan, GameObjectManager* _goMan)
	: GameObject(_name, _gsMan, _goMan), m_quadTree(_quadTree), m_map(_map), m_behaviour(_behaviour), m_pathAgent(_map, _speed, _color), m_spartan(nullptr), m_next(nullptr)
{

}

Agent::~Agent()
{
	delete m_behaviour;
}

void Agent::Load()
{
}

void Agent::Update(float _dt)
{
	if (m_behaviour)
		m_behaviour->Update(this, _dt);

	m_pathAgent.Update(_dt);	
}

void Agent::Draw()
{
	m_pathAgent.Draw();
	DrawText(GetName(), m_pathAgent.pos.x - TextLength(GetName()) + 1, m_pathAgent.pos.y - 19, 15, BLACK);
	DrawText(GetName(), m_pathAgent.pos.x - TextLength(GetName()) + 1, m_pathAgent.pos.y - 20, 15, m_pathAgent.color);	


}

void Agent::GoTo(vec2 _point)
{
	Node* end = nullptr;
	end = m_map->GetClosestNode(_point);

	if (end)
		m_pathAgent.GoToNode(end);
}

void Agent::SetBehaviour(Behaviour* _b)
{
	Behaviour* temp = nullptr;

	*temp = *m_behaviour;
	m_behaviour = _b; 

	delete temp;
	temp = nullptr;
}