#pragma once

#include "SteeringBehaviour.h"
#include "AvoidingBehaviour.h"
#include "Line.h"
#include "HashTable.h"
#include <Azimuth/GameObjects/ATransform.h>
#include <vector>

using std::vector;

class SteeringAgent
{
public:
	SteeringAgent(ATransform* _transform, HashTable* _table, int _currentQuad) 
		: m_transform(_transform), m_direction({0,0}), m_current(new AvoidingBehaviour), 
		m_rot(_transform->Rotation()), m_table(_table), m_velocity(0), currentQuad(_currentQuad) {}

	~SteeringAgent() { }

	void Update(float _dt);
	void Draw();

	void CastRays();
	vec2 MakeRays(int _offset, int _dist);
	void SetVelocity(vec2 _velocity) { m_velocity = _velocity; }

	int GetCurrentQuad() { return currentQuad; }
	HashTable* GetTable() { return m_table; }
	vector<vec2> GetTrianglePoints(float _range);
	vector<vec2> GetTrianglePoints();
	vector<vec2> GetRays();
	vec2 GetFurthestPoint() { return { m_rays[0].end.x, m_rays[0].end.y }; }
	ATransform* GetTransform() { return m_transform; }

public:
	int currentQuad;

private:
	SteeringBehaviour* m_current;
	ATransform* m_transform;
	HashTable* m_table;

	const static int m_rayAmount = 30;
	Line m_rays[m_rayAmount];

	vec2 m_direction;
	vec2 m_velocity;
	float m_rot;

};

