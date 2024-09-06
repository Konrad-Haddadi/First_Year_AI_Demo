#pragma once

#include <glm/glm.hpp>
#include <vector>

namespace AIForGames
{
	struct Node;

	struct Edge
	{
	public:
		Node* target;
		float cost;

		Edge() : target(nullptr), cost(0) { }
		Edge(Node* _target, float _cost) : target(_target), cost(_cost) { }
	};

	struct Node
	{
	public:
		glm::vec2 pos;
		std::vector<Edge> connections;

		Node(float _x, float _y) : pos(_x, _y) { }

		void ConnectTo(Node* _other, float _cost);
		
	};


}