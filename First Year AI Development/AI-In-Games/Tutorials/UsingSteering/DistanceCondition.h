#pragma once

#include "Behaviour.h"

class DistanceCondition : public Behaviour
{
public:

	DistanceCondition(float _dist, bool _bool) : m_distance(_dist), m_isTrue(_bool) { }
	virtual int Update(Agent* _agent, float _dt) override;

private:
	float m_distance;
	bool m_isTrue;
};

