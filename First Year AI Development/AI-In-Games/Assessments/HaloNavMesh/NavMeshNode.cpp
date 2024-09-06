#include "NavMeshNode.h"

int NavMeshNode::GetAdjacentVertices(NavMeshNode* _other, vec2* _adj)
{
	int count = 0;
	for (auto v : verticies)
	{
		for (auto v2 : _other->verticies)
		{
			if (v.x == v2.x && v.y == v2.y)
			{
				_adj[count++] = v;
				break;
			}
		}
	}

	return count;
}
