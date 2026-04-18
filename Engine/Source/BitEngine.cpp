#include "pchEng.h"
#include "BitEngine.h"
#include "Logging/Logging.h"

namespace Engine
{

	BitEngine::BitEngine()
	{
		LOG_TRACE("Creating BitEngine");

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
	}

	BitEngine::~BitEngine()
	{
		LOG_TRACE("Closing BitEngine");
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
			}
		}

		return true;
	}

#pragma region FPS
	static uint64_t s_TickDuration = 0;
	static float s_DeltaTime = 0.f;
	static uint64_t s_Frequecy = SDL_GetPerformanceFrequency();

	void BitEngine::SetFPS(FPS fps)
	{
		if (fps == FPS::Unlim)
		{
			s_TickDuration = 0;
			return;
		}

		s_TickDuration = s_Frequecy / static_cast<uint64_t>(fps);

		LOG_INFO(std::format("Changed FPS to {}", (uint64_t)fps));
	}

	inline float BitEngine::GetDeltaTime()
	{
		return s_DeltaTime;
	}

	void BitEngine::HandleTicks()
	{
		static uint64_t prev = SDL_GetPerformanceCounter();

		uint64_t now = SDL_GetPerformanceCounter();

		uint64_t deltaTicks = now - prev;

		if (deltaTicks < s_TickDuration)
		{
			std::this_thread::sleep_for(std::chrono::microseconds(s_TickDuration - deltaTicks));
			deltaTicks = s_TickDuration;
			prev = SDL_GetPerformanceCounter();
		}
		else
		{
			prev = now;
		}

		s_DeltaTime = (float)deltaTicks / s_Frequecy;
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
	}

	void BitEngine::ResizeWindow(Resolution resolution)
	{
		WindowSize size = s_ScreenPresets.at(resolution);
		SDL_SetWindowSize(m_Window, size.w, size.h);
	}
#pragma endregion

} // namespace Engine