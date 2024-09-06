#pragma once

#include "PathAgent.h"
#include "NodeMap.h"
#include "Agent.h"

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

class CovenantBaseAgent : public Agent
{
public:
	CovenantBaseAgent(const char* _name, QuadTree* _quadTree, NodeMap* _map, int _type, int _speed, GameStateManager* _gsMan, GameObjectManager* _goMan);
	CovenantBaseAgent(QuadTree* _quadTree, NodeMap* _map, int _type, int _speed, GameStateManager* _gsMan, GameObjectManager* _goMan);
	~CovenantBaseAgent();

	virtual void Load();
	virtual void Update(float _dt);
	virtual void Draw();
	
	void AddToSquad(CovenantBaseAgent* _agent) { m_squad.push_back(_agent); }
	void RemoveFromSquad(CovenantBaseAgent* _agent) { m_squad.remove(_agent); }
	HashTable* GetHashTable() { return m_table; }

#pragma region Getters	

	list<CovenantBaseAgent*> GetSquad() { return m_squad; }
	int GetRange() { return GetMap()->GetCellSize() * 5 + GetRank() * GetMap()->GetCellSize(); }
	int GetRank() { return m_type; }	
	int GetBaseSpeed() { return (GetRank() * 50) / 2 + 50; }
	int GetCurrentQuad() { return 0; }
	Rectangle GetQuad(int _quad) { return m_table->GetQuad(_quad); }
	const char* GetTypeName(int _type);
	Color GetTypeColor(int _type);
#pragma endregion

	Color enemyColor;
protected:	


	list<CovenantBaseAgent*> m_squad;	
	HashTable* m_table;
	bool fleeing;
	int m_type;
};

