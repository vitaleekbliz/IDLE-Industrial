#pragma once
#include <filesystem>

struct SDL_Surace;

namespace Engine
{
	class SpriteSheet
	{
	public:
		SpriteSheet() = default;
		SpriteSheet(std::filesystem::path& path);
		SpriteSheet(SpriteSheet&& other) noexcept;
		~SpriteSheet();

		bool Load(std::filesystem::path& path);
		size_t GetHash() const { return reinterpret_cast<size_t>(m_Surface); };
		bool operator==(SpriteSheet& other) const;
		bool operator!=(SpriteSheet& other) const;

	private:
		SDL_Surface* m_Surface = nullptr;
		uint64_t m_Width = 0, m_Height = 0;
	};
} // namespace Engine
