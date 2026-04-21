#pragma once

struct SDL_Texture;
struct SDL_Renderer;

namespace Engine
{
	class SpriteSheet;

	class Texture
	{
	public:
		Texture(SDL_Renderer* renderer, const SpriteSheet* spriteSheet);
		Texture(Texture&& other) noexcept;
		~Texture();

		SDL_Texture* GetTexture() const { return m_Texture; }

	private:
		Texture() = delete;
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;
		SDL_Texture* m_Texture = nullptr;
	};
} // namespace Engine
