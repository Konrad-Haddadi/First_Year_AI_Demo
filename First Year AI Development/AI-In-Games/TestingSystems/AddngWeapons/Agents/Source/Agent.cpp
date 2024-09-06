#include "../Agent.h"
#include "../../Behaviour/Behaviour.h"
#include "../PathAgent.h"
#include "../../Core/Nodes/NavMesh.h"
#include "../../Core/Nodes/INavigatable.h"

#include <raylib/raylib.h>

#include <Azimuth/GameObjects/GameObject.h>
#include <Azimuth/GameObjects/GameObjectManager.h>
#include <Azimuth/GameStates/GameStateManager.h>

Agent::Agent(const char* _name, INavigatable* _map, HashTable* _table, Behaviour* _behaviour, int _speed, Color _color, GameStateManager* _gsMan, GameObjectManager* _goMan)
	: GameObject(_name, _gsMan, _goMan), m_table(_table), m_map(_map), m_current(_behaviour), m_next(nullptr), m_pathAgent(Transform(),_color, _speed, _map),
	m_spartan(nullptr), m_currentQuad(0), m_rotation(0), m_steeringAgent(Transform(), _table, m_currentQuad)
{

}

Agent::~Agent()
{
	delete m_current;
	delete m_next;

	m_current = nullptr;
	m_next = nullptr;
	m_table = nullptr;
	m_map = nullptr;
	m_spartan = nullptr;
}

void Agent::Load()
{
	Transform()->SetPosition(m_pathAgent.GetPos());
}

void Agent::Update(float _dt)
{
	m_current->Update(this, _dt);
	m_pathAgent.Update(_dt);

	m_currentQuad = m_table->CheckQuad(Transform()->Position());
	m_steeringAgent.currentQuad = m_currentQuad;
	
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
