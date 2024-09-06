#include <Azimuth/Application.h>

#include "PlayState.h"

int main(int _argc, char* _argv[])
{
	return Application::Run<PlayState>(_argv);
}