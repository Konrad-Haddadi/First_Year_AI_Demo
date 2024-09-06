#include "Node.h"

#include <raylib/raylib.h>

Node::Node(int _x, int _y)
	: m_size(25), m_space(5), type(0)
{
	pos = {_x * m_size + 2, _y * m_size + 2};
}

void Node::ConnectTo(Node* _other, float _cost)
{
	connections.push_back(Edge(_other, _cost));
}

void Node::Update(float _dt)
{
	
}

void Node::DrawEdge()
{
	for (int i = 0; i < connections.size(); i++)
	{
		Node* connection = connections[i].target;

		if (connection->type == Path && type == Path || connection->type == Path && type == End)
		{
			DrawLine(m_size / 2.2f + pos.x, m_size / 2.2f + pos.y,
				m_size / 2.2f + connection->pos.x, m_size / 2.2f + connection->pos.y, BLACK);
		}
	}
}

void Node::Draw()
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
		m_size - m_space , m_size - m_space, color);
}


