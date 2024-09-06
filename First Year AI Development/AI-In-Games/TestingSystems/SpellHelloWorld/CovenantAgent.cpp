#include "CovenantAgent.h"
#include "Agent.h"
#include "Spartan.h"
#include "INavigatable.h"
#include "HashTable.h"
#include "PassiveTree.h"
#include <Azimuth/GameObjects/ATransform.h>

CovenantAgent::CovenantAgent(string _targetWord, vec2 _pos, HashTable* _table, const char* _name, INavigatable* _map, int _type, int _speed, GameStateManager* _gsMan, GameObjectManager* _goMan)
	: Agent(_name, _map, _table, new PassiveTree, _speed, GetTypeColor(_type), _gsMan, _goMan),m_type(_type), enemyColor(RED), fleeing(false), m_targetWord(_targetWord), match(false)
{
	m_texture = Resources::Find<Texture2D, TextureResource>("textures/" + (string)GetTypeName(_type));
	Transform()->TRS(_pos, 0, { 1,1 });
	SetPos(_pos + vec2{ 5, 5});
}

CovenantAgent::CovenantAgent(string _targetWord, vec2 _pos, HashTable* _table, INavigatable* _map, int _type, int _speed, GameStateManager* _gsMan, GameObjectManager* _goMan)
	: Agent(GetTypeName(_type), _map, _table, new PassiveTree, _speed, GetTypeColor(_type), _gsMan, _goMan), m_type(_type), enemyColor(RED), fleeing(false), m_targetWord(_targetWord), match(false)
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
	if (m_letters.size() >= m_targetWord.size())
		m_letters.clear();

	if (m_current)
		m_current->Update(this, _dt);

	m_pathAgent.Update(_dt);

	if (!PathComplete())
	{
		vec2 dir = glm::normalize(m_pathAgent.GetPos() - Transform()->Position());
		float rot = glm::atan(dir.y, dir.x);

		Transform()->SetRotation(rot);
	}

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

		int randLetter = GetRandomValue(0, 100);

		while(randLetter >= m_table->GetLetters(m_currentQuad)->size() || randLetter < 0)
			randLetter = GetRandomValue(0, m_table->GetLetters(m_currentQuad)->size() - 1);

		
		m_letters.push_back((*m_table->GetLetters(m_currentQuad))[randLetter]);		
		m_table->RefreshQuad(m_currentQuad);
	}

	if (m_letters.size() >= m_targetWord.size())
	{
		string result = "";
		string goal = "";
		for (int i = 0; i < m_letters.size(); i++)
			result += m_letters[i];	

		for (int j = 0; j < m_targetWord.size(); j++)
		{
			for (int i = 0; i < result.size(); i++)
			{			
				if (tolower(result[i]) == tolower(m_targetWord[j]))
					goal += result[i];
			}			
		}

		if (goal == m_targetWord)
			match = true;
		
	}
}

void CovenantAgent::Draw()
{
	m_pathAgent.Draw();
		
	DrawText(GetName(), Transform()->Position().x - TextLength(GetName()) + 1, Transform()->Position().y - 19, 15, BLACK);
	DrawText(GetName(), Transform()->Position().x - TextLength(GetName()) + 1, Transform()->Position().y - 20, 15, m_pathAgent.color);	

	if (match)
		DrawText(m_targetWord.c_str(), 400, 400, 100, PINK);
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
