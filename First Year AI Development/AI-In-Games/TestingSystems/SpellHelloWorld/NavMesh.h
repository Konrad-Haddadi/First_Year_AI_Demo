#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include "poly2tri/poly2tri.h"
#include "INavigatable.h"
#include "NavMeshNode.h"
#include <Azimuth/Resources/Resources.h>
#include <Azimuth/Resources/TextureResource.h>


using std::vector;
using glm::vec2;

class NavMeshNode;

class NavMesh : public INavigatable
{
public:

	struct Obstacle
	{
		Rectangle rect;
		float padding;
	};

	NavMesh(float _width, float _height);
	~NavMesh();

	bool AddObstacle(float _x, float _y, float _width, float _height, float _padding);
	void AddObstacles(int _num, int _width, int _height);
	void Build();
	void Draw();

	virtual void SmoothPath(PathAgent* _agnet, vec2 _end) override;


	virtual NavMeshNode* GetClosestNode(vec2 _worldPos) { return FindClosest(_worldPos); }
	virtual NavMeshNode* GetRandomNode() override;
	virtual vec2 GetRandomPoint() override;

	NavMeshNode* FindClosest(vec2 _point);	
	vector<NavMeshNode*> GetNodes() { return m_nodes; }
	vector<Obstacle> GetObstacles() { return m_obstacles; }

	vec2 extents;

protected:
	vector<Obstacle> m_obstacles;
	vector<NavMeshNode*> m_nodes;
	TextureResource* m_rocks;
	p2t::CDT* m_cdt;
	vector<vector<p2t::Point*>> m_polygons;
};

