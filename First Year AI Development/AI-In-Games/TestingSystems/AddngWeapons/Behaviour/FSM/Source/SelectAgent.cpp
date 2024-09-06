#include "SelectAgent.h"

#include "State.h"
#include "FiniteStateMachine.h"
#include "FSMDistanceCondition.h"
#include "FSMSurroundingCondition.h"

#include "..\GotoPointBehaviour.h"
#include "..\FollowBehavoiur.h"
#include "..\WanderBehaviour.h"
#include "..\FleeBehaviour.h"
#include "..\Condition.h"

SelectAgent::SelectAgent(const char* _name, int _range, INavigatable* _map, HashTable* _table, Behaviour* _behaviour, int _speed, Color _color, GameStateManager* _gsMan, GameObjectManager* _goMan)
	: Agent(_name, _map, _table, GetFSM(_range), _speed, _color, _gsMan, _goMan), m_range(_range)
{	
	m_texture = Resources::Find<Texture2D, TextureResource>("textures/GuiltySpark");
}

SelectAgent::~SelectAgent()
{
	delete m_current;
	delete m_next;

	m_current = nullptr;
	m_next = nullptr;
	m_table = nullptr;
	m_map = nullptr;
	m_spartan = nullptr;
}

void SelectAgent::Draw()
{	
	if(IsKeyDown(KEY_GRAVE))
		DrawCircle(Transform()->Position().x, Transform()->Position().y, m_range, { 100,0,0, 50 });
	else
		DrawTextureEx(*m_texture, { Transform()->Position().x + 10, Transform()->Position().y + 10 }, 0, 0.3f, WHITE);
	
	m_pathAgent.Draw();
	
	DrawText(GetName(), Transform()->Position().x - TextLength(GetName()) + 1, Transform()->Position().y - 19, 15, BLACK);
	DrawText(GetName(), Transform()->Position().x - TextLength(GetName()) + 1, Transform()->Position().y - 20, 15, m_pathAgent.color);	
}

Behaviour* SelectAgent::GetFSM(int _range)
{
	FSMDistanceCondition* inRange = new FSMDistanceCondition(_range, true);
	FSMDistanceCondition* outOfRange = new FSMDistanceCondition(_range, false);
	FSMSurroundingCondition* surroundingEnemy = new FSMSurroundingCondition(_range, true);
	FSMSurroundingCondition* surroundingEmpty = new FSMSurroundingCondition(_range, false);

	State* wanderState = new State(new WanderBehaviour);
	State* followState = new State(new FollowBehavoiur);
	State* fleeState = new State(new FleeBehaviour);

	wanderState->AddTransition(inRange, followState);
	wanderState->AddTransition(surroundingEnemy, fleeState);

	followState->AddTransition(outOfRange, wanderState);

	fleeState->AddTransition(surroundingEmpty, wanderState);
	fleeState->AddTransition(inRange, followState);

	FiniteStateMachine* fsm = new FiniteStateMachine(wanderState);
	fsm->AddState(followState);
	fsm->AddState(fleeState);

	return fsm;
}


