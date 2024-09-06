#include <Azimuth/Application.h>

#include "GameState.h"

int main(int _argc, char* _argv[])
{
	return Application::Run<GameState>(_argv);
}
