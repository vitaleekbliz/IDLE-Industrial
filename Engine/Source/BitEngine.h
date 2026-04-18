#pragma once
#include "stdint.h"

struct SDL_Window;
struct SDL_Renderer;

namespace Engine
{
	enum class Resolution : uint8_t
	{
		nHD,
		qHD,
		HD,
		FullHD,
		_2K,
		_4K
	};

	enum class FPS : uint8_t
	{
		Unlim = 0,
		f30 = 30,
		f60 = 60,
		f120 = 120,
		f144 = 144
	};

	class BitEngine
	{
	public:
		BitEngine();
		~BitEngine();

		void CreateWindow(const char* title, Resolution resolution);
		void SetFPS(FPS fps);
		inline float GetDeltaTime();
		bool PollEvents();
		void HandleTicks();

	private:
		void ResizeWindow(Resolution resolution);
		SDL_Window* m_Window = nullptr;
		SDL_Renderer* m_Renderer = nullptr;
	};
} // namespace Engine