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

using AITesting::Node;
using std::vector;

Agent* agent = nullptr;
vector<SelectAgent*> sAgent;

NodeMap* map = nullptr;

PlayState::PlayState(GameStateManager* _gsMan, GameObjectManager* _goMan)
	: IGameState("Play", _gsMan, _goMan)
{

}

void PlayState::Load()
{
	map = new NodeMap({ 20, 20 });
	map->Load();

	agent = new Agent(map, new GotoPointBehaviour, BLUE, 300);	
	agent->SetCurrentNode(map->GetMap()[0]);

	for (int i = 0; i < GetRandomValue(2, 10); i++)
	{
		sAgent.push_back(new SelectAgent(map, PURPLE, 100));
		sAgent[i]->Load();

		Node* randNode = map->GetRandomNode();
		randNode->SetType(0);
		sAgent[i]->SetCurrentNode(randNode);
		sAgent[i]->GetPathAgent()->SetPos(randNode->pos);
		sAgent[i]->SetTarget(agent);
	}
	
}

void PlayState::Update(float _dt)
{
	map->Update(_dt);
	agent->Update(_dt);	

	for (int i = 0; i < sAgent.size(); i++)
		sAgent[i]->Update(_dt);
}

void PlayState::Draw()
{
	map->Draw();
	agent->Draw();	

	for (int i = 0; i < sAgent.size(); i++)
		sAgent[i]->Draw();
}

void PlayState::Unload()
{
	
}