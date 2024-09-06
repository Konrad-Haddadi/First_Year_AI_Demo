#include "NodeMap.h"
#include <raylib/raylib.h>
#include <glm/glm.hpp>
#include <time.h>
#include "Node.h"


using AITesting::NodeType;

void NodeMap::Load()
{
	int val = 32;
	srand(val);
	nodeMap = new Node * [m_mapSize.x * m_mapSize.y];

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

			nodeMap[x + (int)m_mapSize.x * y] = node;
		}
	}

	nodeMap[0]->SetType(0);

	for (int y = 0; y < m_mapSize.y; y++)
	{
		for (int x = 0; x < m_mapSize.x; x++)
		{
			Node* node = nodeMap[x + (int)m_mapSize.x * y];
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
	DrawRectangleRec({ 15, 15, m_mapSize.x * GetCellSize() + GetCellSize() * 3, m_mapSize.y * GetCellSize() + GetCellSize() * 3 }, BLACK);
	DrawRectangleRec({ 45, 45, m_mapSize.x * GetCellSize() + 5, m_mapSize.y * GetCellSize() + 5}, WHITE);

	for (int x = 0; x < m_mapSize.x * m_mapSize.y; x++)
		nodeMap[x]->Draw();

	for (int x = 0; x < m_mapSize.x * m_mapSize.y; x++)
		nodeMap[x]->DrawEdge();	
}

void NodeMap::Update(float _dt)
{
	Controls();
}

void NodeMap::Controls()
{
	for (int x = 0; x < m_mapSize.x * m_mapSize.y; x++)
	{
		Node* node = nodeMap[x];

		if (CheckCollisionPointRec({ GetMousePosition().x - 50 , GetMousePosition().y - 50 },
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
	float currentDist = 99999999999;

	for (int x = 0; x < m_mapSize.x * m_mapSize.y; x++)
	{
		Node* node = nodeMap[x];

		if (current == nullptr)
			current = node;
		
		float dist = glm::distance({ _point.x - 60, _point.y - 60 }, node->pos);

		if (dist < currentDist)
		{
			current = node;
			currentDist = dist;
		}
	}

	return current;
}

Node* NodeMap::GetRandomNode()
{
	int val = GetRandomValue(0, m_mapSize.x * m_mapSize.y - 1);

	if (nodeMap[val]->type != NodeType::Wall)
		return nodeMap[val];
	else
		return GetRandomNode();

}

void NodeMap::Reset()
{
	for (int x = 0; x < m_mapSize.x * m_mapSize.y; x++)
	{
		if (nodeMap[x]->type != NodeType::Wall)
		{
			nodeMap[x]->type = NodeType::Empty;
			nodeMap[x]->parent = nullptr;
		}
	}
}