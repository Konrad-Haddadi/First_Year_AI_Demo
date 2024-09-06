#include "SelectBehaviour.h"
#include "Composite.h"
#include "Agent.h"
#include "NodeMap.h"
#include <glm/glm.hpp>

int SelectBehaviour::Update(Agent* _agent, float _dt)
{
	if (glm::distance(_agent->GetPos(), _agent->GetTarget()->GetPos()) < _agent->GetMap()->GetCellSize() * 5)
	{
		SetBehaviour(m_b1, _agent);
		_agent->SetColor({ORANGE});
		return Composite::Success;
	}
	else
	{
		SetBehaviour(m_b2, _agent);
		_agent->SetColor(RED);
		return Composite::Failure;
	}

	m_selected->Update(_agent, _dt);
}

void SelectBehaviour::SetBehaviour(Behaviour* _b, Agent* _agent)
{
	if (m_selected != _b)
	{
		m_selected = _b;
		_agent->Reset();
	}
}
