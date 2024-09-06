#include "PlayState.h"

#include <Azimuth/GameStates/IGameState.h>
#include <Azimuth/GameObjects/GameObjectManager.h>
#include <Azimuth/Azimuth.h>
#include <vector>

#include "Node.h"
#include "NodeMap.h"
#include "HashTable.h"
#include "GotoPointBehaviour.h"
#include "CovenantBaseAgent.h"
#include "SpartanAgent.h"

using std::vector;

vector<CovenantBaseAgent*> agent;
SpartanAgent* player = nullptr;

NodeMap* map = nullptr;
HashTable* table = nullptr;

PlayState::PlayState(GameStateManager* _gsMan, GameObjectManager* _goMan)
	: IGameState("Play", _gsMan, _goMan)
{

}

void PlayState::Load()
{
	SetTargetFPS(120);
	SetWindowSize(800, 800);
	SetWindowPosition(150, 50);
	table = new HashTable();
	map = new NodeMap({ 32, 32 });
	table->Load();
	map->Load();

	player = new SpartanAgent("Fanta", table ,map, new GotoPointBehaviour, 150, DARKGREEN, m_stateManager, m_objectManager);
	player->SetCurrentNode(map->GetMap()[0]->pos);
	player->SetPos(map->GetMap()[0]->pos);
	player->SetBehaviour(new GotoPointBehaviour);
	player->Load();

	int max = 30;

	for (int i = 0; i < max; i++)
	{
		int val = GetRandomValue(0, map->GetAmount() - 1);
		
		Node* node = map->GetMap()[val];
		node->type = NodeType::Empty;

		agent.push_back(new CovenantBaseAgent(table, map, GetRandomValue(Grunt, EliteC)
			, 50, m_stateManager, m_objectManager));
		agent[i]->SetCurrentNode(node->pos);
		agent[i]->SetPos(node->pos);

		agent[i]->Load();
	}
}

void PlayState::Update(float _dt)
{
	map->Update(_dt);
	player->Update(_dt);

	for (int i = 0; i < agent.size(); i++)
		agent[i]->Update(_dt);	
}

void PlayState::Draw()
{
	map->Draw();

	for (int i = 0; i < agent.size(); i++)
		agent[i]->Draw();

	player->Draw();
	
	if(IsKeyDown(KEY_GRAVE))
		table->Draw();

	DrawFPS(50, 50);
}

void PlayState::Unload()
{
	
}