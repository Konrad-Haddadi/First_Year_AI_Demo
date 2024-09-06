#pragma once

#include "BehaviourTree.h"

class SearchTree : public BehaviourTree
{
public:
	SearchTree();
	virtual ~SearchTree() { delete m_behaviour; }

	virtual int Update(CovenantAgent* _agent, float _dt) override;
};
