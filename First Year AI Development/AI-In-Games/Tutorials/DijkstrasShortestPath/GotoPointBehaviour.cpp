#include "GotoPointBehaviour.h"
#include "NodeMap.h"
#include "Agent.h"

#include <raylib/raylib.h>

void GotoPointBehaviour::Update(Agent* _agent, float _dt)
{	
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{		
		vec2 mosPos = { GetMousePosition().x, GetMousePosition().y };
		_agent->GoTo(mosPos);
	}	
}

void GotoPointBehaviour::Enter(Agent* _agent)
{
}

void GotoPointBehaviour::Exit(Agent* _agent)
{
}


