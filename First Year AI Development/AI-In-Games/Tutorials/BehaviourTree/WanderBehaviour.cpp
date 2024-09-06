#include "WanderBehaviour.h"
#include "NodeMap.h"
#include "Agent.h"
#include "Node.h"

using AITesting::NodeType;

void WanderBehaviour::Enter(Agent* _agent)
{
	_agent->SetColor(GREEN);
}

int WanderBehaviour::Update(Agent* _agent, float _dt)
{
	if (_agent->PathComplete())
	{		
		Node* node = _agent->GetMap()->GetRandomNode();

		if (node && node->type != NodeType::Wall)
			_agent->GoTo(node->pos);	
		return Composite::Failure;
	}
	return Composite::Success;
	
}

void WanderBehaviour::Exit(Agent* _agent)
{
	_agent->GetPath().clear();	
}

