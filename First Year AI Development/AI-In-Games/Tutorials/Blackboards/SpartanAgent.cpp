#include "SpartanAgent.h"
#include "Agent.h"
#include "Behaviour.h"

SpartanAgent::SpartanAgent(const char* _name, HashTable* _table, NodeMap* _map, Behaviour* _behaviour, int _speed, Color _color, GameStateManager* _gsMan, GameObjectManager* _goMan)
	: Agent(_name, _map, _behaviour, _speed, _color, _gsMan, _goMan), m_table(_table), m_currentQuad(0)
{

}

SpartanAgent::~SpartanAgent()
{
	delete m_behaviour;
}

void SpartanAgent::Load()
{
	m_table->AddToQuad(0, this);
}

void SpartanAgent::Update(float _dt)
{
	if (m_behaviour)
		m_behaviour->Update(this, _dt);

	m_pathAgent.Update(_dt);

	if (m_table->HasMoved(m_currentQuad, this))
		m_currentQuad = m_table->UpdateQuad(this);
}

void SpartanAgent::Draw()
{
	m_pathAgent.Draw();
	DrawText(GetName(), m_pathAgent.pos.x - TextLength(GetName()) + 1, m_pathAgent.pos.y - 19, 15, BLACK);
	DrawText(GetName(), m_pathAgent.pos.x - TextLength(GetName()) + 1, m_pathAgent.pos.y - 20, 15, m_pathAgent.color);
	

	if (m_pathAgent.devMode)
	{
		Rectangle quad = GetHashTable()->GetQuad(m_currentQuad);
		DrawLineEx({ GetPos().x + 10, GetPos().y + 10 }, { quad.x + quad.width / 2, quad.y + quad.height / 2 }, 3, GREEN);
	}	
}