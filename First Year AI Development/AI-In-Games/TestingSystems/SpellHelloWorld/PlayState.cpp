#include "PlayState.h"

#include <Azimuth/GameStates/IGameState.h>
#include <Azimuth/GameObjects/GameObjectManager.h>
#include <Azimuth/GameObjects/ATransform.h>
#include <Azimuth/Azimuth.h>
#include <raylib/raylib.h>
#include <list>

#include "WanderBehaviour.h"
#include "GotoPointBehaviour.h"
#include "INavigatable.h"
#include "NavMeshNode.h"
#include "NavMesh.h"
#include "CovenantAgent.h"
#include "Spartan.h"
#include "HashTable.h"
#include "FSM/SelectAgent.h"
#include <iostream>


using std::list;

HashTable* table = nullptr;
NavMesh* navigation = nullptr;

vector<CovenantAgent*> agents;
list<string> tries;
bool matched = false;
string setGoal = "";
string goal = "";

PlayState::PlayState(GameStateManager* _gsMan, GameObjectManager* _goMan)
	: IGameState("Play", _gsMan, _goMan)
{

}

void PlayState::Load()
{	
	std::cout << "What word do you want to find?" << std::endl;
	std::cin >> setGoal;

	SetWindowSize(1600, 900);
	SetWindowPosition(100, 100);


	navigation = new NavMesh((float)GetScreenWidth(), (float)GetScreenHeight());
	navigation->AddObstacles(40, 30, 30);
	navigation->Build();

	table = new HashTable(navigation);
	table->Load();	
}

void PlayState::Update(float _dt)
{
	
	Controls();	

	if (matched)
		return;

	CheckWord(_dt);
	
}

void PlayState::Draw()
{
	ClearBackground(BROWN);	

	for (int i = 0; i < agents.size(); i++)
		agents[i]->Draw();	
	
	navigation->Draw();

	DrawText(TextFormat("%d", agents.size()), 50, 100, 20, RED);
	DrawFPS(50, 50);

	int i = 0;

	DrawText(goal.c_str(), 50, 0, 10, GREEN);

	for (auto r : tries)
	{
		DrawText(r.c_str(), 50, 125 + (i * 25), 10, PINK);
		i++;
	}

	if (matched)
		DrawText(goal.c_str(), 600, 400, 100, PINK);
}


void PlayState::Unload()
{
	
}

void PlayState::Controls()
{
	if (IsKeyDown(KEY_ONE))
	{
		vec2 pos = navigation->GetRandomPoint();

		CovenantAgent* covenant = new CovenantAgent(setGoal, pos, table, navigation, Grunt, 500, m_stateManager, m_objectManager);
		covenant->Load();
		agents.push_back(covenant);
	}

	if (IsKeyPressed(KEY_TWO))
	{
		vec2 pos = navigation->GetRandomPoint();

		CovenantAgent* covenant = new CovenantAgent("HelloWorld", pos, table, navigation, GruntC, 200, m_stateManager, m_objectManager);
		covenant->Load();
		agents.push_back(covenant);
	}

	if (IsKeyPressed(KEY_THREE))
	{
		vec2 pos = navigation->GetRandomPoint();

		CovenantAgent* covenant = new CovenantAgent("HelloWorld", pos, table, navigation, Elite, 200, m_stateManager, m_objectManager);
		covenant->Load();
		agents.push_back(covenant);
	}

	if (IsKeyPressed(KEY_FOUR))
	{
		vec2 pos = navigation->GetRandomPoint();

		CovenantAgent* covenant = new CovenantAgent("HelloWorld", pos, table, navigation, EliteC, 200, m_stateManager, m_objectManager);
		covenant->Load();
		agents.push_back(covenant);
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
	
	if (IsKeyPressed(KEY_P))
	{
		std::cout << "What word do you want to find?" << std::endl;
		std::cin >> setGoal;
		
		for (auto c : agents)
			c->SetTargetWord(setGoal);

		matched = false;
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

void PlayState::CheckWord(float _dt)
{
	for (int i = 0; i < agents.size(); i++)
	{
		agents[i]->Update(_dt);

		string result = "";
		string target = agents[i]->GetTargetWord();
		vector<int> test = agents[i]->GetLetters();

		if (test.size() >= target.size())
		{
			for (int i = 0; i < test.size(); i++)
			{
				if (goal.empty())
				{
					if (tolower(test[i]) == tolower(target[0]))
						goal += tolower(test[i]);
				}
				else if (tolower(test[i]) == tolower(target[goal.size()]))
					goal += tolower(test[i]);

				result += tolower(test[i]);
			}

			if (goal.size() >= target.size())
				goal = "";

			tries.push_front(result);

			if (tries.size() > 10)
				tries.pop_back();
		}

		if (agents[i]->match)
			matched = true;
	}
}
