#include "pchGame.h"
#include "Application.h"
#include "Logging/Logging.h"

Application::Application()
{
	LOG_TRACE("Constructing Application");
	m_Engine.CreateWindow("IDLE Industrial", Engine::Resolution::FullHD);
	m_Engine.SetFPS(Engine::FPS::f60);
}

Application::~Application()
{
	LOG_TRACE("Deconstructing Application");
}

void Application::Run()
{
	while (m_Running)
	{
		m_Engine.HandleTicks();
		m_Running = m_Engine.PollEvents();
	}
}
