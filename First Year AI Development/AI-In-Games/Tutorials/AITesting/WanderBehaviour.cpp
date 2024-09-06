#include "WanderBehaviour.h"
#include "NodeMap.h"
#include "Agent.h"

void WanderBehaviour::Enter(Agent* _agent)
{
	_agent->SetColor({ 0, 255, 255, 255 });
}

void WanderBehaviour::Update(Agent* _agent, float _dt)
{
	if (_agent->PathComplete())
	{		
		Node* node = _agent->GetMap()->GetRandomNode();
		_agent->GoTo(node->pos);
			
	}
}

void WanderBehaviour::Exit(Agent* _agent)
{
	_agent->GetPath().clear();	
}

