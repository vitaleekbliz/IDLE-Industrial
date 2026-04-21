#include "pchEng.h"
#include "Texture.h"
#include "SpriteSheet.h"
#include "Logging/Logging.h"

namespace Engine
{
	Texture::Texture(SDL_Renderer* renderer, const SpriteSheet* spriteSheet)
	{
		m_Texture = SDL_CreateTextureFromSurface(renderer, spriteSheet->GetSurface());

		if (m_Texture)
			LOG_TRACE(std::format("Creating texture {}", (uint64_t)m_Texture));
		else
			LOG_WARN(std::format("Failed to create texture from surface {}", (uint64_t)spriteSheet->GetSurface()));

		Assert(m_Texture);
	}

	Texture::Texture(Texture&& other) noexcept
	{
		if (this == &other)
			return;

		LOG_TRACE("Texture called move constructor");
		m_Texture = other.m_Texture;
		other.m_Texture = nullptr;
	}

	Texture::~Texture()
	{
		LOG_TRACE(std::format("Destroying texture {}", (uint64_t)m_Texture));

		SDL_DestroyTexture(m_Texture);
	}
} // namespace Engine
