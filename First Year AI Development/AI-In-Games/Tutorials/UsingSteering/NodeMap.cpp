#include "NodeMap.h"
#include <raylib/raylib.h>
#include <raylib/raymath.h>
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

			/*Node* nodeSouthWest = (x == 0 || y == 0) ? nullptr : GetNode(x - 1, y - 1);
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
			}*/
		}
	}
}

void NodeMap::Draw()
{	
	DrawRectangleRec({ 15, 15, m_mapSize.x * GetCellSize() + GetCellSize() * 3, m_mapSize.y * GetCellSize() + GetCellSize() * 3 + 5}, BLACK);
	DrawRectangleRec({ 45, 45, m_mapSize.x * GetCellSize(), m_mapSize.y * GetCellSize()  + 5}, WHITE);

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
	float currentDist = FLT_MAX;

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

vector<Node*> NodeMap::GetSmoothPath(vector<Node*> _path)
{
	vector<Node*> smoothPath;

	smoothPath.push_back(_path.front());

	for (int i = 0; i < _path.size(); i++)
	{
		for (int j = i; j < _path.size(); j++)
		{
			if (!IsVisibleFrom(_path[i], _path[j]))
			{
				smoothPath.push_back(_path[j - 1]);
				i = j - 1;
				break;
			}
		}		
	}

	smoothPath.push_back(_path.back());

	return smoothPath;
}

bool NodeMap::IsVisibleFrom(vec2 _start, vec2 _end)
{
	vec2 delta = _end - _start;
	float distance = glm::distance(_end, _start);
	delta = delta * (GetCellSize() / distance);

	for (float cells = 1.0f; cells < distance; cells += 1.0f)
	{
		vec2 testPosition = _start + (delta * cells);

		if (GetClosestNode(testPosition)->type == NodeType::Wall)
			return false;
	}

	return true;
}

bool NodeMap::IsVisibleFrom(Node* _start, Node* _end)
{
	vec2 delta = _end->pos - _start->pos;
	float distance = glm::distance(_end->pos, _start->pos);
	delta = delta * (GetCellSize() / distance);
	
	for (float cells = 1.0f; cells < distance / GetCellSize(); cells += 1.0f)
	{
		vec2 testPosition = _start->pos + (delta * cells);
		
		if (GetClosestNode(testPosition)->type == NodeType::Wall)
			return false;
	}

	return true;
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