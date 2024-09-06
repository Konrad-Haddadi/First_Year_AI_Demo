#pragma once

#include "NodeMap.h"
#include "HashTable.h"
#include "Agent.h"

#include <Azimuth/Resources/TextureResource.h>
#include <Azimuth/Resources/Resources.h>

class SpartanAgent : public Agent
{
public:
	SpartanAgent(const char* _name, HashTable* _table, NodeMap* _map, Behaviour* _behaviour, int _speed, Color _color, GameStateManager* _gsMan, GameObjectManager* _goMan);
	~SpartanAgent();

	virtual void Load();
	virtual void Update(float _dt);
	virtual void Draw();

	HashTable* GetHashTable() { return m_table; }
	int GetCurrentQuad() { return m_currentQuad; }
	Rectangle GetQuad() { return m_table->GetQuad(m_currentQuad); }

private:
	HashTable* m_table;
	int m_currentQuad;
	TextureResource* m_texture;
};

