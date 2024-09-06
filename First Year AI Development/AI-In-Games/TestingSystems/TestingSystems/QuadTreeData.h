#pragma once

#include <raylib/raylib.h>

template<typename DATA>
struct QuadTreeData
{
public:
	bool flag;
	DATA* data;
	Rectangle bounds;

public:
	QuadTreeData(DATA* _data, Rectangle _bounds)
		:data(_data), bounds(_bounds), flag(false) {}

};
