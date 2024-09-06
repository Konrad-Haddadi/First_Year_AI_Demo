#include "NavMesh.h"
#include "NavMeshNode.h"
#include "Line.h"
#include "PathAgent.h"

#include "poly2tri/poly2tri.h"
#include <glm/vec2.hpp>
#include <glm/glm.hpp>
#include <raylib/raylib.h>

using p2t::Point;
using p2t::CDT;
using p2t::Triangle;
using glm::vec2;

NavMesh::NavMesh(float _width, float _height)
{
	m_polygons.push_back({});
	m_polygons[0].push_back(new Point(0, 0));
	m_polygons[0].push_back(new Point(0, _height));
	m_polygons[0].push_back(new Point(_width, _height));
	m_polygons[0].push_back(new Point(_width, 0));

	m_cdt = new CDT(m_polygons[0]);

	extents = vec2(_width, _height);
}

NavMesh::~NavMesh()
{
}

bool NavMesh::AddObstacle(float _x, float _y, float _width, float _height, float _padding)
{
	for (auto& ob : m_obstacles)
	{
		if (((ob.x + ob.w + ob.padding) < _x - _padding ||
			(ob.y + ob.h + ob.padding) < _y - _padding ||
			(_x + _width + _padding) < ob.x - ob.padding ||
			(_y + _height + _padding) < ob.y - ob.padding) == false)
			return false;
	}

	Obstacle o = { _x, _y, _width, _height, _padding };
	m_obstacles.push_back(o);

	m_polygons.push_back({});
	m_polygons.back().push_back(new Point(o.x - _padding, o.y - _padding));
	m_polygons.back().push_back(new Point(o.x - _padding, o.y + o.h + _padding));
	m_polygons.back().push_back(new Point(o.x + o.w + _padding, o.y + o.h + _padding));
	m_polygons.back().push_back(new Point(o.x + o.w + _padding, o.y - _padding));
	m_cdt->AddHole(m_polygons.back());

	return true;
}

void NavMesh::AddObstacles(int _num, int _width, int _height)
{
	for (int i = 0; i < _num; i++)
	{
		bool safe = false;

		do
		{
			safe = AddObstacle((rand() / float(RAND_MAX) * 0.75f + 0.125f) * extents.x, (rand() / float(RAND_MAX) * 0.75f + 0.125f) * extents.y,
				_width, _height,
				15);
		} while (safe == false);
	}
}


void NavMesh::Build()
{
	m_cdt->Triangulate();

	vector<Triangle*> triangles = m_cdt->GetTriangles();

	for (auto tri : triangles)
	{
		auto node = new NavMeshNode();

		node->verticies.push_back({ (float)tri->GetPoint(0)->x, (float)tri->GetPoint(0)->y });
		node->verticies.push_back({ (float)tri->GetPoint(1)->x, (float)tri->GetPoint(1)->y });
		node->verticies.push_back({ (float)tri->GetPoint(2)->x, (float)tri->GetPoint(2)->y });

		node->pos.x = (node->verticies[0].x + node->verticies[1].x + node->verticies[2].x) / 3;
		node->pos.y = (node->verticies[0].y + node->verticies[1].y + node->verticies[2].y) / 3;
		
		m_nodes.push_back(node);
	}

	for (auto n : m_nodes)
	{
		for (auto n2 : m_nodes)
		{
			if (n == n2) 
				continue;

			vec2 v[2];
			if (n->GetAdjacentVertices(n2, v) == 2)
			{
				float mag = (n->pos.x - n2->pos.x) *
					(n->pos.x - n2->pos.x) +
					(n->pos.y - n2->pos.y) *
					(n->pos.y - n2->pos.y);

				float dist = glm::distance(n->pos, n2->pos);

				NavMeshNode::Edge e1 = NavMeshNode::Edge(n2, dist);
				NavMeshNode::Edge e2 = NavMeshNode::Edge(n, dist);

				n->connections.push_back(e1);
				n2->connections.push_back(e2);
			}
		}
	}

	for (auto& p : m_polygons)
	{
		for (auto ptr : p)
			delete ptr;
	}

	m_polygons.clear();

	delete m_cdt;
	m_cdt = nullptr;
}

void NavMesh::Draw()
{
	Color lineColor = BLUE;
	Color obstacleColor = WHITE;

	for (auto node :  GetNodes())
	{
		for (auto v : node->verticies)
		{
			//DrawLine(node->pos.x, node->pos.y, v.x, v.y, RED);
		}

		DrawLine((int)node->verticies[0].x, (int)node->verticies[0].y, (int)node->verticies[1].x, (int)node->verticies[1].y, lineColor);
		DrawLine((int)node->verticies[1].x, (int)node->verticies[1].y, (int)node->verticies[2].x, (int)node->verticies[2].y, lineColor);
		DrawLine((int)node->verticies[2].x, (int)node->verticies[2].y, (int)node->verticies[0].x, (int)node->verticies[0].y, lineColor);
	}

	for (auto o : GetObstacles())
		DrawRectangle(o.x, o.y, o.w, o.h, obstacleColor);
}

NavMeshNode* NavMesh::GetRandomNode()
{
	int index = rand() % m_nodes.size();

	if (m_nodes[index])
		return m_nodes[index];
	else
		return GetRandomNode();
}

NavMeshNode* NavMesh::FindClosest(vec2 _point)
{
	NavMeshNode* close = nullptr;
	float dist = FLT_MAX;

	Vector2 point = {_point.x, _point.y};
	for (int x = 0; x < m_nodes.size(); x++)
	{
		NavMeshNode* node = m_nodes[x];
		float nodeDist = glm::distance(node->pos, _point);

		if (nodeDist < dist)
		{
			dist = nodeDist;
			close = node;
		}

		Vector2 a = { node->verticies[0].x, node->verticies[0].y };
		Vector2 b = { node->verticies[1].x, node->verticies[1].y };
		Vector2 c = { node->verticies[2].x, node->verticies[2].y };
		
		

		if (CheckCollisionPointTriangle(point, a, b, c))
			return m_nodes[x];
	}
	
	return close;
}


bool TriCollision(vec2 _point, vec2 _a, vec2 _b, vec2 _c)
{
	return CheckCollisionPointTriangle({ _point.x, _point.y }, { _a.x, _a.y }, { _b.x, _b.y }, { _c.x, _c.y });
}

void NavMesh::SmoothPath(PathAgent* _agent, vec2 _end)
{	
	vector<vec2>* smoothPath = &_agent->GetSmoothPath();

	smoothPath->clear();

	NavMeshNode* currentNm = FindClosest(_agent->GetPos());

	if (TriCollision(_end, currentNm->verticies[0], currentNm->verticies[1], currentNm->verticies[2]))
	{
		smoothPath->push_back(_end);
		return;
	}


	vector<NavMeshNode*> path = _agent->GetPath();	
	vector<Line> portals;

	if (!path.empty())
	{
		for (int i = 0; i < path.size() - 1; i++)
		{
			Line l = {};

			for (auto v1 : path[i]->verticies)
			{
				for (auto v2 : path[i + 1]->verticies)
				{
					if (v1 == v2)
					{
						if (!l.HasStart())
							l.start = { v1.x, v1.y };
						else if (!l.HasEnd())
							l.end = { v1.x, v1.y };
						break;
					}
				}
			}

			if (l.HasStart() || l.HasEnd())
				portals.push_back(l);
		}
	}
	
	vec2 currentPoint = _agent->GetPos();

	for (Line l : portals)
	{
		vec2* point = l.DoesIntersect({ currentPoint,  _end });

		if (point)
			currentPoint = *point;		
		else
			currentPoint = l.GetClosestPoint((currentPoint + _end) / 2.0f);
		
		smoothPath->push_back(currentPoint);
	}

	smoothPath->push_back(_end);
}

