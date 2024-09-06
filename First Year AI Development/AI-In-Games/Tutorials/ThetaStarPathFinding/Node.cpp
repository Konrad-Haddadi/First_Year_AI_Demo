#include "Node.h"

#include <raylib/raylib.h>

AITesting::Node::Node(int _x, int _y, float _adjCost, float _diagCost)
	: adjCost(_adjCost), diagCost(_diagCost), m_size(25), m_space(5), type(0)
{
	pos = {_x * m_size, _y * m_size};
	rect = { pos.x, pos.y, 25, 25 };
}

void AITesting::Node::DiagConnectTo(Node* _other)
{
	connections.push_back(Edge(_other, diagCost));
}

void AITesting::Node::AdjacentConnectTo(Node* _other)
{
	connections.push_back(Edge(_other, adjCost));
}

void AITesting::Node::Update(float _dt)
{

}

void AITesting::Node::DrawEdge()
{
	
}

void AITesting::Node::Draw()
{
	Color color = WHITE;	
	switch (type)
	{
	case Empty:
		color = LIGHTGRAY;
		break;			

	case Wall:
		color = BLACK;
		break;
	
	case Swamp:
		color = GREEN;
			break;
	}

	DrawRectangle(pos.x, pos.y,
		m_size - m_space, m_size - m_space, color);
}


