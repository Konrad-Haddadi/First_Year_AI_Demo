#include "SpartanAgent.h"
#include "Agent.h"
#include "Behaviour.h"
#include "QuadTree.h"
#include <Azimuth/GameObjects/ATransform.h>

SpartanAgent::SpartanAgent(const char* _name, QuadTree* _quadTree, NodeMap* _map, Behaviour* _behaviour, int _speed, Color _color, GameStateManager* _gsMan, GameObjectManager* _goMan)
	: Agent(_name, _quadTree, _map, _behaviour, _speed, _color, _gsMan, _goMan)
{

}

SpartanAgent::~SpartanAgent()
{
	delete m_behaviour;
}

void SpartanAgent::Load()
{
	
}

void SpartanAgent::Update(float _dt)
{
	vec2 rot = m_pathAgent.currentNode + vec2{10, 10} - Transform()->Position();
	float rotation = atan2(rot.x, rot.y);

	rotation = rotation * RAD2DEG;
	rotation += 90;

	if (m_behaviour)
		m_behaviour->Update(this, _dt);

	m_pathAgent.Update(_dt);
	
	Transform()->TRS(GetPos(), rotation, { m_pathAgent.size,m_pathAgent.size });	
}

void SpartanAgent::Draw()
{
	m_pathAgent.Draw();
	DrawText(GetName(), m_pathAgent.pos.x - TextLength(GetName()) + 1, m_pathAgent.pos.y - 19, 15, BLACK);
	DrawText(GetName(), m_pathAgent.pos.x - TextLength(GetName()) + 1, m_pathAgent.pos.y - 20, 15, m_pathAgent.color);
	
	/*if(!m_pathAgent.IsEmpty())
		DrawRectanglePro({ GetPos().x + 10, GetPos().y +10, 10, 50 }, { 5, 50 }, Transform()->Rotation(), GREEN);*/

}