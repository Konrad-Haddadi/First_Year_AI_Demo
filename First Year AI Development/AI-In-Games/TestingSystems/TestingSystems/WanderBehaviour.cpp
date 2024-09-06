#include "WanderBehaviour.h"
#include "CovenantBaseAgent.h"	
#include "Composite.h"
#include "NodeMap.h"
#include "Node.h"


int WanderBehaviour::Update(Agent* _agent, float _dt)
{
	return 0;	
}

int WanderBehaviour::Update(CovenantBaseAgent* _agent, float _dt)
{
	if (_agent->PathComplete())
	{
		Node* node = _agent->GetMap()->GetRandomNode();
		_agent->GoTo(node->pos);

		return Composite::Pending;
	}
	return Composite::Success;
}
