#pragma once

#include "Azimuth/Azimuth.h"
#include "Azimuth/Game.h"

#include <string>

using std::string;

class Window;
class GameObjectManager;
class GameStateManger;
class Config;

class Application
{
public:
	template<Derived<Game> GAME>
	static int Run(char* _argv[]);

	DLL static const char* GetApplicationDirectory();
	DLL static void GetWindowSize(int& _width, int& _height);
	DLL static Window* GetWindow();

	DLL static void Quit();

private:
	DLL static Application* m_instance;

	Game* m_game;
	Config* m_config;
	const char* m_applicationDir;
	
	Window* m_window;
	GameStateManager* m_stateManager;
	GameObjectManager* m_objectManger;

	bool m_shouldQuit;

private:
	DLL Application(Game* _game);
	DLL ~Application();

	DLL void Init();
	DLL void Process();

};

template<Derived<Game> GAME>
inline int Application::Run(char* _argv[])
{
	if (m_instance == nullptr)
	{
		const string argvStr = string(_argv[0]);
		const string appPath = argvStr.substr(0, argvStr.find_last_of("\\"));

		m_instance = new Application(new GAME());
		m_instance->m_applicationDir = appPath.c_str();
		m_instance->Process();

		return 0;
	}

	return -1;
}
