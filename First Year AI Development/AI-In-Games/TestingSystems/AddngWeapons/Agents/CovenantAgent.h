#pragma once

#include "PathAgent.h"
#include "Agent.h"
#include "HashTable.h"
#include <raylib/raylib.h>
#include <vector>

using std::vector;

class HashTable;
class Behaviour;
class Node;
class SpartanAgent;

enum CovenantType
{
	Grunt,
	GruntC,
	Elite,
	EliteC
};

class CovenantAgent : public Agent
{
public:
	CovenantAgent(vec2 _pos, HashTable* _table, const char* _name, INavigatable* _map, int _type, int _speed, GameStateManager* _gsMan, GameObjectManager* _goMan);
	CovenantAgent(vec2 _pos, HashTable* _table, INavigatable* _map, int _type, int _speed, GameStateManager* _gsMan, GameObjectManager* _goMan);
	~CovenantAgent();

	virtual void Load();
	virtual void Update(float _dt);
	virtual void Draw();

	void AddToSquad(CovenantAgent* _agent) { m_squad.push_back(_agent); }
	void RemoveFromSquad(CovenantAgent* _agent) { m_squad.remove(_agent); }

#pragma region Getters	

	list<CovenantAgent*> GetSquad() { return m_squad; }
	int GetRange() { return 200; }
	int GetRank() { return m_type; }
	int GetBaseSpeed() { return (GetRank() * 50) / 2 + 50; }
	const char* GetTypeName(int _type);
	int CheckSquadSize();
	Color GetTypeColor(int _type);

#pragma endregion
	Color enemyColor;
	bool fleeing;

protected:
	list<CovenantAgent*> m_squad;
	int m_type;
};

