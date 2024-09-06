#include "GameState.h"
#include "PlayState.h"

#include <Azimuth/GameStates/GameStateManager.h>

void GameState::Load(GameStateManager* _gsMan, GameObjectManager* _goMan)
{
	_gsMan->AddState(new PlayState(_gsMan, _goMan));
	_gsMan->ActivateState("Play");
}