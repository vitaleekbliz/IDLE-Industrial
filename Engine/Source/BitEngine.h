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

	class BitEngine
	{
	public:
		static BitEngine& Get();
		void Close();

		void CreateWindow(const char* title, Resolution resolution);
		bool PollEvents();

	private:
		BitEngine();
		~BitEngine();

		void ResizeWindow(Resolution resolution);
		SDL_Window* m_Window = nullptr;
		SDL_Renderer* m_Renderer = nullptr;
	};
} // namespace Engine