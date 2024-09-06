#include "WanderBehaviour.h"
#include "INavigatable.h"
#include "Agent.h"

void WanderBehaviour::Enter(Agent* _agent)
{
	_agent->SetColor(GREEN);
}

void WanderBehaviour::Update(Agent* _agent, float _dt)
{
	if (_agent->PathComplete())
	{		
		_agent->GoTo({ GetRandomValue(0 , GetScreenWidth()), GetRandomValue(0 , GetScreenHeight()) });
	}
}

void WanderBehaviour::Exit(Agent* _agent)
{
	_agent->GetPath().clear();	
}

