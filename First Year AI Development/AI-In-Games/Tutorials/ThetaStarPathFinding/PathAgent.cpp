#include "PathAgent.h"
#include <raylib/raylib.h>
#include <raylib/raymath.h>
#include <glm/glm.hpp>
#include <algorithm>
#include <vector>
#include <list>

using AITesting::NodeType;
using AITesting::Node;
using std::vector;
using std::list;


PathAgent::PathAgent(NodeMap* _map, Color _color, int _speed)
	: m_nodeMap(_map), m_currentIndex(0), m_speed(_speed), color(_color)
{

}

PathAgent::~PathAgent()
{

}

void PathAgent::Update(float _dt)
{
	if (IsKeyDown(KEY_TAB))
		return;

	if (m_smoothPath.empty() || m_currentIndex >= m_smoothPath.size())
	{
		m_currentIndex = 0;
		return;
	}

	float distance = 0;
	vec2 targetLocation = { 0,0 };

	distance = glm::distance(currentNode, m_smoothPath[m_currentIndex + 1]);
	targetLocation = glm::normalize(m_pos - m_smoothPath[m_currentIndex + 1]);	

	if (!CheckCollisionPointCircle({m_pos.x, m_pos.y}, {m_smoothPath[m_currentIndex + 1].x, m_smoothPath[m_currentIndex + 1].y}, 5))
		m_pos -= m_speed * _dt * targetLocation;	
	else
	{
		m_currentIndex++;

		if (m_currentIndex >= m_smoothPath.size() - 1)
		{
			currentNode = m_smoothPath[m_currentIndex];
			m_smoothPath.clear();
		}
		else
			currentNode = m_smoothPath[m_currentIndex];
	}
}

void PathAgent::GoToNode(Node* _end)
{
	Node* node = m_nodeMap->GetClosestNode(m_pos);
	vector<Node*> temp = AStarSearch(node, _end);

	m_smoothPath.clear();
	m_path.clear();
	if (std::find(temp.begin(), temp.end(), node) != temp.end())
	{
		m_smoothPath = GetSmoothPath(temp);
		m_path = temp;
		m_currentIndex = 0;
	}
}

bool Sort(Node* _lhs, Node* _rhs)
{
	if (_lhs->fScore < _rhs->fScore)
		return true;
	else return false;
}

vector<Node*> PathAgent::AStarSearch(Node* _start, Node* _end)
{
	list<Node*> open;
	list<Node*> close;

	if (!_start || !_end)
		return vector<Node*>();

	if (_start == _end)
		return vector<Node*>();

	_end->gScore = 0;
	_start->parent = nullptr;

	open.push_back(_start);

	while (!open.empty())
	{
		open.sort(&Sort);

		Node* currentNode = open.front();

		close.push_back(open.front());
		open.erase(open.begin());

		for (auto& c : currentNode->connections)
		{
			if (c.target->type != NodeType::Wall && std::find(close.begin(), close.end(), c.target) == close.end())
			{
				float gScore = currentNode->gScore + c.cost;
				float hScore = DistHeuristic(c.target->pos, _end->pos);
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
	
	Node* currentNode = _end;

	vector<Node*> m_smoothPath;
	while (currentNode)
	{
		m_smoothPath.emplace(m_smoothPath.begin(), currentNode);		
		currentNode = currentNode->parent;
	}	

	return m_smoothPath;
}

vector<vec2> PathAgent::GetSmoothPath(vector<Node*> _path)
{
	vector<vec2> smooth;

	smooth.push_back(_path[0]->pos);

	for (int i = 0; i < _path.size(); i++)
	{
		for (int j = i + 1; j < _path.size(); j++)
		{
			if (!LineOfSight(_path[i]->pos, _path[j]->pos))
			{
				smooth.push_back(_path[j - 1]->pos);
				i = j;
			}
		}
	}

	if(LineOfSight(smooth.back(), _path.back()->pos))
		smooth.push_back(_path.back()->pos);

	return smooth;
}

bool PathAgent::LineOfSight(vec2 _lhs, vec2 _rhs)
{   
	return !m_nodeMap->DoesCollide({ _lhs.x + 10, _lhs.y + 10 }, { _rhs.x + 10, _rhs.y + 10 }, NodeType::Wall);;
}

float PathAgent::DistHeuristic(vec2 _posA, vec2 _posB)
{
	return glm::distance(_posA, _posB);
}

float PathAgent::ManHattanHeuristic(vec2 _posB, vec2 _posA)
{
	return  abs(_posA.x - _posB.x) + abs(_posA.y - _posB.y);
}

float PathAgent::ManHattan8WayHeuristic(Node* _current, Node* _end)
{
	float dx = abs(_current->pos.x - _end->pos.x);
	float dy = abs(_current->pos.y - _end->pos.y);
	
	if (dx > dy)
		return (_current->diagCost * dy) + _current->adjCost * (dx - dy);
	else
		return (_current->diagCost * dx) + _current->adjCost * (dy - dx);
}

void PathAgent::Draw()
{	
	DrawCircleV({ m_pos.x + 10, m_pos.y + 10 }, 10, BLACK);
	DrawCircleV({ m_pos.x + 10, m_pos.y + 10 }, 8, color);

	if (m_smoothPath.empty() || IsKeyUp(KEY_GRAVE))
		return;

	for (int i = 0; i < m_path.size(); i++)
	{
		DrawRectangle(m_path[i]->pos.x, m_path[i]->pos.y, 20, 20, { 0, 255,0, 100 });

		if (i + 1 < m_path.size())
			DrawLine(m_path[i]->pos.x + 10, m_path[i]->pos.y + 10, m_path[i + 1]->pos.x + 10, m_path[i + 1]->pos.y + 10, BLACK);
	}

	for (int i = 0; i < m_smoothPath.size(); i++)
	{
		DrawRectangle(m_smoothPath[i].x, m_smoothPath[i].y, 20, 20, { color.r, color.g,color.b, 255 });

		if(i + 1 < m_smoothPath.size())
			DrawLine(m_smoothPath[i].x + 10, m_smoothPath[i].y + 10, m_smoothPath[i + 1].x + 10, m_smoothPath[i + 1].y + 10, BLACK);
	}	

}