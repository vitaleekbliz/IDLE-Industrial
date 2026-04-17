#include "pchApp.h"
#include "Game.h"
#include "BitEngine.h"

Game::Game()
{
	Engine::BitEngine::Get().CreateWindow("IDLE Industrial", Engine::Resolution::FullHD);
}

Game::~Game()
{
	Engine::BitEngine::Get().Close();
}

void Game::Run()
{
	while (m_Running)
	{
		m_Running = Engine::BitEngine::Get().PollEvents();
		std::this_thread::sleep_for(std::chrono::milliseconds(15));
	}
}
