#pragma once
#include "BitEngine.h"

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	bool m_Running = true;
};
