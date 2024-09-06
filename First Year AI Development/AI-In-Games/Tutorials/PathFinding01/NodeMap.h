#pragma once

#include "Node.h"
#include <vector>
#include <string>
using std::vector;
using AIForGames::Node;
using std::string;

class NodeMap
{
public:
	void Init(vector<string> _asciiMap, int _cellsize);

	Node* GetNode(int _x, int _y) { return m_nodes[_x + m_width * _y]; }
	void Draw();

private:
	int m_width;
	int m_height;
	float m_cellSize;
	
	Node** m_nodes;
	
};

