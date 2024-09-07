#include "PlayState.h"

#include <Azimuth/GameStates/IGameState.h>
#include <Azimuth/GameObjects/GameObjectManager.h>
#include <Azimuth/GameObjects/ATransform.h>
#include <Azimuth/Azimuth.h>
#include <raylib/raylib.h>

#include "WanderBehaviour.h"
#include "GotoPointBehaviour.h"
#include "INavigatable.h"
#include "NavMeshNode.h"
#include "NavMesh.h"
#include "CovenantAgent.h"
#include "Spartan.h"
#include "HashTable.h"
#include "FSM/SelectAgent.h"

HashTable* table = nullptr;
NavMesh* navigation = nullptr;
Spartan* player = nullptr;

vector<SelectAgent*> SAgent;
vector<CovenantAgent*> agents;
Image* background = nullptr;

PlayState::PlayState(GameStateManager* _gsMan, GameObjectManager* _goMan)
	: IGameState("Play", _gsMan, _goMan)
{

}

void PlayState::Load()
{	
	SetWindowSize(1600, 900);
	SetWindowPosition(100, 100);

	background = new Image();
	*background = LoadImage("Assets/textures/Benlin.png");


	navigation = new NavMesh((float)GetScreenWidth(), (float)GetScreenHeight());
	navigation->AddObstacles(40, 30, 30);
	navigation->Build();

	table = new HashTable(navigation);
	table->Load();
	vec2 start = navigation->GetRandomPoint();

	player = new Spartan("Player", navigation, table, new GotoPointBehaviour, 300, DARKGREEN, m_stateManager, m_objectManager);
	player->SetCurrentNode(start);
	player->SetPos(start);
	player->Load();
}

void PlayState::Update(float _dt)
{
	if (player->timer <= 0)
	{
		if (IsKeyPressed(KEY_ENTER))
		{
			player->timer = 10;
		}
		else
			return;
	}

	Controls();

	if (IsSeen())
		player->seen = true;
	else
		player->seen = false;

	if (IsKeyDown(KEY_TAB))
		return;

	player->Update(_dt);

	for (int i = 0; i < SAgent.size(); i++)
		SAgent[i]->Update(_dt);

	for (int i = 0; i < agents.size(); i++)
		agents[i]->Update(_dt);	
	
}

void PlayState::Draw()
{
	ClearBackground(BROWN);

	if (IsKeyDown(KEY_GRAVE))
	{
		table->Draw();

		DrawFPS(50, 50);
		DrawText(TextFormat("%d", agents.size()), 50, 80, 20, SKYBLUE);
	}
	

	for (int i = 0; i < agents.size(); i++)
		agents[i]->Draw();
	
	for (int i = 0; i < SAgent.size(); i++)
		SAgent[i]->Draw();

	player->Draw();

	navigation->Draw();

	if (player->seen && player->timer > 0)
	{
		DrawRectangle(650, 30, 300, 50, {0,0,0,150});
		DrawText(TextFormat("Seen: %d Seconds", (int)player->timer), 720, 50, 20, RED);
	}

	if (IsKeyDown(KEY_TAB))
		DrawControls();	
	else if(IsKeyUp(KEY_GRAVE))
		DrawText("Press Tab For Controls", 50, 50, 30, BLACK);

	if (player->timer <= 0)
	{
		DrawText("GAME OVER", 650, 400, 50, RED);
		DrawText("Press Enter to continue", 550, 500, 50, RED);
	}
}


void PlayState::Unload()
{
	
}

void PlayState::Controls()
{
	if (IsKeyPressed(KEY_ONE))
	{
		vec2 pos = navigation->GetRandomPoint();

		CovenantAgent* covenant = new CovenantAgent(pos, table, navigation, Grunt, 200, m_stateManager, m_objectManager);
		covenant->Load();
		agents.push_back(covenant);
	}

	if (IsKeyPressed(KEY_TWO))
	{
		vec2 pos = navigation->GetRandomPoint();

		CovenantAgent* covenant = new CovenantAgent(pos, table, navigation, GruntC, 200, m_stateManager, m_objectManager);
		covenant->Load();
		agents.push_back(covenant);
	}

	if (IsKeyPressed(KEY_THREE))
	{
		vec2 pos = navigation->GetRandomPoint();

		CovenantAgent* covenant = new CovenantAgent(pos, table, navigation, Elite, 200, m_stateManager, m_objectManager);
		covenant->Load();
		agents.push_back(covenant);
	}

	if (IsKeyPressed(KEY_FOUR))
	{
		vec2 pos = navigation->GetRandomPoint();

		CovenantAgent* covenant = new CovenantAgent(pos, table, navigation, EliteC, 200, m_stateManager, m_objectManager);
		covenant->Load();
		agents.push_back(covenant);
	}
	
	if (IsKeyPressed(KEY_FIVE))
	{
		vec2 rand = navigation->GetRandomPoint();

		SelectAgent* guilty = new SelectAgent("GuiltySpark", 200, navigation, table, new GotoPointBehaviour, 150, SKYBLUE, m_stateManager, m_objectManager);

		guilty->SetCurrentQuad(guilty->GetHashTable()->CheckQuad(guilty->Transform()->Position()));
		guilty->SetCurrentNode(rand);
		guilty->SetPos(rand);
		guilty->Load();
		guilty->SetTargetEnemy(player);

		SAgent.push_back(guilty);
	}

	if (IsKeyPressed(KEY_ENTER))
	{
		for (int i = agents.size() - 1; i >= 0; i--)
		{
			delete agents[i];
			agents[i] = nullptr;
		}

		agents.clear();
	}

	if (IsKeyPressed(KEY_BACKSPACE))
	{
		for (int i = SAgent.size() - 1; i >= 0; i--)
		{
			delete SAgent[i];
			SAgent[i] = nullptr;
		}

		SAgent.clear();
	}

}

void PlayState::DrawControls()
{
	DrawRectangle(650, 150, 500, 550, { 200,200,200,100 });
	DrawText("Press '~' for DevMode", 700, 200, 20, BLACK);
	DrawText("Press '1' for Grunt", 700, 250, 20, BLACK);
	DrawText("Press '2' for GruntC", 700, 300, 20, BLACK);
	DrawText("Press '3' for Elite", 700, 350, 20, BLACK);
	DrawText("Press '4' for EliteC", 700, 400, 20, BLACK);
	DrawText("Press '5' for GuiltySpark", 700, 450, 20, BLACK);
	DrawText("Press Enter to remove Covenant", 700, 500, 20, BLACK);
	DrawText("Press Backspace to remove GuiltySpark", 700, 550, 20, BLACK);
	DrawText("Press LMB to move", 700, 600, 20, BLACK);
}

bool PlayState::IsSeen()
{
	for (int i = 0; i < agents.size(); i++)
	{
		if (agents[i]->GetSpartanTarget())
			return true;
	}

	return false;
}