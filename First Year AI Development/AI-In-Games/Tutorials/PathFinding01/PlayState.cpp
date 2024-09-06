#include "PlayState.h"

#include <vector>
#include <string>
#include "Node.h"
#include "NodeMap.h"

using AIForGames::Node;
using std::vector;
using std::string;

vector<string> asciiMap;
NodeMap* map;

void PlayState::Load(GameStateManager* _gsMan, GameObjectManager* _goMan)
{
	asciiMap.push_back("000000000000");
	asciiMap.push_back("010111011100");
	asciiMap.push_back("010101110110");
	asciiMap.push_back("010100000000");
	asciiMap.push_back("010111111110");
	asciiMap.push_back("010000001000");
	asciiMap.push_back("011111111110");
	asciiMap.push_back("000000000000");
	
	map = new NodeMap();
	map->Init(asciiMap, 25);
}

void PlayState::Update(float _dt)
{

}

void PlayState::Draw()
{
	map->Draw();
}

void PlayState::Unload()
{
}
