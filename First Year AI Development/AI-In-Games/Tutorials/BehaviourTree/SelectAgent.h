#pragma once
#include "Agent.h"

#include "Behaviour.h"
class SelectAgent : public Agent
{
public:
	SelectAgent(NodeMap* _nodeMap, Color _color, int _speed);
	~SelectAgent() { };

	virtual void Load() override;
	virtual void Update(float _dt) override;
	virtual void Draw() override;

private:
	Behaviour* m_behaviours;
};

