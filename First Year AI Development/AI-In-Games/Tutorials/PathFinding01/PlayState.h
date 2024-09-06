#pragma once

#include <Azimuth/Game.h>

class PlayState : public Game
{
public:
	void Load(GameStateManager* _gsMan, GameObjectManager* _goMan) override;
	void Update(float _dt) override;
	void Draw() override;
	void Unload() override;
};

