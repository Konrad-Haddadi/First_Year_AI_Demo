#pragma once

#include "Behaviour.h"

class VisionCondition : public Behaviour
{
public:

	VisionCondition(bool _bool) : m_isTrue(_bool) { }
	virtual int Update(Agent* _agent, float _dt) override;

private:
	
	bool m_isTrue;
};

