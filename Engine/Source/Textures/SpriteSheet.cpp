#include "pchEng.h"
#include "SpriteSheet.h"
#include "Logging/Logging.h"

namespace Engine
{
	SpriteSheet::SpriteSheet(std::filesystem::path& path)
	{
		Load(path);
	}

	SpriteSheet::~SpriteSheet()
	{
		LOG_TRACE(std::format("Sprite sheet destructor, destroying surface {}", (uint64_t)m_Surface));
		SDL_DestroySurface(m_Surface);
	}

	bool SpriteSheet::Load(std::filesystem::path& path)
	{
		if (!std::filesystem::exists(path))
		{
			LOG_ERROR(std::format("Can't load sprite sheet {}", path.string()));
			Assert(false);
			return false;
		}

		SDL_DestroySurface(m_Surface);

		m_Surface = SDL_LoadSurface(path.string().c_str());
		m_Width = m_Surface->w;
		m_Height = m_Surface->h;

		LOG_INFO(std::format("Loaded sprite sheet {}", path.string()));

		return true;
	}

	bool SpriteSheet::operator!=(SpriteSheet& other) const
	{
		return !(*this == other);
	}

	bool SpriteSheet::operator==(SpriteSheet& other) const
	{
		return m_Width == other.m_Width && m_Height == other.m_Height && m_Surface == other.m_Surface;
	}

	SpriteSheet::SpriteSheet(SpriteSheet&& other) noexcept
	{
		if (&other == this)
		{
			return;
		}
		SDL_DestroySurface(m_Surface);

		m_Width = other.m_Width;
		m_Height = other.m_Height;
		m_Surface = other.m_Surface;
		other.m_Surface = nullptr;
	}
} // namespace Engine
