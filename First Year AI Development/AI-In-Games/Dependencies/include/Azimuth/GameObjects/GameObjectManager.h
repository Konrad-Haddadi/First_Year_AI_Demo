#pragma once

#include "Azimuth/Azimuth.h"

#include <list>
#include <functional>

using std::list;
using std::function;

class GameObject;

class GameObjectManager
{
public:
	DLL void Spawn(GameObject* _go);
	DLL void Destroy(GameObject* _go);
	DLL list<GameObject*> FindObjectsWithTag(const char* _tag);
	DLL list<GameObject*> GetALl();

private:
	friend class Application;

	list<GameObject*> m_gameObjects;
	list<function<void()>> m_listUpdates;

private:
	DLL GameObjectManager();
	DLL ~GameObjectManager();

	GameObjectManager(GameObjectManager&) = delete;
	GameObjectManager(GameObjectManager&&) = delete;

	DLL void Update(float _dt);
	DLL void Draw();

};


