#pragma once
#include "BitEngine.h"

class Application
{
public:
	Application();
	~Application();

	void Run();

private:
	Engine::BitEngine m_Engine;
	bool m_Running = true;
};
