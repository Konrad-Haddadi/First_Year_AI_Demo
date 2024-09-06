
#pragma once

#include "BehaviourTree.h"

class HuntTree : public BehaviourTree
{
public:
	HuntTree();
	virtual ~HuntTree() { delete m_behaviour; }

	virtual int Update(CovenantBaseAgent* _agent, float _dt) override;
};
