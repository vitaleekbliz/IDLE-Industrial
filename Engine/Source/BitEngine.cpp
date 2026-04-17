#include "pchEng.h"
#include "BitEngine.h"
#include "Logging/Logging.h"

namespace Engine
{
	static BitEngine* s_Instance = nullptr;

	BitEngine::BitEngine()
	{
		LOG::Message(LOG::Level::Trace, "BitEngine Created");
	}

	BitEngine::~BitEngine()
	{
		LOG::Message(LOG::Level::Trace, "BitEngine Destroyed");
	}

	BitEngine& BitEngine::Get()
	{
		if (!s_Instance)
			s_Instance = new BitEngine();

		return *s_Instance;
	}

	void BitEngine::Init()
	{

		if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
		{
		}
	}

	void BitEngine::Close()
	{
		delete s_Instance;
	}

} // namespace Engine