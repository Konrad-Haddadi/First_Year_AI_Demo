#include "PlayState.h"

#include <Azimuth/GameStates/IGameState.h>
#include <Azimuth/GameObjects/GameObjectManager.h>
#include <Azimuth/Azimuth.h>
#include <vector>

#include "Node.h"
#include "NodeMap.h"
#include "HashTable.h"
#include "QuadTree.h"
#include "GotoPointBehaviour.h"
#include "CovenantBaseAgent.h"
#include "SpartanAgent.h"

using std::vector;


vector<CovenantBaseAgent*> agent;
SpartanAgent* player = nullptr;

QuadTree* quadTree = nullptr;
NodeMap* map = nullptr;

PlayState::PlayState(GameStateManager* _gsMan, GameObjectManager* _goMan)
	: IGameState("Play", _gsMan, _goMan)
{

}

void PlayState::Load()
{
	SetTargetFPS(120);
	SetWindowSize(800, 800);
	SetWindowPosition(150, 150);

	quadTree = new QuadTree(Rectangle{ 0,0, (float)GetScreenWidth(), (float)GetScreenHeight() });
	quadTree->Load();
	
	map = new NodeMap({ 32, 32 });	
	map->Load();

	player = new SpartanAgent("Player", quadTree, map, new GotoPointBehaviour, 250, PINK, m_stateManager, m_objectManager);
	player->SetCurrentNode(map->GetMap()[0]->pos);
	player->SetPos(map->GetMap()[0]->pos);
	player->SetBehaviour(new GotoPointBehaviour);
	player->Load();	

	for (int i = 0; i < 15; i++)
	{
		agent.push_back(new CovenantBaseAgent(quadTree, map, Grunt, 150, m_stateManager, m_objectManager));

		Node* node = map->GetRandomNode();
		node->SetType(Empty);

		agent[i]->SetCurrentNode(node->pos);
		agent[i]->SetPos(node->pos);
		agent[i]->Load();
	}
}

void PlayState::Update(float _dt)
{
	map->Update(_dt);
	player->Update(_dt);
	quadTree->Update(_dt);

	for (int i = 0; i < agent.size(); i++)
		agent[i]->Update(_dt);	
}

void PlayState::Draw()
{
	map->Draw();

	for (int i = 0; i < agent.size(); i++)
		agent[i]->Draw();

	player->Draw();
	quadTree->Draw();

	DrawFPS(50, 50);
}

void PlayState::Unload()
{
	
}