#pragma once

#include "NodeMap.h"
#include "HashTable.h"
#include "Agent.h"

class SpartanAgent : public Agent
{
public:
	SpartanAgent(const char* _name, QuadTree* _quadTree, NodeMap* _map, Behaviour* _behaviour, int _speed, Color _color, GameStateManager* _gsMan, GameObjectManager* _goMan);
	~SpartanAgent();

	virtual void Load();
	virtual void Update(float _dt);
	virtual void Draw();

	HashTable* GetHashTable() { return nullptr; }
	int GetCurrentQuad() { return 0; }
	Rectangle GetQuad() { return {}; }
};

