#include "Node.h"

void AIForGames::Node::ConnectTo(Node* _other, float _cost)
{
	connections.push_back(Edge(_other, _cost));
}
