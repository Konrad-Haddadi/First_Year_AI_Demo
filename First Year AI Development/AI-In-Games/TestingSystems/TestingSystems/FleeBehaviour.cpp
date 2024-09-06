#include "FleeBehaviour.h"
#include "CovenantBaseAgent.h"	
#include "SpartanAgent.h"
#include "Composite.h"
#include "NodeMap.h"
#include "Node.h"
#include <glm/glm.hpp>

bool InRange(CovenantBaseAgent* _covenant, SpartanAgent* _spartan);

int FleeBehaviour::Update(Agent* _agent, float _dt)
{
	return 0;
}

int FleeBehaviour::Update(CovenantBaseAgent* _agent, float _dt)
{
	SpartanAgent* target = _agent->GetTargetEnemy();
	float dist = 0;

	if (!target)
	{
		_agent->enemyColor = RED;
		_agent->SetTargetEnemy(nullptr);
		_agent->SetSpeed(_agent->GetBaseSpeed());
		return Composite::Success;
	}

	if (target)
		dist = glm::distance(target->GetPos(), _agent->GetPos());

	if (dist < _agent->GetRange() || InRange(_agent, target))
	{
		Rectangle emenyQuad = _agent->GetTargetEnemy()->GetQuad();
		Node* node = _agent->GetMap()->GetRandomNode();

		while (CheckCollisionRecs({ node->pos.x, node->pos.y, (float)node->GetSize(), (float)node->GetSize() }, emenyQuad))
		{
			node = _agent->GetMap()->GetRandomNode();
		}

		if (_agent->PathComplete())
		{
			_agent->SetSpeed(150);
			_agent->GoTo(node->pos);
			_agent->enemyColor = PURPLE;
		}
		return Composite::Pending;
	}
	else
	{
		_agent->enemyColor = RED;
		_agent->SetTargetEnemy(nullptr);
		_agent->SetSpeed(_agent->GetBaseSpeed());
		return Composite::Success;
	}
}

bool InRange(CovenantBaseAgent* _covenant, SpartanAgent* _spartan)
{
	if (_covenant->GetCurrentQuad() == _spartan->GetCurrentQuad() ||
		_covenant->GetCurrentQuad() == _spartan->GetCurrentQuad() + 8 ||
		_covenant->GetCurrentQuad() == _spartan->GetCurrentQuad() - 8 ||
		_covenant->GetCurrentQuad() == _spartan->GetCurrentQuad() + 1 ||
		_covenant->GetCurrentQuad() == _spartan->GetCurrentQuad() - 1)
		return true;

	return false;
}
