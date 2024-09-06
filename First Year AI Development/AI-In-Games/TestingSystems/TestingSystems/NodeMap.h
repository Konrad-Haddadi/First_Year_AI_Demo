#pragma once

#include "HashTable.h"

#include "Node.h"
#include <vector>
#include <raylib/raylib.h>
#include <glm/vec2.hpp>

using glm::vec2;

class NodeMap
{
public:
	NodeMap(vec2 _mapSize) : m_mapSize(_mapSize), m_nodeMap(nullptr) {}

	void Update(float _dt);
	void Load();
	void Draw();

	int GetAmount() { return m_mapSize.x * m_mapSize.y; }
	float GetCellSize() { return m_nodeMap[0]->GetSize(); }
	
	Node* GetNode(int _x, int _y) { return m_nodeMap[_x + (int)m_mapSize.x * _y]; }
	Node* GetClosestNode(vec2 _point);
	Node** GetMap() { return m_nodeMap; }
	Node* GetRandomNode();
	void Reset();

private:
	void Controls();		
	
	vec2 m_mapSize;
	Node** m_nodeMap;
};