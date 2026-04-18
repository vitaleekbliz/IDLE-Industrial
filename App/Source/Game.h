#pragma once
#include "BitEngine.h"

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	Engine::BitEngine m_Engine;
	bool m_Running = true;
};
