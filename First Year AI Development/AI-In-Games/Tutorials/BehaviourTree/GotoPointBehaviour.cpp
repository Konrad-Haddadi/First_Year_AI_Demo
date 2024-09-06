#include "GotoPointBehaviour.h"
#include "NodeMap.h"
#include "Agent.h"
#include "Composite.h"
#include <raylib/raylib.h>

void GotoPointBehaviour::Enter(Agent* _agent)
{
	_agent->GetPath().clear();
}

int GotoPointBehaviour::Update(Agent* _agent, float _dt)
{	
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
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


