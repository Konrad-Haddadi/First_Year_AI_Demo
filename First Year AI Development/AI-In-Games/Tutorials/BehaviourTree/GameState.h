#pragma once
#include <Azimuth/Game.h>

class GameState : public Game
{
	// Inherited via Game
	virtual void Load(GameStateManager* _gsMan, GameObjectManager* _goMan) override;
};