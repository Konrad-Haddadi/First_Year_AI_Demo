#include "PathAgent.h"
#include <raylib/raylib.h>
#include <raylib/raymath.h>
#include <glm/glm.hpp>
#include <algorithm>
#include <vector>
#include <list>
#include "NavMeshNode.h"

using std::vector;
using std::list;

PathAgent::PathAgent(Color _color, int _speed, INavigatable* _nodeMap)
	: currentIndex(0), currentNode({0,0}), speed(_speed), color(_color), m_nodeMap(_nodeMap)
{

}

PathAgent::~PathAgent()
{

}

bool PathAgent::CanSeePoint()
{
	for (int i = currentIndex; i < m_smoothPath.size(); i++)
	{
		if (!CheckCollisionPointLine({ m_smoothPath[i].x, m_smoothPath[i].y }, { pos.x, pos.y }, { m_smoothPath.back().x, m_smoothPath.back().y }, 10))
			currentIndex = i - 1;
	}

	return true;
}

void PathAgent::Update(float _dt)
{
	if (m_smoothPath.empty() || currentIndex >= m_smoothPath.size())
	{
		currentIndex = 0;
		return;
	}

	currentNode = m_smoothPath[currentIndex];

	vec2 delta = glm::normalize(currentNode - pos);
	float distanceToNext = glm::distance(pos, currentNode);

	if (distanceToNext >= 10)
	{
		pos += delta * (speed / 2) * _dt;
	}
	else
	{
		currentIndex++;

		if (currentIndex >= m_smoothPath.size())
		{
			m_path.clear();
			m_smoothPath.clear();
		}			
	}
}

void PathAgent::GoToNode(vec2 _end)
{
	NavMeshNode* node = m_nodeMap->GetClosestNode(currentNode);
	NavMeshNode* end = m_nodeMap->GetClosestNode(_end);

	vector<NavMeshNode*> temp = AStarSearch(node, end);

	m_path.clear();
	m_smoothPath.clear();

	if (std::find(temp.begin(), temp.end(), node) != temp.end())
	{
		m_path = temp;
		currentIndex = 0;
	}
	
	m_nodeMap->SmoothPath(this, _end);

}

bool Sort(NavMeshNode* _lhs, NavMeshNode* _rhs)
{
	if (_lhs->fScore < _rhs->fScore)
		return true;
	else return false;
}

vector<NavMeshNode*> PathAgent::AStarSearch(NavMeshNode* _start, NavMeshNode* _end)
{
	list<NavMeshNode*> open;
	list<NavMeshNode*> close;

	if (!_start || !_end)
		return vector<NavMeshNode*>();

	if (_start == _end)
		return vector<NavMeshNode*>();

	_start->gScore = 0;
	_start->parent = nullptr;

	open.push_back(_start);

	while (!open.empty())
	{
		open.sort(&Sort);

		NavMeshNode* currentNode = open.front();

		close.push_back(open.front());
		open.erase(open.begin());

		for (auto& c : currentNode->connections)
		{
			if (std::find(close.begin(), close.end(), c.target) == close.end())
			{
				float gScore = currentNode->gScore + c.cost;
				float hScore = abs(c.target->pos.x - _end->pos.x) + abs(c.target->pos.y - _end->pos.y);
				float fScore = gScore + hScore;

				if (std::find(open.begin(), open.end(), c.target) == open.end())
				{
					c.target->gScore = gScore;
					c.target->fScore = fScore;
					c.target->parent = currentNode;
					open.push_back(c.target);
				}
				else if (fScore < c.target->fScore)
				{
					c.target->gScore = gScore;
					c.target->fScore = fScore;
					c.target->parent = currentNode;
				}
			}
		}
	}

	NavMeshNode* currentNode = _end;

	vector<NavMeshNode*> path;
	while (currentNode)
	{
		path.emplace(path.begin(), currentNode);
		currentNode = currentNode->parent;
	}

	_end->parent = nullptr;

	return path;
}

void PathAgent::Draw()
{	
	if (IsKeyDown(KEY_GRAVE))
	{
		/*if (!m_path.empty())
		{
			for (int i = 0; i < m_path.size() - 1; i++)
			{
				if (i < m_path.size())
				{
					DrawLine(m_path[i]->pos.x, m_path[i]->pos.y, m_path[i + 1]->pos.x, m_path[i + 1]->pos.y, PINK);
					DrawCircleV({ m_path[i]->pos.x, m_path[i]->pos.y }, 10, YELLOW);
				}
			}
		}*/

		if (!m_smoothPath.empty())
		{
			for (int i = 0; i < m_smoothPath.size() - 1; i++)
			{
				if (i < m_smoothPath.size())
				{
					DrawLine(m_smoothPath[i].x, m_smoothPath[i].y, m_smoothPath[i + 1].x, m_smoothPath[i + 1].y, GREEN);
					//DrawCircleV({ m_smoothPath[i].x, m_smoothPath[i].y }, 10, GREEN);
				}
			}
			DrawLine(pos.x, pos.y, currentNode.x, currentNode.y, PURPLE);
		}
	}
	
	
	DrawCircleV({ pos.x, pos.y }, 5, BLACK);
	DrawCircleV({ pos.x, pos.y }, 4, color);

}