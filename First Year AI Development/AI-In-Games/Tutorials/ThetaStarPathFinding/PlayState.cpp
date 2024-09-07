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
	

	for (int i = 0; i < 0; i++)
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
	if (IsKeyPressed(KEY_ENTER))
	{
		SelectAgent* newAgent = new SelectAgent(map, PURPLE, 100);
		sAgent.push_back(newAgent);
		newAgent->Load();

		Node* randNode = map->GetRandomNode();
		randNode->SetType(0);
		newAgent->SetCurrentNode(randNode);
		newAgent->GetPathAgent()->SetPos(randNode->pos);
		newAgent->SetTarget(agent);
	}
	
	if (IsKeyPressed(KEY_BACKSPACE))
	{
		if(sAgent.size() > 0)
			sAgent.pop_back();
	}

	if (IsKeyDown(KEY_TAB))
		return;

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
	
	DrawText("'~' for path", 560, 50, 20, BLACK);
	DrawText("LMB to draw walls", 560, 80, 20, BLACK);
	DrawText("E to destroy walls", 560, 110, 20, BLACK);
	DrawText("RMB to move", 560, 140, 20, BLACK);
	DrawText("BS to remove agents", 560, 170, 20, BLACK);
	DrawText("Enter to add agents", 560, 200, 20, BLACK);
	DrawText("Space to clear board", 560, 230, 20, BLACK);
	
	Vector2 mousePos = GetMousePosition();

	Node* node = map->GetClosestNode({ mousePos.x, mousePos.y});

	DrawRectangle(node->pos.x, node->pos.y, map->GetCellSize() - 5, map->GetCellSize() - 5, { 100,100,100,100 });
	
}

void PlayState::Unload()
{
	
}