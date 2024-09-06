#include "NodeMap.h"
#include <raylib/raylib.h>
#include <glm/glm.hpp>
#include <time.h>
#include "Node.h"

void NodeMap::Load()
{
	int val = 32;
	srand(val);

	m_nodeMap = new Node * [m_mapSize.x * m_mapSize.y];
	for (int y = 0; y < m_mapSize.y; y++)
	{
		for (int x = 0; x < m_mapSize.x; x++)
		{
			Node* node = new Node(x, y);

			int typeVal = rand() % 100;

			if (typeVal % 4 == 0)
				node->SetType(1);
			else
				node->SetType(0);

			m_nodeMap[x + (int)m_mapSize.x * y] = node;					
		}
	}

	m_nodeMap[0]->SetType(0);

	for (int y = 0; y < m_mapSize.y; y++)
	{
		for (int x = 0; x < m_mapSize.x; x++)
		{
			Node* node = m_nodeMap[x + (int)m_mapSize.x * y];
			if (node)
			{
				Node* nodeWest = x == 0 ? nullptr : GetNode(x - 1, y);
				if (nodeWest)
				{
					node->ConnectTo(nodeWest, 1);
					nodeWest->ConnectTo(node, 1);
				}

				Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
				if (nodeSouth)
				{
					node->ConnectTo(nodeSouth, 1);
					nodeSouth->ConnectTo(node, 1);
				}
			}
		}
	}	
}

void NodeMap::Draw()
{	
	for (int x = 0; x < m_mapSize.x * m_mapSize.y; x++)
		m_nodeMap[x]->Draw();

}

void NodeMap::Update(float _dt)
{
	Controls();
}

void NodeMap::Controls()
{
	for (int x = 0; x < m_mapSize.x * m_mapSize.y; x++)
	{
		Node* node = m_nodeMap[x];

		if (CheckCollisionPointRec({ GetMousePosition().x , GetMousePosition().y },
			{ (float)node->pos.x, (float)node->pos.y, 25, 25 }))
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
				node->type = NodeType::Wall;

			if (IsKeyDown(KEY_E))
				node->type = NodeType::Empty;
		}
	}
}

Node* NodeMap::GetClosestNode(vec2 _point)
{
	Node* current = nullptr;
	float currentDist = FLT_MAX;

	for (int x = 0; x < m_mapSize.x * m_mapSize.y; x++)
	{
		Node* node = m_nodeMap[x];

		if (node->type != NodeType::Wall)
		{
			if (current == nullptr)
				current = node;

			float dist = glm::distance({ _point.x + 10, _point.y + 10 }, node->pos);

			if (dist < currentDist)
			{
				current = node;
				currentDist = dist;
			}
		}		
	}

	return current;
}

Node* NodeMap::GetRandomNode()
{
	int val = GetRandomValue(0, m_mapSize.x * m_mapSize.y - 1);

	if (m_nodeMap[val]->type != NodeType::Wall)
		return m_nodeMap[val];
	else
		return GetRandomNode();

}

void NodeMap::Reset()
{
	for (int x = 0; x < m_mapSize.x * m_mapSize.y; x++)
	{
		if (m_nodeMap[x]->type != NodeType::Wall)
		{
			m_nodeMap[x]->type = NodeType::Empty;
			m_nodeMap[x]->parent = nullptr;
		}
	}
}