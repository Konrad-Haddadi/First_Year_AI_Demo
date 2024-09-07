#include "NodeMap.h"
#include <raylib/raylib.h>
#include <glm/glm.hpp>

using AITesting::NodeType;

void NodeMap::Load()
{
	m_nodeMap = new Node * [m_mapSize.x * m_mapSize.y];

	for (int y = 0; y < m_mapSize.y; y++)
	{	
		for (int x = 0; x < m_mapSize.x; x++)
		{
			Node* node = new Node(x, y, 10, 14.14f);

			int val = GetRandomValue(0, 100);
			if (val % 5 == 0)
				node->SetType(NodeType::Wall);			
			else
				node->SetType(NodeType::Empty);

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
					node->AdjacentConnectTo(nodeWest);
					nodeWest->AdjacentConnectTo(node);
				}

				Node* nodeSouth = y == 0 ? nullptr : GetNode(x, y - 1);
				if (nodeSouth)
				{
					node->AdjacentConnectTo(nodeSouth);
					nodeSouth->AdjacentConnectTo(node);
				}

				/*Node* nodeSouthWest = (x == 0 || y == 0) ? nullptr : GetNode(x - 1, y - 1);
				if (nodeSouthWest)
				{
					node->DiagConnectTo(nodeSouthWest);
					nodeSouthWest->DiagConnectTo(node);
				}

				Node* nodeSouthEast = (x == m_mapSize.x - 1 || y == 0) ? nullptr : GetNode(x + 1, y - 1);
				if (nodeSouthEast)
				{
					node->DiagConnectTo(nodeSouthEast);
					nodeSouthEast->DiagConnectTo(node);
				}*/
			}			
		}
	}
}

void NodeMap::Draw()
{
	for (int x = 0; x < m_mapSize.x * m_mapSize.y; x++)
		m_nodeMap[x]->Draw();		

	for (int x = 0; x < m_mapSize.x * m_mapSize.y; x++)
		m_nodeMap[x]->DrawEdge();
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

		if (IsKeyDown(KEY_SPACE))
			node->type = NodeType::Empty;

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

			float dist = glm::distance({ _point.x, _point.y }, node->pos);

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

bool NodeMap::DoesCollide(vec2 _start, vec2 _end, int _type)
{
	bool top = false;
	bool right = false;
	bool left = false;
	bool bot = false;

	for (int x = 0; x < m_mapSize.x * m_mapSize.y; x++)
	{
		Node* node = m_nodeMap[x];
		Vector2 vec = { 0,0 };
		
		top = CheckCollisionLines({ _start.x, _start.y }, { _end.x, _end.y},
			{node->pos.x, node->pos.y}, { node->pos.x + node->rect.width, node->pos.y }, & vec);

		right = CheckCollisionLines({ _start.x, _start.y }, { _end.x, _end.y },
			{ node->pos.x + node->rect.width, node->pos.y }, { node->pos.x + node->rect.width, node->pos.y + node->rect.height }, & vec);

		left = CheckCollisionLines({ _start.x, _start.y }, { _end.x, _end.y },
			{ node->pos.x, node->pos.y }, { node->pos.x, node->pos.y + node->rect.height }, & vec);

		bot = CheckCollisionLines({ _start.x, _start.y }, { _end.x, _end.y },
			{ node->pos.x, node->pos.y + node->rect.height }, { node->pos.x + node->rect.width, node->pos.y + node->rect.height }, & vec);


		if (top || right || left || bot)
		{
			if (node->type == _type)
				return true;
		}

	}
	return false;
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
