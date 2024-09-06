#pragma once

#include "..\Condition.h"

class FSMSurroundingCondition : public Condition
{
public:
	FSMSurroundingCondition(float _d, bool _lt) : m_distance(_d), m_lessThan(_lt) { }

	virtual bool IsTrue(Agent* _agent) override;

private:
	float m_distance;
	bool m_lessThan;
};