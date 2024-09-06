#include "PlayState.h"

#include "Node.h"

#include <Azimuth/GameStates/IGameState.h>
#include <Azimuth/GameObjects/GameObjectManager.h>
#include <Azimuth/Azimuth.h>
#include <raylib/raylib.h>
#include <vector>
#include "Agent.h"
#include "SelectAgent.h"
#include "NodeMap.h"
#include "Node.h"
#include "GotoPointBehaviour.h"
#include "SelectAgent.h"


Agent* agent = nullptr;
vector<SelectAgent*> bAgent;
NodeMap* map = nullptr;

PlayState::PlayState(GameStateManager* _gsMan, GameObjectManager* _goMan)
	: IGameState("Play", _gsMan, _goMan)
{

}

void PlayState::Load()
{
	SetWindowSize(1200, 900);
	map = new NodeMap({ 40, 30 });
	map->Load();

	agent = new Agent(map, new GotoPointBehaviour, BLUE, 150);	
	agent->SetCurrentNode(map->GetMap()[0]);
	agent->SetPos(map->GetMap()[0]->pos);

	for (int i = 0; i < 0; i++)
	{
		bAgent.push_back( new SelectAgent(map, ORANGE, 50));

		Node* node = map->GetRandomNode();

		bAgent[i]->SetCurrentNode(node);
		bAgent[i]->SetPos(node->pos);
		bAgent[i]->SetTarget(agent);
	}
	
	
}

void PlayState::Update(float _dt)
{
	map->Update(_dt);
	agent->Update(_dt);		

	for (int i = 0; i < bAgent.size(); i++)
		bAgent[i]->Update(_dt);
		
}

void PlayState::Draw()
{
	map->Draw();
	agent->Draw();	
	for (int i = 0; i < bAgent.size(); i++)
		bAgent[i]->Draw();
}

void PlayState::Unload()
{
	
}