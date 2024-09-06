#include "PathAgent.h"
#include <raylib/raylib.h>
#include <raylib/raymath.h>
#include <glm/glm.hpp>
#include <algorithm>
#include <vector>
#include <list>
#include "NavMeshNode.h"
#include <Azimuth/GameObjects/ATransform.h>

using std::vector;
using std::list;

PathAgent::PathAgent(ATransform* _transform, Color _color, int _speed, INavigatable* _nodeMap)
	: m_transform(_transform), m_currentIndex(0), m_currentNode({0,0}), m_speed(_speed), color(_color), m_nodeMap(_nodeMap)
{
	m_pos = m_transform->Position();
}

PathAgent::~PathAgent()
{

}

void PathAgent::Update(float _dt)
{
	m_velocity = (m_speed / 100) * (m_pos - m_transform->Position());

	if (!CheckCollisionPointCircle({ m_transform->Position().x, m_transform->Position().y }, { m_pos.x, m_pos.y }, 2))
		m_transform->UpdatePosition(_dt * m_velocity);	

	if (m_smoothPath.empty() || m_currentIndex >= m_smoothPath.size())
	{
		m_currentIndex = 0;
		return;
	}

	m_currentNode = m_smoothPath[m_currentIndex];

	vec2 delta = glm::normalize(m_currentNode - m_pos);
	float distanceToNext = glm::distance(m_pos, m_currentNode);

	if (distanceToNext >= 10)
	{
		m_pos += delta * (m_speed / 2) * _dt;
	}
	else
	{
		m_currentIndex++;
		if (m_currentIndex >= m_smoothPath.size())
		{
			m_path.clear();
			m_smoothPath.clear();
		}			
	}
}

void PathAgent::GoToNode(vec2 _end)
{
	NavMeshNode* node = m_nodeMap->GetClosestNode(m_currentNode);
	NavMeshNode* end = m_nodeMap->GetClosestNode(_end);

	vector<NavMeshNode*> temp = AStarSearch(node, end);

	m_path.clear();
	m_smoothPath.clear();

	if (std::find(temp.begin(), temp.end(), node) != temp.end())
	{
		m_path = temp;
		m_currentIndex = 0;
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
				float hScore = glm::distance(c.target->pos, _end->pos) * 0.25f;
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
					DrawLine(m_smoothPath[i].x, m_smoothPath[i].y, m_smoothPath[i + 1].x, m_smoothPath[i + 1].y, PINK);
					//DrawCircleV({ m_smoothPath[i].x, m_smoothPath[i].y }, 10, GREEN);
				}
			}
			DrawLine(m_pos.x, m_pos.y, m_currentNode.x, m_currentNode.y, PURPLE);
		}

		DrawCircleV({ m_pos.x, m_pos.y }, 5, BLACK);
		DrawCircleV({ m_pos.x, m_pos.y }, 4, LIGHTGRAY);
	}	
	
	DrawCircleV({ m_transform->Position().x, m_transform->Position().y}, 5, BLACK);
	DrawCircleV({ m_transform->Position().x, m_transform->Position().y }, 4, color);

}