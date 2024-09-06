#include "Map.h"

#include <iostream>
#include <raylib/raylib.h>
#include "Node.h"


bool Map::found = false;

Map::Map(vec2 _pos, vec2 _scale, Map* _parent)
	: m_pos(_pos), scale(_scale), color(GRAY), parent(_parent),
	isStart(false), isEnd(false), empty(true), m_smoothPath(false), isFound(false), checked(false)
{
}

Map::Map()
	: m_pos({0,0}), scale({0,0}), color(GRAY), parent(nullptr),
	isStart(false), isEnd(false), empty(true), m_smoothPath(false), isFound(false), checked(false)
{
}

void Map::Load()
{
}

void Map::Update(float _dt)
{
	if (CheckCollisionPointRec(GetMousePosition(), { 100 + m_pos.x * 30, 50 + m_pos.y * 30, scale.x, scale.y }) && !found)
	{
		if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
		{
			Clear();
			empty = false;
		}

		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			empty = true;

		if (IsKeyPressed(KEY_S))
			isStart = true;		
		
		if (IsKeyPressed(KEY_E))
			isEnd = true;
	}	

	if (IsKeyPressed(KEY_SPACE))
		Clear();	
}

void Map::Draw()
{

	if (isStart)
		color = BLUE;
	else if (isEnd)
		color = RED;
	else if (isFound)
		color = PURPLE;
	else if (m_smoothPath)
		color = YELLOW;
	else if (!empty)
		color = BLACK;
	else
		color = LIGHTGRAY;

	DrawRectangle(100 + m_pos.x * 30, 50 + m_pos.y * 30, scale.x, scale.y, color);
}

void Map::Unload()
{
}

void Map::DrawPath()
{	
	if (isStart)
		return;

	isFound = true;
	parent->DrawPath();
}

void Map::FollowPath()
{

}
void Map::Clear()
{
	isStart = false;
	isEnd = false;
	m_smoothPath = false;
	found = false;
	isFound = false;	
	checked = false;
}
