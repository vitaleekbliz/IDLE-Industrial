#pragma once
#include "BitEngine.h"
#include "Textures/SpriteSheet.h"
#include <memory>

namespace Game
{
	class Application
	{
	public:
		Application();
		~Application();

		void Run();

	private:
		Engine::BitEngine m_Engine;
		std::shared_ptr<Engine::SpriteSheet> m_SpriteSheet;

		bool m_Running = true;
	};
} // namespace Game
