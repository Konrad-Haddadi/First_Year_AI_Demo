#include "GotoPointBehaviour.h"
#include "Agent.h"
#include "Composite.h"
#include <raylib/raylib.h>
#include <Azimuth/GameObjects/ATransform.h>
int GotoPointBehaviour::Update(CovenantAgent* _agent, float _dt)
{
	return 0;
}

int GotoPointBehaviour::Update(Agent* _agent, float _dt)
{	
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
		DrawLine(_agent->Transform()->Position().x, _agent->Transform()->Position().y, GetMousePosition().x, GetMousePosition().y, PINK);	

	if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
	{		
		_agent->GoTo({ GetMousePosition().x, GetMousePosition().y});
		return Composite::Pending;
	}	

	return Composite::Failure;
}