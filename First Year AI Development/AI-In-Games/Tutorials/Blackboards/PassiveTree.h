#pragma once

#include "BehaviourTree.h"

class PassiveTree : public BehaviourTree
{
public:
	PassiveTree();
	virtual ~PassiveTree() { delete m_behaviour; }

	virtual int Update(CovenantBaseAgent* _agent, float _dt) override;
};

