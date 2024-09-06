#pragma once

#include "Azimuth/Azimuth.h"

class GameStateManager;
class GameObjectManager;
class ATransform;

class GameObject
{
public:
	DLL GameObject(const char* _name, GameStateManager* _gsMan, GameObjectManager* _goMan);
	DLL virtual ~GameObject();

	virtual void Load() {}
	virtual void Update(float _dt) {}
	virtual void Draw() {}
	virtual void Unload() {}
	
	DLL void SetName(const char* _name);
	DLL void SetTag(const char* _tag);

	DLL const char* GetName() const;
	DLL const char* GetTag() const;

	DLL ATransform* Transform() const;

protected:
	GameStateManager* m_stateManeger;
	GameObjectManager* m_objectManager;

private:

	ATransform* m_transform;

	const char* m_name;
	const char* m_tag;
};

