#pragma once

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
		Start,
		End,
		Searched,
		Path
	};

	struct Node;

	struct Edge
	{
	public:
		Node* target;
		float cost;

		Edge() : target(nullptr), cost(0) { }
		Edge(Node* _target, float _cost) : target(_target), cost(_cost) { }
		~Edge() { target = nullptr; cost = 0; }
	};

	struct Node
	{
	public:
		float gScore;

		int type;
		vec2 pos;		
		vector<Edge> connections;
		vec2 direction;

	public:

		Node(int _x, int _y);
		~Node() {};
		

		void SetType(int _type) { type = _type; }

		int GetSize() { return m_size; }
		void ConnectTo(Node* _other, float _cost);
		virtual void Update(float _dt);
		void DrawDirection();
		void Draw();

	private:
		int m_size;
		int m_space;
	};
}

