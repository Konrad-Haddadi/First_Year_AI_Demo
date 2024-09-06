#include "PlayState.h"


#include <Azimuth/GameStates/IGameState.h>
#include <Azimuth/GameObjects/GameObjectManager.h>
#include <Azimuth/Azimuth.h>

#include <raylib/raylib.h>
#include <vector>

#include "NodeMap.h"
#include "Node.h"
#include "Agent.h"

using AITesting::Node;
using std::vector;

NodeMap* map = nullptr;
vector<Agent*> agents;

PlayState::PlayState(GameStateManager* _gsMan, GameObjectManager* _goMan)
	: IGameState("Play", _gsMan, _goMan)
{

}

void PlayState::Load()
{
	map = new NodeMap({ 25, 25 });
	map->Load();	

	for (int i = 0; i < 5; i++)
	{
		Node* node = map->GetRandomNode();

		node->SetType(0);

		agents.push_back(new Agent(map, BLUE, 100));
		agents[i]->SetPos(node->pos);
	}	
}

void PlayState::Update(float _dt)
{
	map->Update(_dt);

	for (int i = 0; i < agents.size(); i++)
		agents[i]->Update(_dt);
}

void PlayState::Draw()
{
	map->Draw();	

	for (int i = 0; i < agents.size(); i++)
		agents[i]->Draw();
	
}

void PlayState::Unload()
{
	
}