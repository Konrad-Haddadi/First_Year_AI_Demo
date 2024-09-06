#pragma once

#include "glm/vec2.hpp"
#include "raylib/raylib.h"
#include "raylib/raymath.h"

#include <vector>

using std::vector;
using glm::vec2;

class Line
{
public:
	Line(vec2 _start, vec2 _end) : start({ _start.x, _start.y }), end({ _end.x, _end.y }) { }
	Line(Vector2 _start, Vector2 _end) : start(_start), end(_end) {}
	
	Line() : start({}), end({}) {}

	bool HasStart() { return (!Vector2Equals(start, { 0,0 })); }
	bool HasEnd() { return (!Vector2Equals(end, { 0,0 })); }
	
	vec2 GetMiddle();
	Vector2 GetMiddleVector2();
	vec2 GetClosestPoint(vec2 _point);
	vec2* DoesIntersect(Line _line);	
	vec2* CanSeePoint(vector<Line> _lines, vec2 _point);

public:
	Vector2 start;
	Vector2 end;
};