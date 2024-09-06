#include "../FleeBehaviour.h"
#include "../../Agents/CovenantAgent.h"	
#include "../../Agents/Spartan.h"
#include "../../Agents/Agent.h"
#include "../BehaviourTree/Composite/Composite.h"
#include "../../Core/Nodes/HashTable.h"
#include <glm/glm.hpp>
#include <Azimuth/GameObjects/ATransform.h>

bool InRange(CovenantAgent* _covenant, Spartan* _spartan);

int FleeBehaviour::Update(Agent* _agent, float _dt)
{	
	list<CovenantAgent*> covenant = *_agent->GetHashTable()->GetCovenant(_agent->GetCurrentQuad());

	for (auto c : covenant)
	{
		float dist = glm::distance(c->Transform()->Position(), _agent->Transform()->Position());

		if (dist < 300)
		{
			Rectangle emenyQuad = c->GetQuad();
			vec2 point = _agent->GetMap()->GetRandomPoint();
			_agent->SetSpeed(400);

			while (CheckCollisionCircleRec({ point.x, point.y }, 15, emenyQuad))
				point = _agent->GetMap()->GetRandomPoint();
			
			if (_agent->PathComplete())
				_agent->GoTo({ point.x, point.y });
			
			
		}		
	}	

	_agent->SetColor(YELLOW);
	return Composite::Success;
}

int FleeBehaviour::Update(CovenantAgent* _agent, float _dt)
{	
	Spartan* target = _agent->GetSpartanTarget();

	if (target)
	{
		float dist = glm::distance(target->Transform()->Position(), _agent->Transform()->Position());

		if (dist < 200 * (2 - _agent->GetRank()) || _agent->GetCurrentQuad() == target->GetCurrentQuad())
		{
			Rectangle emenyQuad = target->GetQuad();
			vec2 point = _agent->GetMap()->GetRandomPoint();
			_agent->enemyColor = PURPLE;
			_agent->SetSpeed(400);
			_agent->fleeing = true;

			while (CheckCollisionCircleRec({ point.x, point.y }, 15, emenyQuad))
				point = _agent->GetMap()->GetRandomPoint();

			if (_agent->PathComplete())
			{
				_agent->GoTo({ point.x, point.y });
			}
			return Composite::Pending;
		}
		else
		{
			_agent->fleeing = true;
			_agent->enemyColor = RED;
			_agent->SetTargetEnemy(nullptr);
			_agent->SetSpeed(200);
			return Composite::Success;
		}
	}	
}

bool InRange(CovenantAgent* _covenant, Spartan* _spartan)
{
	if (_covenant->GetCurrentQuad() == _spartan->GetCurrentQuad() ||
		_covenant->GetCurrentQuad() == _spartan->GetCurrentQuad() + 8 ||
		_covenant->GetCurrentQuad() == _spartan->GetCurrentQuad() - 8 ||
		_covenant->GetCurrentQuad() == _spartan->GetCurrentQuad() + 1 ||
		_covenant->GetCurrentQuad() == _spartan->GetCurrentQuad() - 1)
		return true;

	return false;
}
