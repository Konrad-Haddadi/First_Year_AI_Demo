#pragma once

#include <list>
#include <vector>
#include <raylib/raylib.h>
#include <glm/glm.hpp>

using glm::vec2;
using std::vector;
using std::list;

class CovenantBaseAgent;
class SpartanAgent;

class HashTable
{
public:
	HashTable();
	~HashTable();
	
	void Load();
	int UpdateQuad(CovenantBaseAgent* _agent);
	int UpdateQuad(SpartanAgent* _agent);
	void AddToQuad(int _num, CovenantBaseAgent* _agent);
	void AddToQuad(int _num, SpartanAgent* _agent);
	void Draw();

	bool HasMoved(int _quad, CovenantBaseAgent* _agent);
	bool HasMoved(int _quad, SpartanAgent* _agent);
	list<CovenantBaseAgent*>* GetCovenant(int _quad);
	list<SpartanAgent*> GetSpartan(int _quad);
	Rectangle GetQuad(int _quad);

private:
	vector<list<CovenantBaseAgent*>> m_covenantTable;
	vector<list<SpartanAgent*>> m_spartanTable;
	vector<Rectangle> m_quadrents;

};

