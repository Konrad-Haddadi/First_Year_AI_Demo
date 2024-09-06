#pragma once

#include "BehaviourTree.h"

class GroupTree : public BehaviourTree
{
public:
	GroupTree();
	virtual ~GroupTree() { delete m_behaviour; };

	virtual int Update(CovenantBaseAgent* _agent, float _dt) override;
};