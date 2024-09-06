#include "NodeMap.h"
#include <raylib/raylib.h>
#include <glm/glm.hpp>
#include <list>

using std::list;
using AITesting::NodeType;

void NodeMap::Load()
{
	nodeMap = new Node * [m_mapSize.x * m_mapSize.y];

	for (int y = 0; y < m_mapSize.y; y++)
	{	
		for (int x = 0; x < m_mapSize.x; x++)
		{
			Node* node = new Node(x, y);

			int val = GetRandomValue(0, 100);
			
			if (val % 4 == 0)
				node->SetType(1);
			else
				node->SetType(0);

			nodeMap[x + (int)m_mapSize.x * y] = node;	
		}
	}

	nodeMap[0]->SetType(0);	
}

void NodeMap::Draw()
{
	for (int x = 0; x < m_mapSize.x * m_mapSize.y; x++)
		nodeMap[x]->Draw();		

	for (int x = 0; x < m_mapSize.x * m_mapSize.y; x++)
		nodeMap[x]->DrawDirection();	
}

void NodeMap::Update(float _dt)
{
	Controls();
}

void NodeMap::Controls()
{		
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	{
		Node* node = GetClosestNode({ GetMousePosition().x, GetMousePosition().y });

		if(node)
			node->type = NodeType::Empty;
	}

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		Node* node = GetClosestNode({ GetMousePosition().x, GetMousePosition().y });

		if (node)
			node->type = NodeType::Wall;
	}

	for (int x = 0; x < m_mapSize.x * m_mapSize.y; x++)
	{		
		Node* node = nodeMap[x];		

		if (IsKeyPressed(KEY_SPACE))
			node->SetType(NodeType::Empty);

		if (IsKeyPressed(KEY_ENTER))
		{
			node->direction = { 0,0 };
		}
	}

	if (IsKeyPressed(KEY_ENTER))
	{
		for (int x = 0; x < m_mapSize.x * m_mapSize.y; x++)
		{
			Node* node = nodeMap[x];
			if (node->type == NodeType::End)
				node->type = NodeType::Empty;
		}

		Node* node = GetRandomNode();
		node->type = NodeType::End;

		UseFlowField(node);
	}
}

Node* NodeMap::GetClosestNode(vec2 _point)
{
	for (int x = 0; x < m_mapSize.x * m_mapSize.y; x++)
	{
		Node* node = nodeMap[x];

		if (node->type != NodeType::Wall)
		{
			if (CheckCollisionPointCircle({ node->pos.x, node->pos.y}, { _point.x, _point.y }, 5))
				return node;
		}		
	}

	return nullptr;
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
		}		
	}
}

void NodeMap::UseFlowField(Node* _node)
{
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

				Node* nodeSouthWest = (x == 0 || y == 0) ? nullptr : GetNode(x - 1, y - 1);
				if (nodeSouthWest)
				{
					node->ConnectTo(nodeSouthWest, 1.414f);
					nodeSouthWest->ConnectTo(node, 1.414f);
				}

				Node* nodeSouthEast = (x == m_mapSize.x - 1 || y == 0) ? nullptr : GetNode(x + 1, y - 1);
				if (nodeSouthEast)
				{
					node->ConnectTo(nodeSouthEast, 1.414f);
					nodeSouthEast->ConnectTo(node, 1.414f);
				}
			}
		}
	}

	Dijkstras(_node);
	
	for (int y = 0; y < m_mapSize.y; y++)
	{
		for (int x = 0; x < m_mapSize.x; x++)
		{
			Node* node = nodeMap[x + (int)m_mapSize.x * y];
			if (node)
			{
				node->connections.clear();
			}
		}
	}
}

void NodeMap::Dijkstras(Node* _start)
{	
	list<Node*> open;
	list<Node*> close;

	open.push_back(_start);

	while (!open.empty())
	{
		Node* currentNode = open.front();

		close.push_back(open.front());
		open.erase(open.begin());

		if (!currentNode)
			return;

		for (auto& c : currentNode->connections)
		{
			if (c.target->type != NodeType::Wall && std::find(close.begin(), close.end(), c.target) == close.end())
			{
				float gScore = currentNode->gScore + c.cost;				

				if (std::find(open.begin(), open.end(), c.target) == open.end())
				{
					c.target->gScore = gScore;
					c.target->direction = glm::normalize(currentNode->pos - c.target->pos);
					open.push_back(c.target);
				}
				else if (gScore < c.target->gScore)
				{
					c.target->gScore = gScore;
					c.target->direction = glm::normalize(currentNode->pos - c.target->pos);
				}
			}
		}
	}
}