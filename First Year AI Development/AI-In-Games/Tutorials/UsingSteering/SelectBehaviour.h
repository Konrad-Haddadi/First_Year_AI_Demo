#pragma once

#include "Behaviour.h"

class SelectBehaviour : public Behaviour
{
public:
	SelectBehaviour(Behaviour* _b1, Behaviour* _b2) : m_b1(_b1), m_b2(_b2) { }
	virtual int Update(Agent* _agent, float _dt);

	void SetBehaviour(Behaviour* _b, Agent* _agent);
private:
	Behaviour* m_b1;
	Behaviour* m_b2;
	Behaviour* m_selected;
};

