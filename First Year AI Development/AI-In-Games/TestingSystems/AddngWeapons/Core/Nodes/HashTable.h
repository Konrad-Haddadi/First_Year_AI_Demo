#pragma once

#include <list>
#include <vector>
#include <raylib/raylib.h>
#include <glm/glm.hpp>
#include "NavMesh.h"

using glm::vec2;
using std::vector;
using std::list;

class NavMesh;
class CovenantAgent;
class Spartan;

class HashTable
{
public:
	HashTable(NavMesh* _navMesh);
	~HashTable();
	
	void Load();

	int CheckQuad(vec2 _point);	
	int UpdateQuad(CovenantAgent* _agent);
	int UpdateQuad(Spartan* _agent);
	int UpdateQuad(Rectangle _bounds);
	void AddToQuad(int _num, CovenantAgent* _agent);
	void AddToQuad(int _num, Spartan* _agent);
	void Draw();

	bool HasMoved(int _quad, CovenantAgent* _agent);
	bool HasMoved(int _quad, Spartan* _agent);

	void RemoveFromQuad(CovenantAgent* _agent);
	void RemoveFromQuad(Spartan* _agent);

	list<CovenantAgent*>* GetCovenant(int _quad);
	list<Spartan*>* GetSpartan(int _quad);
	list<Rectangle>* GetObjects(int _quad);
	vector<Rectangle>* GetAllQuads();
	Rectangle GetQuad(int _quad);

private:
	vector<list<CovenantAgent*>> m_covenantTable;
	vector<list<Spartan*>> m_spartanTable;
	vector<list<Rectangle>> m_objectTable;
	vector<Rectangle> m_quadrents;

	NavMesh* m_navMesh;

};

