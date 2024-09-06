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

PathAgent::PathAgent(Color _color, int _speed)
	: currentIndex(0), currentNode(nullptr), speed(_speed), color(_color)
{

}

PathAgent::~PathAgent()
{

}

void PathAgent::Update(float _dt)
{
	if (path.empty())
	{
		currentIndex = 0;
		return;
	}

	if (currentIndex == path.size() - 1)
	{
		for (int i = 0; i < path.size(); i++)
		{
			path[i]->SetType(NodeType::Empty);
		}
		currentNode = path[currentIndex];
		path.clear();		
		return;
	}

	float distance = 0;
	vec2 targetLocation = { 0,0 };

	currentNode = path[currentIndex];
	
	distance = glm::distance(currentNode->pos, path[currentIndex + 1]->pos);
	targetLocation = glm::normalize(pos - path[currentIndex + 1]->pos);	

	if (!CheckCollisionPointCircle({pos.x, pos.y}, {path[currentIndex + 1]->pos.x, path[currentIndex + 1]->pos.y}, 5))
		pos -= speed * _dt * targetLocation;	
	else
		currentIndex++;
}

void PathAgent::GoToNode(Node* _end)
{
	vector<Node*> temp = Dijkstras(currentNode, _end);

	if (std::find(temp.begin(), temp.end(), currentNode) != temp.end())
	{
		path = Dijkstras(currentNode, _end);
		currentIndex = 0;
	}
}

bool Sort(Node* _lhs, Node* _rhs)
{
	if (_lhs->gScore < _rhs->gScore)
		return true;
	else return false;
}

vector<Node*> PathAgent::Dijkstras(Node* _start, Node* _end)
{
	list<Node*> open;
	list<Node*> close;

	if (!_start || !_end)
		return vector<Node*>();

	if (_start == _end)
		return vector<Node*>();

	_start->gScore = 0;
	_start->parent = nullptr;

	open.push_back(_start);

	while (!open.empty())
	{
		Node* currentNode = open.front();

		close.push_back(open.front());
		open.erase(open.begin());

		for (auto& c : currentNode->connections)
		{
			if (c.target->type != NodeType::Wall && std::find(close.begin(), close.end(), c.target) == close.end())
			{
				float gScore = currentNode->gScore + c.cost;				

				if (std::find(open.begin(), open.end(), c.target) == open.end())
				{
					c.target->gScore = gScore;
					c.target->parent = currentNode;
					open.push_back(c.target);
				}
				else if (gScore < c.target->gScore)
				{
					c.target->gScore = gScore;
					c.target->parent = currentNode;
				}
			}
		}
	}

	Node* currentNode = _end;

	vector<Node*> path;
	while (currentNode)
	{	
		path.emplace(path.begin(), currentNode);		
		currentNode = currentNode->parent;
	}

	return path;
}

void PathAgent::Draw()
{	
	DrawCircleV({ pos.x + 60, pos.y + 60 }, 10, BLACK);
	DrawCircleV({ pos.x + 60, pos.y + 60 }, 8, color);

	if (path.empty())
		return;

	for (int i = 0; i < path.size() - 1; i++)
	{
		DrawRectangle(path[i]->pos.x + 50, path[i]->pos.y + 50, 20, 20, { color.r, color.g,color.b, 100 });
		DrawLine(path[i]->pos.x + 60, path[i]->pos.y + 60, path[i + 1]->pos.x + 60, path[i + 1]->pos.y + 60, BLACK);
	}	
}