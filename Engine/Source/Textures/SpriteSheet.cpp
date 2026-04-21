#include "pchEng.h"
#include "SpriteSheet.h"
#include "Logging/Logging.h"

namespace Engine
{
	SpriteSheet::SpriteSheet(std::filesystem::path path)
	{
		if (!std::filesystem::exists(path))
		{
			LOG_ERROR(std::format("Can't load sprite sheet {}", path.string()));
			Assert(false);
			return;
		}

		m_Surface = SDL_LoadSurface(path.string().c_str());
		Assert(m_Surface);
		LOG_INFO(std::format("Loaded sprite sheet {}", path.string()));
	}

	SpriteSheet::SpriteSheet(SpriteSheet&& other) noexcept
	{
		if (&other == this)
		{
			return;
		}

		m_Surface = other.m_Surface;
		other.m_Surface = nullptr;
	}

	SpriteSheet& SpriteSheet::operator=(SpriteSheet&& other) noexcept
	{
		if (this == &other)
			return *this;

		LOG_TRACE(std::format("Calling {}", __FUNCTION__));
		Assert(m_Surface);
		m_Surface = other.m_Surface;
		other.m_Surface = nullptr;

		return *this;
	}

	SpriteSheet::~SpriteSheet()
	{
		LOG_TRACE(std::format("Sprite sheet destructor, destroying surface {}", (uint64_t)m_Surface));
		SDL_DestroySurface(m_Surface);
	}

	bool SpriteSheet::operator!=(const SpriteSheet& other) const
	{
		return !(*this == other);
	}

	bool SpriteSheet::operator==(const SpriteSheet& other) const
	{
		return m_Surface == other.m_Surface;
	}
} // namespace Engine
