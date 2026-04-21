#include "pchGame.h"
#include "Application.h"
#include "Logging/Logging.h"
#include "Textures/Sprite.h"

namespace Game
{
	Application::Application()
	{
		LOG_TRACE("Constructing Application");
		m_Engine.CreateWindow("IDLE Industrial", Engine::Resolution::FullHD);
		m_Engine.SetFPS(Engine::FPS::f60);

		m_SpriteSheet = std::make_shared<Engine::SpriteSheet>("Assets/SpriteSheetIDLE.png");
	}

	Application::~Application()
	{
		LOG_TRACE("Deconstructing Application");
	}

	static inline Engine::Sprite mine{
		2, 1, 64
	};
	static inline Engine::Sprite grass{
		0, 0, 64
	};

	void Application::Run()
	{
		while (m_Running)
		{
			m_Engine.ClearFrame();

			m_Engine.HandleTicks();
			m_Running = m_Engine.PollEvents();

			for (int i = 0; i < 64; i++)
			{
				for (int j = 0; j < 64; j++)
				{
					m_Engine.RenderSprite(grass, m_SpriteSheet.get(), i, j);
					if (i == j)
						m_Engine.RenderSprite(mine, m_SpriteSheet.get(), i, j);
				}
			}
			m_Engine.RenderFrame();
		}
	}
} // namespace Game
