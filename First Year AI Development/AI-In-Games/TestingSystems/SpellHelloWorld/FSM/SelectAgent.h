#pragma once
#include "../Agent.h"

class SelectAgent : public Agent
{
public:
	SelectAgent(const char* _name, int _range, INavigatable* _map, HashTable* _table, Behaviour* _behaviour, 
		int _speed, Color _color, GameStateManager* _gsMan, GameObjectManager* _goMan);

	~SelectAgent();

	virtual void Draw() override;

	Behaviour* GetFSM(int _range);

private:
	int m_range;
};

