#pragma once

#include <Azimuth/GameStates/IGameState.h>
#include <glm/vec2.hpp>

using glm::vec2;

class PlayState : public IGameState
{
public:
	PlayState(GameStateManager* _gsMan, GameObjectManager* _goMan);

	void Load() override;
	void Update(float _dt) override;
	void Draw() override;
	void Unload() override;
	
};

