#pragma once
#include <filesystem>

struct SDL_Surface;

namespace Engine
{
	class SpriteSheet
	{
	public:
		SpriteSheet(std::filesystem::path path);
		SpriteSheet(SpriteSheet&& other) noexcept;
		SpriteSheet& operator=(SpriteSheet&& other) noexcept;
		~SpriteSheet();

		SDL_Surface* GetSurface() const { return m_Surface; }

		bool operator==(const SpriteSheet& other) const;
		bool operator!=(const SpriteSheet& other) const;

	private:
		SpriteSheet() = delete;
		SpriteSheet& operator=(const SpriteSheet& other) = delete;
		SpriteSheet(const SpriteSheet& other) = delete;

		SDL_Surface* m_Surface = nullptr;
	};
} // namespace Engine
