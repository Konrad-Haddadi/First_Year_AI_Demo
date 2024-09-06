#include "PlayState.h"

#include <Azimuth/GameStates/IGameState.h>
#include <Azimuth/GameObjects/GameObjectManager.h>
#include <Azimuth/Azimuth.h>
#include <raylib/raylib.h>

#include "WanderBehaviour.h"
#include "GotoPointBehaviour.h"
#include "INavigatable.h"
#include "NavMeshNode.h"
#include "NavMesh.h"
#include "SelectAgent.h"
#include "Agent.h"

using std::vector;

NavMesh* navigation = nullptr;
Agent* player = nullptr;
vector<SelectAgent*> agents;

PlayState::PlayState(GameStateManager* _gsMan, GameObjectManager* _goMan)
	: IGameState("Play", _gsMan, _goMan)
{

}

void PlayState::Load()
{	
	SetWindowSize(1600, 900);
	SetWindowPosition(100, 100);


	navigation = new NavMesh((float)GetScreenWidth(), (float)GetScreenHeight());
	srand(42);
	navigation->AddObstacles(50, 30, 30);
	navigation->Build();
	NavMeshNode* start = navigation->GetNodes()[0];

	player = new Agent(navigation, new GotoPointBehaviour, BLUE, 800);
	player->SetCurrentNode(start->pos);
	player->SetPos(start->pos);	

	for (int i = 0; i < 0; i++)
	{
		NavMeshNode* node = navigation->GetRandomNode();

		agents.push_back(new SelectAgent(navigation, RED, 400));
		agents[i]->Load();
		agents[i]->SetTarget(player);
		agents[i]->SetCurrentNode(node->pos);
		agents[i]->SetPos(node->pos);
	}
}

void PlayState::Update(float _dt)
{
	player->Update(_dt);

	for (int i = 0; i < agents.size(); i++)
		agents[i]->Update(_dt);
	
}

void PlayState::Draw()
{
	ClearBackground(DARKGRAY);
	navigation->Draw();
	player->Draw();

	for (int i = 0; i < agents.size(); i++)
		agents[i]->Draw();

	DrawFPS(50, 50);
	
}


void PlayState::Unload()
{
	
}