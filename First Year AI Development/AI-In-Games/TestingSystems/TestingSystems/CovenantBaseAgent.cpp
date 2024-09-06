#include "CovenantBaseAgent.h"
#include "WanderBehaviour.h"
#include "Agent.h"
#include "SpartanAgent.h"
#include "QuadTree.h"


CovenantBaseAgent::CovenantBaseAgent(const char* _name, QuadTree* _quadTree, NodeMap* _map, int _type, int _speed, GameStateManager* _gsMan, GameObjectManager* _goMan)
	: Agent(_name, _quadTree, _map, new WanderBehaviour, ((_type * 50) / 2 + 50, _type), GetTypeColor(_type), _gsMan, _goMan), m_table(nullptr), m_type(_type), enemyColor(RED), fleeing(false)
{

}

CovenantBaseAgent::CovenantBaseAgent(QuadTree* _quadTree, NodeMap* _map, int _type, int _speed, GameStateManager* _gsMan, GameObjectManager* _goMan)
	: Agent(GetTypeName(_type), _quadTree, _map, new WanderBehaviour, ((_type * 50) / 2 + 50, _type), GetTypeColor(_type), _gsMan, _goMan), m_table(nullptr), m_type(_type), enemyColor(RED), fleeing(false)
{

}

CovenantBaseAgent::~CovenantBaseAgent()
{
	delete m_behaviour;
}

void CovenantBaseAgent::Load()
{
	//m_table->AddToQuad(0, this);
	m_currentQuad = m_quadTree->GetRoot();
	SetSpeed(GetBaseSpeed());
}

void CovenantBaseAgent::Update(float _dt)
{
	if(m_behaviour)
		m_behaviour->Update(this, _dt);

	m_pathAgent.Update(_dt);
	m_currentQuad = m_quadTree->UpdateQuad(this);
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

	if (m_currentQuad)
	{
		Rectangle quad = m_currentQuad->GetBounds();
		DrawLineEx({ GetPos().x + 10, GetPos().y + 10 }, { quad.x + quad.width / 2, quad.y + quad.height / 2 }, 3, GREEN);
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