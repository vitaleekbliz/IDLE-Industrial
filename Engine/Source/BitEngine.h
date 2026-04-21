#pragma once
#include "cstdint"
#include "Textures/Texture.h"
#include "Textures/Sprite.h"
#include <unordered_map>

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

	class SpriteSheet;

	class BitEngine
	{
	public:
		BitEngine();
		~BitEngine();

		void CreateWindow(const char* title, Resolution resolution);
		void SetFPS(FPS fps);

		const float GetDeltaTime() const { return m_DeltaTime; }
		bool PollEvents();
		void HandleTicks();

		// called to clear renderer at the start of the frame
		void ClearFrame();
		void RenderSprite(Sprite sprite, const SpriteSheet* spriteSheet, int x, int y);
		void RenderFrame();

	private:
		void ResizeWindow(Resolution resolution);
		SDL_Window* m_Window = nullptr;
		SDL_Renderer* m_Renderer = nullptr;
		std::unordered_map<const SpriteSheet*, Texture> m_Textures;

		uint64_t m_TicksPerFrame = 0;
		float m_DeltaTime = 0.f;
		// from SDL (resolution of the clock)
		uint64_t m_Frequecy = 0;
		uint64_t m_PrevTick = 0;
	};
} // namespace Engine