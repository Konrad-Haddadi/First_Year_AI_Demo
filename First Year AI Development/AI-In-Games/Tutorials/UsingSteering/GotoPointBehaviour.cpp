#include "GotoPointBehaviour.h"
#include "NodeMap.h"
#include "Agent.h"
#include "Composite.h"
#include <raylib/raylib.h>

void GotoPointBehaviour::Enter(Agent* _agent)
{
	_agent->Reset();
}

int GotoPointBehaviour::Update(Agent* _agent, float _dt)
{	
	if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
	{		
		vec2 mosPos = { GetMousePosition().x, GetMousePosition().y };
		_agent->GoTo(mosPos);

		return Composite::Success;
	}	

	return Composite::Failure;
}

void GotoPointBehaviour::Exit(Agent* _agent)
{

}


