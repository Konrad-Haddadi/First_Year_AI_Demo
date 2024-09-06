#pragma once

#include "Azimuth/Azimuth.h"
#include <string>

using std::string;

class GameStateManager;
class GameObjectManager;
class GameObject;

class IGameState
{
public:
	DLL GameObject* GetWorld() const;
	DLL const char* GetID() const;

protected:
	friend class GameStateManager;

	GameStateManager* m_stateManager;
	GameObjectManager* m_objectManager;

protected:
	IGameState() = delete;

	DLL IGameState(const char* _id, GameStateManager* _gsMan, GameObjectManager* _goMan);
	IGameState(IGameState&) = delete;
	IGameState(IGameState&&) = delete;
	DLL virtual ~IGameState();

	virtual void Load() {}
	virtual void Update(float _dt) {}
	virtual void Draw() {}
	virtual void Unload() {}

	DLL GameObject* CreateObject(const char* _name);
	DLL void DestroyObject(GameObject* _go);

private:
	GameObject* m_world;
	const char* m_id;
};

