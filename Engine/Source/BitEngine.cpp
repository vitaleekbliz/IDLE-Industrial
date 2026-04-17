#include "pchEng.h"
#include "BitEngine.h"
#include "Logging/Logging.h"

namespace Engine
{
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

	static BitEngine* s_Instance = nullptr;

	BitEngine& BitEngine::Get()
	{
		if (!s_Instance)
			s_Instance = new BitEngine();

		return *s_Instance;
	}

	void BitEngine::Close()
	{
		delete s_Instance;
	}

	BitEngine::BitEngine()
	{
		LOG::Message(LOG::Level::Trace, "Creating BitEngine");

		if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
		{
			LOG::Message(LOG::Level::Fatal, "Failed SDL_INIT");
		}

		if (!MIX_Init())
		{
			LOG::Message(LOG::Level::Fatal, "Failed MIX_Init");
		}

		if (!TTF_Init())
		{
			LOG::Message(LOG::Level::Fatal, "Failed TTF_Init");
		}
	}

	BitEngine::~BitEngine()
	{
		LOG::Message(LOG::Level::Trace, "Closing BitEngine");
	}

	void BitEngine::CreateWindow(const char* title, Resolution resolution)
	{
		WindowSize size = s_ScreenPresets.at(resolution);
		SDL_CreateWindowAndRenderer(title, size.w, size.h, NULL, &m_Window, &m_Renderer);
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

	void BitEngine::ResizeWindow(Resolution resolution)
	{
		WindowSize size = s_ScreenPresets.at(resolution);
		SDL_SetWindowSize(m_Window, size.w, size.h);
	}

} // namespace Engine