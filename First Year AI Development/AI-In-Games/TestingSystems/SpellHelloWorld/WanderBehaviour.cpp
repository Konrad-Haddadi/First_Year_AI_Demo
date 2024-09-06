#include "WanderBehaviour.h"
#include "CovenantAgent.h"	
#include "Composite.h"
#include "NavMeshNode.h"


int WanderBehaviour::Update(Agent* _agent, float _dt)
{
	if (_agent->PathComplete())
	{
		vec2 point = _agent->GetMap()->GetRandomPoint();
		_agent->GoTo(point);
	}

	_agent->SetSpeed(150);
	_agent->SetColor(LIGHTGRAY);
	return Composite::Pending;
}


int WanderBehaviour::Update(CovenantAgent* _agent, float _dt)
{
	if (_agent->PathComplete())
	{
		vec2 point = _agent->GetMap()->GetRandomPoint();
		_agent->GoTo(point);

		return Composite::Pending;
	}
	return Composite::Success;
}
