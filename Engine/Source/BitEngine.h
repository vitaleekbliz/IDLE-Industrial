#pragma once
#include "cstdint"

// namespace std
//{
//	template <>
//	struct hash<Engine::SpriteSheet>
//	{
//		size_t operator()(const Engine::SpriteSheet& sheet) const
//		{
//			sheet.GetHash();
//		}
//	};
// } // namespace std

struct SDL_Window;
struct SDL_Renderer;
// typedef uint64_t SDL_TexturePointer;

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
		// std::unordered_map<SpriteSheet, SDL_TexturePointer> m_SpriteSheets;
	};
} // namespace Engine