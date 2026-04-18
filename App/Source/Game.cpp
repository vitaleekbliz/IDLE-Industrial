#include "pchApp.h"
#include "Game.h"
#include "BitEngine.h"

Game::Game()
{
	m_Engine.CreateWindow("IDLE Industrial", Engine::Resolution::FullHD);
	m_Engine.SetFPS(Engine::FPS::Unlim);
}

Game::~Game()
{
}

void Game::Run()
{
	while (m_Running)
	{
		m_Engine.HandleTicks();

		m_Running = m_Engine.PollEvents();
	}
}
