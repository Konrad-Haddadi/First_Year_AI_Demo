#pragma once

#include <glm/vec2.hpp>
#include <raylib/raylib.h>
#include <vector>

using std::vector;
using glm::vec2;

class Map
{
public:
	Map(vec2 _pos, vec2 _scale, Map* _parent);
	Map();

	void Load();
	void Update(float _dt);
	void Draw();
	void Unload();
	void Clear();
	void DrawPath();
	void FollowPath();

public:
	vec2 pos;
	vec2 scale;
	Color color;

	bool empty;
	bool isStart;
	bool isEnd;
	bool path;
	bool isFound;
	bool checked;
	
	
	static bool found;

	
	Map* parent;


};

