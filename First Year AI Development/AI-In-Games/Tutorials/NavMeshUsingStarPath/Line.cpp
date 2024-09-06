#include "Line.h"

#include <vector>
#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <raylib/raylib.h>

using std::vector;
using glm::vec2;

vec2* Line::DoesIntersect(Line _line)
{
	Vector2* collision = new Vector2{ 0,0 };	

	if (CheckCollisionLines(start, end, _line.start, _line.end, collision))
		return new vec2{ collision->x, collision->y };
	else
		return nullptr;
}

vec2* Line::CanSeePoint(vector<Line> _lines, vec2 _point)
{
	Vector2* crossSection = new Vector2;
	vec2* result = nullptr;
	Vector2 point = { _point.x, _point.y };

	for (int i = 0; i < _lines.size() - 1; i++)
	{
		if (CheckCollisionLines(point, _lines[i + 1].GetMiddleVector2(), _lines[i].start, _lines[i].end, crossSection))
		{
			delete result;
			result = new vec2{ crossSection->x, crossSection->y };
		}
	}

	return result;
}

vec2 Line::GetMiddle()
{
	return { (start.x + end.x) / 2, (start.y + end.y) / 2 };
}

Vector2 Line::GetMiddleVector2()
{
	return { (start.x + end.x) / 2, (start.y + end.y) / 2 };
}

vec2 Line::GetClosestPoint(vec2 _point)
{
	float middleDist = 0;
	float startDist = 0;
	float endDist = 0;

	middleDist = glm::distance(_point, GetMiddle());
	startDist = glm::distance(_point, { start.x,start.y });
	endDist = glm::distance(_point, { end.x,end.y });

	if (startDist < endDist)
	{
		if(startDist < middleDist)
			return { start.x, start.y };
		else
			return GetMiddle();
	}		
	else
	{
		if (middleDist < endDist)
			return GetMiddle();
		else
			return { end.x, end.y };
	}

}