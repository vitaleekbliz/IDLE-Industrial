#include "pchEng.h"
#include "BitEngine.h"
#include "Logging/Logging.h"
#include "Textures/SpriteSheet.h"

namespace Engine
{

	BitEngine::BitEngine()
	{
		LOG_TRACE("Constructing BitEngine");

		if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
		{
			LOG_FATAL("Failed SDL_INIT");
		}
		if (!MIX_Init())
		{
			LOG_FATAL("Failed MIX_Init");
		}
		if (!TTF_Init())
		{
			LOG_FATAL("Failed TTF_Init");
		}

		m_Frequecy = SDL_GetPerformanceFrequency();
		m_PrevTick = SDL_GetPerformanceCounter();
	}

	BitEngine::~BitEngine()
	{
		LOG_TRACE("Deconstucting BitEngine");

		SDL_DestroyRenderer(m_Renderer);
		SDL_DestroyWindow(m_Window);
	}

	// return false if requested closing of the window
	bool BitEngine::PollEvents()
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
				case SDL_EVENT_QUIT:
				case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
					return 0;
				case SDL_EVENT_WINDOW_RESIZED:
					m_PrevTick = SDL_GetPerformanceCounter();
					break;
			}
		}

		return true;
	}

#pragma region Rendering
	void BitEngine::RenderSprite(Sprite sprite, const SpriteSheet* spriteSheet, int x, int y)
	{
		if (!m_Textures.contains(spriteSheet))
		{
			m_Textures.emplace(spriteSheet, Texture(m_Renderer, spriteSheet));
		}

		SDL_FRect source((float)(sprite.X * sprite.Size), (float)(sprite.Y * sprite.Size), (float)sprite.Size, (float)sprite.Size);
		SDL_FRect destination((float)x * sprite.Size, (float)y * sprite.Size, (float)sprite.Size, (float)sprite.Size);

		SDL_RenderTexture(m_Renderer, m_Textures.at(spriteSheet).GetTexture(), &source, &destination);
	}

	void BitEngine::ClearFrame()
	{
		SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
		SDL_RenderClear(m_Renderer);
	}

	void BitEngine::RenderFrame()
	{
		SDL_RenderPresent(m_Renderer);
	}

#pragma endregion

#pragma region FPS
	void BitEngine::SetFPS(FPS fps)
	{
		if (fps == FPS::Unlim)
		{
			m_TicksPerFrame = 0;
			LOG_INFO("Change FPS limit to Unlimited");
			return;
		}

		m_TicksPerFrame = m_Frequecy / static_cast<uint64_t>(fps);
		LOG_INFO(std::format("Changed FPS limit to {}", (uint64_t)fps));
	}

	void BitEngine::HandleTicks()
	{
		uint64_t now = SDL_GetPerformanceCounter();
		uint64_t deltaTicks = now - m_PrevTick;
		if (deltaTicks < m_TicksPerFrame)
		{
			SDL_DelayNS(m_TicksPerFrame - deltaTicks);
			deltaTicks = m_TicksPerFrame;
			m_PrevTick = SDL_GetPerformanceCounter();
		}
		else
		{
			m_PrevTick = now;
		}
		m_DeltaTime = (float)deltaTicks / m_Frequecy;
	}

#pragma endregion

#pragma region Window
	struct WindowSize
	{
		int w = 0, h = 0;
	};

	static std::unordered_map<Resolution, WindowSize> s_ScreenPresets = {
		{ Resolution::nHD, { 640, 360 } },
		{ Resolution::qHD, { 960, 540 } },
		{ Resolution::HD, { 1280, 720 } },
		{ Resolution::FullHD, { 1920, 1080 } },
		{ Resolution::_2K, { 2560, 1440 } },
		{ Resolution::_4K, { 3840, 2160 } }
	};

	void BitEngine::CreateWindow(const char* title, Resolution resolution)
	{
		WindowSize size = s_ScreenPresets.at(resolution);
		SDL_CreateWindowAndRenderer(title, size.w, size.h, NULL, &m_Window, &m_Renderer);
		LOG_INFO(std::format("Created window and renderer, res : {}x{}", size.w, size.h));
	}

	void BitEngine::ResizeWindow(Resolution resolution)
	{
		WindowSize size = s_ScreenPresets.at(resolution);
		SDL_SetWindowSize(m_Window, size.w, size.h);
		LOG_INFO(std::format("Set resolution to {}x{}", size.w, size.h));
	}
#pragma endregion

} // namespace Engine