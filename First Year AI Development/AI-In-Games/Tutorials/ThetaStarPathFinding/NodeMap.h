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

	float GetCellSize() { return m_nodeMap[0]->GetSize(); }
	Node* GetNode(int _x, int _y) { return m_nodeMap[_x + (int)m_mapSize.x * _y]; }
	Node* GetClosestNode(vec2 _point);
	Node** GetMap() { return m_nodeMap; }
	Node* GetRandomNode();
	bool DoesCollide(vec2 _start, vec2 _end, int _type);
	void Reset();

private:
	void Controls();
		
	vec2 m_mapSize;
	Node** m_nodeMap;

};