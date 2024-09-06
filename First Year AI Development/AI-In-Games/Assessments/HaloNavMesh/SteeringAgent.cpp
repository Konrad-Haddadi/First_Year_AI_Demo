#include "SteeringAgent.h"
#include "Line.h"
#include <glm/vec2.hpp>
#include <raylib/raylib.h>

#include <string>
#include <vector>

#include <Azimuth/GameObjects/ATransform.h>

using std::vector;
using std::string;
using glm::vec2;

void SteeringAgent::Update(float _dt)
{
	m_direction.x = cos(m_transform->Rotation());
	m_direction.y = sin(m_transform->Rotation());

	m_transform->UpdatePosition(_dt * m_velocity);	
	m_current->Update(this, _dt);
	CastRays();
}

void SteeringAgent::Draw()
{
	for (int i = 0; i < m_rayAmount; i++)
		DrawLine(m_rays[i].start.x, m_rays[i].start.y, m_rays[i].end.x, m_rays[i].end.y, RED);

	vector<vec2> tri = GetTrianglePoints();

	for (int i = 1; i < 3; i++)
	{
		DrawLine( tri[i].x, tri[i].y, m_transform->Position().x, m_transform->Position().y, SKYBLUE);
	}

	if(m_velocity != vec2{0,0})
		DrawLine(m_velocity.x + m_transform->Position().x, m_velocity.y + m_transform->Position().y, 
		m_transform->Position().x, m_transform->Position().y, YELLOW);
}

void SteeringAgent::CastRays()
{
	vec2 forwardPos = { 200 * m_direction.x + m_transform->Position().x , 200 * m_direction.y + m_transform->Position().y };

	m_rays[0] = { m_transform->Position(),  forwardPos };

	for (int i = 1; i < m_rayAmount; i++)
	{
		m_rays[i] = { m_transform->Position(), MakeRays(-100 + (20 * i), 20) };
	}
}

vec2 SteeringAgent::MakeRays(int _offset, int _dist)
{
	vec2 offset = { 0,0 };
	float rot = m_transform->Rotation() * RAD2DEG + _offset;

	offset.x = cos(rot * DEG2RAD);
	offset.y = sin(rot * DEG2RAD);
	
	return	{ _dist * offset.x + m_transform->Position().x , _dist * offset.y + m_transform->Position().y };
}

vector<vec2> SteeringAgent::GetTrianglePoints()
{
	vector<vec2> tri;

	tri.push_back(m_transform->Position());
	tri.push_back(MakeRays(-325, 100));
	tri.push_back(MakeRays(325, 100));

	return tri;
}


vector<vec2> SteeringAgent::GetTrianglePoints(float _range)
{
	vector<vec2> tri;

	float range = (_range - 360);

	tri.push_back(m_transform->Position());
	tri.push_back(MakeRays(-range, 100));
	tri.push_back(MakeRays(range, 100));

	return tri;
}

std::vector<vec2> SteeringAgent::GetRays()
{
	vector<vec2> rays;

	for (int i = 0; i < m_rayAmount; i++)
		rays.push_back({ m_rays[i].end.x, m_rays[i].end.y });

	return rays;
}
