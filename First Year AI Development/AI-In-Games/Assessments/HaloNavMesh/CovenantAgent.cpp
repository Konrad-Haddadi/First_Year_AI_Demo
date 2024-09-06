#include "CovenantAgent.h"
#include "Agent.h"
#include "Spartan.h"
#include "INavigatable.h"
#include "HashTable.h"
#include "PassiveTree.h"
#include <Azimuth/GameObjects/ATransform.h>

CovenantAgent::CovenantAgent(vec2 _pos, HashTable* _table, const char* _name, INavigatable* _map, int _type, int _speed, GameStateManager* _gsMan, GameObjectManager* _goMan)
	: Agent(_name, _map, _table, new PassiveTree, _speed, GetTypeColor(_type), _gsMan, _goMan),m_type(_type), enemyColor(RED), fleeing(false)
{
	m_texture = Resources::Find<Texture2D, TextureResource>("textures/" + (string)GetTypeName(_type));
	Transform()->TRS(_pos, 0, { 1,1 });
	SetPos(_pos + vec2{ 5, 5});
}

CovenantAgent::CovenantAgent(vec2 _pos, HashTable* _table, INavigatable* _map, int _type, int _speed, GameStateManager* _gsMan, GameObjectManager* _goMan)
	: Agent(GetTypeName(_type), _map, _table, new PassiveTree, _speed, GetTypeColor(_type), _gsMan, _goMan), m_type(_type), enemyColor(RED), fleeing(false)
{
	m_texture = Resources::Find<Texture2D, TextureResource>("textures/" + (string)GetTypeName(_type));
	Transform()->TRS(_pos, 0, { 1,1 });
	SetPos(_pos + vec2{5, 5});
}

CovenantAgent::~CovenantAgent()
{
	m_table->RemoveFromQuad(this);
	delete m_current;
	delete m_next;	

	m_current = nullptr;
	m_next = nullptr;
	m_table = nullptr;
	m_map = nullptr;
	m_spartan = nullptr;
}

void CovenantAgent::Load()
{	
	m_table->AddToQuad(0, this);
	m_steeringAgent.currentQuad = m_currentQuad;
}

void CovenantAgent::Update(float _dt)
{
	if (m_current)
		m_current->Update(this, _dt);

	m_pathAgent.Update(_dt);

	if (!PathComplete())
	{
		vec2 dir = glm::normalize(m_pathAgent.GetPos() - Transform()->Position());
		float rot = glm::atan(dir.y, dir.x);

		Transform()->SetRotation(rot);
	}

	m_steeringAgent.Update(_dt);

	if (m_next)
	{
		Behaviour* temp = &*m_current;
		m_current = m_next;
		delete temp;

		temp = nullptr;
		m_next = nullptr;
	}

	if (m_table->HasMoved(m_currentQuad, this))
	{
		m_currentQuad = m_table->UpdateQuad(this);
		m_steeringAgent.currentQuad = m_currentQuad;
	}
}

void CovenantAgent::Draw()
{
	m_pathAgent.Draw();
		
	DrawText(GetName(), Transform()->Position().x - TextLength(GetName()) + 1, Transform()->Position().y - 19, 15, BLACK);
	DrawText(GetName(), Transform()->Position().x - TextLength(GetName()) + 1, Transform()->Position().y - 20, 15, m_pathAgent.color);	

	if (fleeing)
	{
		DrawText("!", Transform()->Position().x + 1, Transform()->Position().y - 19, 15, BLACK);
		DrawText("!", Transform()->Position().x + 1, Transform()->Position().y - 20, 15, m_pathAgent.color);
	}

	if (IsKeyUp(KEY_GRAVE))
	{
		DrawTextureEx(*m_texture, { Transform()->Position().x, Transform()->Position().y}, 0, 0.45f, WHITE);	

		vector<vec2> tri = m_steeringAgent.GetTrianglePoints();

		DrawTriangle({ tri[0].x,tri[0].y }, { tri[1].x,tri[1].y }, { tri[2].x,tri[2].y }, { 100,100,150,100 });

		return;
	}

	for (auto a : m_squad)
	{
		DrawLineEx({ Transform()->Position().x + 5, Transform()->Position().y + 5 },
			{ a->Transform()->Position().x + 5, a->Transform()->Position().y + 5 }, 2, PINK);
	}

	if (GetSpartanTarget())
	{
		vec2 player = GetSpartanTarget()->Transform()->Position();
		DrawLineEx({ Transform()->Position().x + 5, Transform()->Position().y + 5 }, { player.x + 5, player.y + 5 }, 2, enemyColor);
	}

	m_steeringAgent.Draw();

}


Color CovenantAgent::GetTypeColor(int _type)
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


const char* CovenantAgent::GetTypeName(int _type)
{
	switch (_type)
	{
	case Grunt:
		return "Grunt";

	case GruntC:
		return "GruntC";

	case Elite:
		return "Elite";

	case EliteC:
		return "EliteC";
	}
}

int CovenantAgent::CheckSquadSize()
{
	int val = 0;

	for (auto covenant : m_squad)
	{
		val += covenant->GetRank() + 1;
		val += covenant->CheckSquadSize();
	}

	return val;
}
