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
	}

	BitEngine::~BitEngine()
	{
		LOG_TRACE("Deconstucting BitEngine");
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
	static uint64_t s_MaxDeltaTicks = 0;
	static float s_DeltaTime = 0.f;
	static uint64_t s_Frequecy = SDL_GetPerformanceFrequency();

	void BitEngine::SetFPS(FPS fps)
	{
		if (fps == FPS::Unlim)
		{
			s_MaxDeltaTicks = 0;
			LOG_INFO("Change FPS limit to Unlimited");
			return;
		}

		s_MaxDeltaTicks = s_Frequecy / static_cast<uint64_t>(fps);
		LOG_INFO(std::format("Changed FPS limit to {}", (uint64_t)fps));
	}

	inline float BitEngine::GetDeltaTime()
	{
		return s_DeltaTime;
	}

	static float s_MaxDeltaTime = 1.f;

	void BitEngine::HandleTicks()
	{
		static uint64_t prev = SDL_GetPerformanceCounter();
		uint64_t now = SDL_GetPerformanceCounter();
		uint64_t deltaTicks = now - prev;
		if (deltaTicks < s_MaxDeltaTicks)
		{
			SDL_DelayNS(s_MaxDeltaTicks - deltaTicks);
			deltaTicks = s_MaxDeltaTicks;
			prev = SDL_GetPerformanceCounter();
		}
		else
		{
			prev = now;
		}
		s_DeltaTime = (float)deltaTicks / s_Frequecy;

		// TODO(VB) : clamping delta time to be max 1 second
		s_DeltaTime = std::min(s_DeltaTime, s_MaxDeltaTime);
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