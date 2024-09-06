#pragma once

#include "../Core/Nodes/INavigatable.h"
#include "../Core/Nodes/HashTable.h"
#include "../Agents/Agent.h"

#include <Azimuth/Resources/TextureResource.h>
#include <Azimuth/Resources/Resources.h>

class Spartan: public Agent
{
public:
	Spartan(const char* _name, INavigatable* _map, HashTable* _table, Behaviour* _behaviour, int _speed, Color _color, GameStateManager* _gsMan, GameObjectManager* _goMan);
	~Spartan();

	virtual void Load();
	virtual void Update(float _dt);
	virtual void Draw();
	void DrawVeiw();
	void DrawName();

	void Controls(float _dt);
	void HashTableCheck();
	void CheckNext();
	void CalculateRot();
	void SeenTimer(float _dt);
public:
	float timer;
	bool seen;

private:
	float m_spread;
	float m_spreadMin;
	float m_spreadMax;
};

