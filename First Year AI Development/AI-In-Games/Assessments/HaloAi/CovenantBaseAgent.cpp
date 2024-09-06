#include "CovenantBaseAgent.h"
#include "PassiveTree.h"
#include "Agent.h"
#include "SpartanAgent.h"


CovenantBaseAgent::CovenantBaseAgent(HashTable* _table, const char* _name,  NodeMap* _map, int _type, int _speed, GameStateManager* _gsMan, GameObjectManager* _goMan)
	: Agent(_name, _map, new PassiveTree, ((_type * 50) / 2 + 50, _type), GetTypeColor(_type), _gsMan, _goMan), m_table(_table), m_type(_type), enemyColor(RED), fleeing(false)
{

}

CovenantBaseAgent::CovenantBaseAgent(HashTable* _table, NodeMap* _map, int _type, int _speed, GameStateManager* _gsMan, GameObjectManager* _goMan)
	: Agent(GetTypeName(_type), _map, new PassiveTree, ((_type * 50) / 2 + 50, _type), GetTypeColor(_type), _gsMan, _goMan), m_table(_table), m_type(_type), enemyColor(RED), fleeing(false)
{

}

CovenantBaseAgent::~CovenantBaseAgent()
{
	delete m_behaviour;
}

void CovenantBaseAgent::Load()
{
	m_table->AddToQuad(0, this);
	SetSpeed(GetBaseSpeed());
}

void CovenantBaseAgent::Update(float _dt)
{
	if(m_behaviour)
		m_behaviour->Update(this, _dt);

	m_pathAgent.Update(_dt);

	if (m_table->HasMoved(m_currentQuad, this))
		m_currentQuad = m_table->UpdateQuad(this);		
}

void CovenantBaseAgent::Draw()
{
	m_pathAgent.Draw();
	DrawText(GetName(), m_pathAgent.pos.x - TextLength(GetName()) + 1, m_pathAgent.pos.y - 19, 15, BLACK);
	DrawText(GetName(), m_pathAgent.pos.x - TextLength(GetName()) + 1, m_pathAgent.pos.y - 20, 15, m_pathAgent.color);

	if (GetTargetEnemy())
	{
		DrawText("!", GetPos().x + 10, GetPos().y - 6, 30, BLACK);
		DrawText("!", GetPos().x + 9, GetPos().y - 5, 30, YELLOW);
	}

	if (!m_pathAgent.devMode)
		return;

	for (auto a : m_squad)
	{
		DrawLineEx({ GetPos().x + 10, GetPos().y + 10 }, { a->GetPos().x + 10, a->GetPos().y + 10 }, 2, BLUE);
	}

	if (GetTargetEnemy())
	{
		vec2 player = GetTargetEnemy()->GetPos();
		DrawLineEx({ GetPos().x + 10, GetPos().y + 10 }, { player.x + 10, player.y + 10 }, 2, enemyColor);
	}

	Rectangle quad = GetHashTable()->GetQuad(m_currentQuad);
	DrawLineEx({ GetPos().x + 10, GetPos().y + 10 }, { quad.x + quad.width / 2, quad.y + quad.height / 2 }, 3, GREEN);		
}


Color CovenantBaseAgent::GetTypeColor(int _type)
{
	switch (_type)
	{
	case Grunt:
		return ORANGE;

	case GruntC:
		return RED;

	case Elite:
		return BLUE;

	case EliteC:
		return	PURPLE;
	}
}


const char* CovenantBaseAgent::GetTypeName(int _type)
{
	switch (_type)
	{
	case Grunt:
		return "Grunt";
	
	case GruntC:
		return "Grunt Commander";

	case Elite:
		return "Elite";

	case EliteC:
		return "Elite Commander";
	}
}