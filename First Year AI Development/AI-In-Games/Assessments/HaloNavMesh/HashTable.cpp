#include "HashTable.h"
#include "Agent.h"
#include "CovenantAgent.h"
#include "Spartan.h"
#include <raylib/raylib.h>
#include <Azimuth/GameObjects/ATransform.h>
#include "NavMesh.h"

HashTable::HashTable(NavMesh* _navMesh) : m_navMesh(_navMesh)
{
}

HashTable::~HashTable()
{
	for (int i = 0; i < m_covenantTable.size(); i++)
	{
		for (int j = 0; j < m_covenantTable[i].size(); j++)
		{
			m_covenantTable[i].clear();
			m_spartanTable[i].clear();
			m_objectTable[i].clear();
		}
	}
}

void HashTable::Load()
{
	for (float y = 0; y < 5; y++)
	{
		for (float x = 0; x < 8; x++)
		{
			m_covenantTable.push_back(list<CovenantAgent*>());
			m_spartanTable.push_back(list<Spartan*>());
			m_objectTable.push_back(list<Rectangle>());
			m_quadrents.push_back({ 200 * x, 200 * y, 200, 200 });
		}
	}

	for (int i = 0; i < m_navMesh->GetObstacles().size(); i++)
	{
		UpdateQuad(m_navMesh->GetObstacles()[i].rect);
	}
}

int HashTable::CheckQuad(vec2 _point)
{
	int val = 0;

	for (int i = 0; i < m_quadrents.size(); i++)
	{
		if (CheckCollisionPointRec({ _point.x, _point.y }, m_quadrents[i]))
		{
			val = i;
		}
	}

	return val;
}

int HashTable::UpdateQuad(CovenantAgent* _agent)
{
	int val = 0;

	for (int i = 0; i < m_quadrents.size(); i++)
	{	
		if (std::find(m_covenantTable[i].begin(), m_covenantTable[i].end(), _agent) != m_covenantTable[i].end())
			m_covenantTable[i].remove(_agent);

		if (CheckCollisionPointRec({ _agent->Transform()->Position().x, _agent->Transform()->Position().y }, m_quadrents[i]))
		{
			m_covenantTable[i].push_back(_agent);
			val = i;
		}
	}

	return val;
}

int HashTable::UpdateQuad(Spartan* _agent)
{
	int val = 0;

	for (int i = 0; i < m_quadrents.size(); i++)
	{
		if (std::find(m_spartanTable[i].begin(), m_spartanTable[i].end(), _agent) != m_spartanTable[i].end())
			m_spartanTable[i].remove(_agent);

		if (CheckCollisionPointRec({ _agent->Transform()->Position().x, _agent->Transform()->Position().y }, m_quadrents[i]))
		{
			m_spartanTable[i].push_back(_agent);
			val = i;
		}
	}

	return val;
}

int HashTable::UpdateQuad(Rectangle _bounds)
{
	int val = 0;

	for (int i = 0; i < m_quadrents.size(); i++)
	{
		if (CheckCollisionRecs(_bounds, m_quadrents[i]))
		{
			m_objectTable[i].push_back(_bounds);
			val = i;
		}
	}

	return val;
}

void HashTable::AddToQuad(int _num, CovenantAgent* _agent)
{
	m_covenantTable[_num].push_back(_agent);
}

void HashTable::AddToQuad(int _num, Spartan* _agent)
{
	m_spartanTable[_num].push_back(_agent);
}

void HashTable::Draw()
{
	for (int i = 0; i < m_quadrents.size(); i++)
	{
		Rectangle quad = m_quadrents[i];
		DrawRectangleLines(quad.x, quad.y, quad.width, quad.height, GREEN);	
		DrawText(TextFormat("%d", i), quad.x + quad.width / 2, quad.y + quad.height / 2, 15 ,BLACK);
	}
}

bool HashTable::HasMoved(int _quad, CovenantAgent* _agent)
{
	if (CheckCollisionPointRec({ _agent->Transform()->Position().x, _agent->Transform()->Position().y }, m_quadrents[_quad]))
		return false;	

	return true;
}

bool HashTable::HasMoved(int _quad, Spartan* _agent)
{
	if (CheckCollisionPointRec({ _agent->Transform()->Position().x, _agent->Transform()->Position().y }, m_quadrents[_quad]))
		return false;

	return true;
}

void HashTable::RemoveFromQuad(CovenantAgent* _agent)
{
	for (int i = 0; i < m_quadrents.size(); i++)
	{
		if (std::find(m_covenantTable[i].begin(), m_covenantTable[i].end(), _agent) != m_covenantTable[i].end())
			m_covenantTable[i].remove(_agent);		
	}
}

void HashTable::RemoveFromQuad(Spartan* _agent)
{
	for (int i = 0; i < m_quadrents.size(); i++)
	{
		if (std::find(m_spartanTable[i].begin(), m_spartanTable[i].end(), _agent) != m_spartanTable[i].end())
			m_spartanTable[i].remove(_agent);
	}
}

list<CovenantAgent*>* HashTable::GetCovenant(int _quad)
{	
	return &m_covenantTable[_quad];
}

list<Spartan*>* HashTable::GetSpartan(int _quad)
{
	return &m_spartanTable[_quad];
}

list<Rectangle>* HashTable::GetObjects(int _quad)
{
	return &m_objectTable[_quad];
}


vector<Rectangle>* HashTable::GetAllQuads()
{
	return &m_quadrents;

}

Rectangle HashTable::GetQuad(int _quad)
{
	return m_quadrents[_quad];
	
}
