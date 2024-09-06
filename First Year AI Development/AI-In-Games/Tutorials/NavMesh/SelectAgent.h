#pragma once
#include "Agent.h"

class SelectAgent : public Agent
{
public:
	SelectAgent(INavigatable* _nodeMap, Color _color, int _speed);
	~SelectAgent();

	void Load();

private:
};

