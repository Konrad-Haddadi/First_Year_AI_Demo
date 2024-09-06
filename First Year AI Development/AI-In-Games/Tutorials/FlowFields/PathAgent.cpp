#include "PathAgent.h"

#include "NodeMap.h"

PathAgent::PathAgent(Color _color, int _speed, NodeMap* _nodeMap)
	: currentIndex(0), speed(_speed), color(_color), nodeMap(_nodeMap)
{

}

PathAgent::~PathAgent()
{

}

void PathAgent::Update(float _dt)
{
	float distance = 0;
	
	if(nodeMap->GetClosestNode({ pos.x, pos.y }))
		dir = nodeMap->GetClosestNode({ pos.x, pos.y })->direction;

	pos += speed * _dt * dir;		
}

void PathAgent::GoToNode(Node* _end)
{
	
}

void PathAgent::Draw()
{	
	DrawCircleV({ pos.x + 10, pos.y + 10}, 10, BLACK);
	DrawCircleV({ pos.x + 10, pos.y + 10 }, 8, color);
}