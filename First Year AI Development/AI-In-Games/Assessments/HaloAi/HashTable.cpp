#include "HashTable.h"
#include "Agent.h"
#include "CovenantBaseAgent.h"
#include "SpartanAgent.h"
#include <raylib/raylib.h>

HashTable::HashTable()
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
		}
	}
}

void HashTable::Load()
{
	for (float y = 0; y < 4; y++)
	{
		for (float x = 0; x < 8; x++)
		{
			m_covenantTable.push_back(list<CovenantBaseAgent*>());
			m_spartanTable.push_back(list<SpartanAgent*>());
			m_quadrents.push_back({ 200 * x, 200 * y, 200, 200 });
		}
	}
}

int HashTable::UpdateQuad(CovenantBaseAgent* _agent)
{
	int val = 0;

	for (int i = 0; i < m_quadrents.size(); i++)
	{	
		if (std::find(m_covenantTable[i].begin(), m_covenantTable[i].end(), _agent) != m_covenantTable[i].end())
			m_covenantTable[i].remove(_agent);

		if (CheckCollisionPointRec({ _agent->GetPos().x, _agent->GetPos().y }, m_quadrents[i]))
		{
			m_covenantTable[i].push_back(_agent);
			val = i;
		}
	}

	return val;
}

int HashTable::UpdateQuad(SpartanAgent* _agent)
{
	int val = 0;

	for (int i = 0; i < m_quadrents.size(); i++)
	{
		if (std::find(m_spartanTable[i].begin(), m_spartanTable[i].end(), _agent) != m_spartanTable[i].end())
			m_spartanTable[i].remove(_agent);

		if (CheckCollisionPointRec({ _agent->GetPos().x, _agent->GetPos().y }, m_quadrents[i]))
		{
			m_spartanTable[i].push_back(_agent);
			val = i;
		}
	}

	return val;
}

void HashTable::AddToQuad(int _num, CovenantBaseAgent* _agent)
{
	m_covenantTable[_num].push_back(_agent);
}

void HashTable::AddToQuad(int _num, SpartanAgent* _agent)
{
	m_spartanTable[_num].push_back(_agent);
}

void HashTable::Draw()
{
	for (int i = 0; i < m_quadrents.size(); i++)
	{
		Rectangle quad = m_quadrents[i];
		DrawRectangleLines(quad.x, quad.y, quad.width, quad.height, GREEN);
		DrawCircleV({ quad.x + quad.width / 2 , quad.y + quad.height / 2}, 30, { GREEN.r, GREEN.g, GREEN.b, 100 });
		DrawText(TextFormat("%d", i), quad.x + quad.width / 2, quad.y + quad.height / 2, 50, RED);
	}

}

bool HashTable::HasMoved(int _quad, CovenantBaseAgent* _agent)
{
	if (CheckCollisionPointRec({ _agent->GetPos().x, _agent->GetPos().y }, m_quadrents[_quad]))
		return false;	

	return true;
}

bool HashTable::HasMoved(int _quad, SpartanAgent* _agent)
{
	if (CheckCollisionPointRec({ _agent->GetPos().x, _agent->GetPos().y }, m_quadrents[_quad]))
		return false;

	return true;
}

list<CovenantBaseAgent*>* HashTable::GetCovenant(int _quad)
{	
	return &m_covenantTable[_quad];
}

list<SpartanAgent*>* HashTable::GetSpartan(int _quad)
{
	return &m_spartanTable[_quad];
}

Rectangle HashTable::GetQuad(int _quad)
{
	return m_quadrents[_quad];
	
}
