#include "GotoPointBehaviour.h"
#include "Agent.h"
#include "Composite.h"
#include <raylib/raylib.h>

int GotoPointBehaviour::Update(CovenantBaseAgent* _agent, float _dt)
{
	return 0;
}

int GotoPointBehaviour::Update(Agent* _agent, float _dt)
{			
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{		
		_agent->GoTo({ GetMousePosition().x - 15, GetMousePosition().y - 15 });
		return Composite::Pending;
	}	

	return Composite::Failure;
}