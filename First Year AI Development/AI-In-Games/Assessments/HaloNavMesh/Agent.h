#pragma once
#include <raylib/raylib.h>

#include <Azimuth/GameObjects/GameObject.h>
#include <Azimuth/GameObjects/GameObjectManager.h>
#include <Azimuth/GameStates/GameStateManager.h>
#include <Azimuth/Resources/Resource.h>
#include <Azimuth/Resources/TextureResource.h>
#include "PathAgent.h"
#include "SteeringAgent.h"

class Spartan;
class HashTable;
class Behaviour;
class INavigatable;
class CovenantAgent;

class Agent : public GameObject
{
public:
	Agent(const char* _name, INavigatable* _map, HashTable* _table, Behaviour* _behaviour, int _speed, Color _color, GameStateManager* _gsMan, GameObjectManager* _goMan);
	~Agent();

	virtual void Load();
	virtual void Update(float _dt);
	virtual void Draw();


	void GoTo(vec2 _point);
	void Reset() { GetSmoothPath().clear(); GetPath().clear(); }
	bool PathComplete() { return GetSmoothPath().empty(); }

	// Setters
	void SetCurrentQuad(int _current) { m_currentQuad = _current; }
	void SetCurrentNode(vec2 _node) { m_pathAgent.GetCurrentNode() = _node; }
	void SetTarget(CovenantAgent* _agent) { m_pathAgent.SetTarget(_agent); }
	void SetColor(Color _color) { m_pathAgent.color = _color; }
	void SetBehaviour(Behaviour* _b) { m_current = _b; }
	void SetNextBehaviour(Behaviour* _next) { m_next = _next; }
	void SetPos(vec2 _pos) { m_pathAgent.SetPos({ _pos.x + 1, _pos.y + 1 }); }
	void SetSpeed(int _speed) { m_pathAgent.SetSpeed(_speed); }
	void SetTargetEnemy(Spartan* _target) { m_spartan = _target; }
	void SetRotration(float _rot) { m_rotation = _rot; }

	// Getters
	vector<vec2> GetSmoothPath() { return m_pathAgent.GetSmoothPath(); }
	vector<NavMeshNode*> GetPath() { return m_pathAgent.GetPath(); }
	Behaviour* GetBehaviour() { return m_current; }
	Behaviour* GetNextBehaviour() { return m_next; }	
	PathAgent* GetPathAgent() { return &m_pathAgent; }
	SteeringAgent* GetSteeringAgent() { return &m_steeringAgent; }
	INavigatable* GetMap() { return m_map; }
	HashTable* GetHashTable() { return m_table; }
	Rectangle GetQuad() { return m_table->GetQuad(m_currentQuad); }
	Spartan* GetSpartanTarget() { return m_spartan; }
	CovenantAgent* GetCovenantTarget() { return m_pathAgent.GetTarget(); }
	int GetCurrentQuad() { return m_currentQuad; }
	int GetSpeed() { return m_pathAgent.GetSpeed(); }
	float GetRotation() { return m_rotation; }

protected:
	float m_rotation;
	int m_currentQuad;
	TextureResource* m_texture;
	HashTable* m_table;
	INavigatable* m_map;
	
	Spartan* m_spartan;
	PathAgent m_pathAgent;
	SteeringAgent m_steeringAgent;

	Behaviour* m_current;
	Behaviour* m_next;
};