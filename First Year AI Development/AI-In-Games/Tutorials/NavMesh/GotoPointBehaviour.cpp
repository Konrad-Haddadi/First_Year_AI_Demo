#include "GotoPointBehaviour.h"
#include "Agent.h"

#include <raylib/raylib.h>

void GotoPointBehaviour::Update(Agent* _agent, float _dt)
{	
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	{
		DrawLine(_agent->GetPos().x, _agent->GetPos().y, GetMousePosition().x, GetMousePosition().y, YELLOW);
	}

	if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
	{		
		_agent->Reset();
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


