#pragma once

#include "PathAgent.h"
#include "NodeMap.h"

#include <raylib/raylib.h>
#include <Azimuth/GameObjects/GameObject.h>
#include <Azimuth/GameObjects/GameObjectManager.h>
#include <Azimuth/GameStates/GameStateManager.h>
#include <vector>

using std::vector;

class SpartanAgent;
class HashTable;
class Behaviour;
class Node;

class Agent : public GameObject
{
public:
	Agent(const char* _name, NodeMap* _map, Behaviour* _behaviour, int _speed, Color _color, GameStateManager* _gsMan, GameObjectManager* _goMan);
	~Agent();

	virtual void Load();
	virtual void Update(float _dt);
	virtual void Draw();

	void GoTo(vec2 _point);
	void Reset() { m_pathAgent.path.clear(); }
	bool PathComplete() { return m_pathAgent.path.empty(); }

#pragma region Setters
	void SetCurrentNode(vec2 _nodePos) { m_pathAgent.currentNode = _nodePos; }
	void SetTargetEnemy(SpartanAgent* _agent) { m_spartan = _agent; }
	void SetTarget(CovenantBaseAgent* _agent) { m_pathAgent.target = _agent; }
	void SetPos(vec2 _pos) { m_pathAgent.pos = _pos; }
	void SetBehaviour(Behaviour* _b);
	void SetSpeed(int _speed) { m_pathAgent.speed = _speed; }
	void SetColor(Color _color) { m_pathAgent.color = _color; }
#pragma endregion

#pragma region Getters
	SpartanAgent* GetTargetEnemy() { return m_spartan; }
	vector<Node*> GetPath() { return m_pathAgent.path; }
	vec2 GetPos() { return m_pathAgent.pos; }
	CovenantBaseAgent* GetTarget() { return m_pathAgent.target; }
	PathAgent* GetPathAgent() { return &m_pathAgent; }
	NodeMap* GetMap() { return m_map; }	
	int GetSpeed() { return m_pathAgent.speed; }

#pragma endregion

protected:
	float rotation;
	SpartanAgent* m_spartan;
	PathAgent m_pathAgent;
	Behaviour* m_behaviour;
	Behaviour* m_next;
	NodeMap* m_map;
};

