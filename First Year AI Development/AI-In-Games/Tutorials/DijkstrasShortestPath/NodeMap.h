#pragma once

#include <glm/vec2.hpp>
#include "Node.h"

using glm::vec2;
using AITesting::Node;

class NodeMap
{
public:
	NodeMap(vec2 _mapSize) : m_mapSize(_mapSize) {}

	void Update(float _dt);
	void Load();
	void Draw();

	float GetCellSize() { return nodeMap[0]->GetSize(); }
	Node* GetNode(int _x, int _y) { return nodeMap[_x + (int)m_mapSize.x * _y]; }
	Node* GetClosestNode(vec2 _point);
	Node** GetMap() { return nodeMap; }
	Node* GetRandomNode();
	void Reset();

private:
	void Controls();
		
	Node* m_end = nullptr;
	vec2 m_mapSize;
	Node** nodeMap;

};