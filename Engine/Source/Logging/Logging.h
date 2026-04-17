#pragma once
#include <stdint.h>
#include <string_view>

namespace LOG
{
	enum class Level : uint8_t
	{
		None = 0,
		Trace,
		Info,
		Warn,
		Error,
		Fatal
	};

	void Message(Level level, std::string_view message);

#ifdef DEBUG
	#define CONSOLE_LOG_LEVEL Level::Trace
	#define FILE_LOG_LEVEL Level::Trace
#elif RELEASE
	#define CONSOLE_LOG_LEVEL Level::Info
	#define FILE_LOG_LEVEL Level::Warn
#else // DIST
	#define CONSOLE_LOG_LEVEL Level::Error
	#define FILE_LOG_LEVEL Level::Info
#endif

	// Assert
#if defined(DEBUG) || defined(RELEASE)
	#define Assert(x) \
		if (!x)       \
			__debugbreak();
#else // DIST
	#define Assert(x) ((void)0)
#endif
} // namespace LOG
