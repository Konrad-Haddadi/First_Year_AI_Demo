#include "Node.h"

#include <raylib/raylib.h>

AITesting::Node::Node(int _x, int _y)
	: m_size(25),m_space(5), type(0), gScore(0), direction({0,0})
{
	pos = {_x * m_size, _y * m_size };
}

void AITesting::Node::ConnectTo(Node* _other, float _cost)
{
	connections.push_back(Edge(_other, _cost));
}

void AITesting::Node::Update(float _dt)
{
	
}

void AITesting::Node::DrawDirection()
{
	if (type != Wall)
		DrawLineEx({ pos.x + 10, pos.y + 10 }, { pos.x + 10 + direction.x * 15, pos.y + 10 + direction.y * 15 }, 2, RED);
}

void AITesting::Node::Draw()
{
	Color color = WHITE;	
	switch (type)
	{
	case Empty:
		color = LIGHTGRAY;
		break;

	case Start:
		color = BLUE;
		break;

	case End:
		color = YELLOW;
		break;

	case Wall:
		color = BLACK;
		break;

	case Path:
		color = { 100, 100, 100, 200 };
		break;
	}

	DrawRectangle(pos.x, pos.y,
		m_size - m_space, m_size - m_space, color);

}


