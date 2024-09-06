#pragma once

#include "Azimuth/Azimuth.h"

#include <list>
#include <map>
#include <functional>
#include <string>

using std::list;
using std::map;
using std::function;
using std::string;

class Application;
class IGameState;

class GameStateManager
{
public:
	DLL void ActivateState(const char* _id);
	DLL void DeactivateState(const char* _id);
	DLL void AddState(IGameState* _id);
	DLL void RemoveState(IGameState* _id);

private:
	friend class Application;

	list<IGameState*> m_active;
	list<function<void()>> m_listUpdates;
	std::map<const char*, IGameState*> m_states;

private:
	GameStateManager() = default;
	DLL ~GameStateManager();
	GameStateManager(GameStateManager&) = delete;
	GameStateManager(GameStateManager&&) = delete;

	DLL void Update(float _dt);
	DLL void Draw();
};

