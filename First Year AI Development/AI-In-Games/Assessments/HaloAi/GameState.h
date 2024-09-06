#pragma once
#include <Azimuth/Game.h>

class GameState : public Game
{
	// Inherited via Game
	virtual void Load(GameStateManager* _gsMan, GameObjectManager* _goMan) override;
	virtual void Unload() {}

	virtual void Draw() {}
	virtual void Update(float _dt) {}
};