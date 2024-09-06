#pragma once

#include <vector>
#include <glm/vec2.hpp>

using std::vector;
using glm::vec2;

class NavMeshNode 
{
public:
	struct Edge
	{
	public:
		NavMeshNode* target;
		float cost;

		Edge() : target(nullptr), cost(0) { }
		Edge(NavMeshNode* _target, float _cost) : target(_target), cost(_cost) { }
	};

	NavMeshNode() : pos({ 0,0 }), fScore(0), hScore(0), gScore(0), parent(nullptr) { }
	NavMeshNode(int _x, int _y) : pos({ _x, _y }), fScore(0), hScore(0), gScore(0) { }
	~NavMeshNode() { }	

	int GetAdjacentVertices(NavMeshNode* _other, vec2* _adj);

public:
	vector<Edge> connections;
	vector<vec2> verticies;

	float fScore;
	float hScore;
	float gScore;

	vec2 pos;
	NavMeshNode* parent;
};

