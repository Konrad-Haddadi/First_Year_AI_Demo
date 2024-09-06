#pragma once

#include <raylib/raylib.h>
#include <glm/vec2.hpp>
#include <vector>
#include <string>

using std::vector;
using std::string;
using glm::vec2;

namespace AITesting
{
	enum NodeType
	{
		Empty,
		Wall,
		Swamp		
	};

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

		float fScore = 0;
		float hScore = 0;
		float gScore = 0;

		int type;
		vec2 pos;		
		vector<Edge> connections;
		Node* parent = nullptr;
		Rectangle rect;

		float adjCost;
		float diagCost;
	public:

		Node(int _x, int _y, float _adjCost, float _diagCost);
		~Node();
		

		void SetType(int _type) { type = _type; }

		virtual void Update(float _dt);

		int GetSize() { return m_size; }
		void DiagConnectTo(Node* _other);
		void AdjacentConnectTo(Node* _other);
		void DrawEdge();
		void Draw();

	private:
		int m_size;
		int m_space;
	};
}


