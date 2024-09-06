#pragma once

#include "Condition.h"

class DistanceCondition : public Condition
{
public:
	DistanceCondition(float _d, bool _lt) : m_distance(_d), m_lessThan(_lt) { }
	virtual bool IsTrue(Agent* _agent);

private:
	float m_distance;
	bool m_lessThan;
};

