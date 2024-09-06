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
		Node* node = _agent->GetNodeMap()->GetRandomNode();

		if(node)
			_agent->GoTo(_agent->GetNodeMap()->GetRandomNode()->pos);
	}
}

void WanderBehaviour::Exit(Agent* _agent)
{
	_agent->GetPath().clear();	
}

