#pragma once
#include <cstdint>

// Assert
#if defined(DEBUG) || defined(RELEASE)
	#define Assert(x) \
		if (!x)       \
			__debugbreak();
#else // DIST
	#define Assert(x)
#endif

namespace LOG
{
	enum class Level : uint8_t
	{
		Trace = 0,
		Info,
		Warn,
		Error,
		Fatal
	};

	void Message(Level level, std::string message);

} // namespace LOG

#define BIT_LEVEL_TRACE 0
#define BIT_LEVEL_INFO 1
#define BIT_LEVEL_WARN 2
#define BIT_LEVEL_ERROR 3
#define BIT_LEVEL_FATAL 4

#ifdef DEBUG
	#define CONSOLE_LOG_LEVEL BIT_LEVEL_TRACE
	#define FILE_LOG_LEVEL BIT_LEVEL_FATAL
#elif RELEASE
	#define CONSOLE_LOG_LEVEL BIT_LEVEL_INFO
	#define FILE_LOG_LEVEL BIT_LEVEL_FATAL
#else // DIST
	#define CONSOLE_LOG_LEVEL BIT_LEVEL_WARN
	#define FILE_LOG_LEVEL BIT_LEVEL_ERROR
#endif

#define LOG_MESSAGE(level, message) LOG::Message(level, message)

#define MIN_LOG_LEVEL (CONSOLE_LOG_LEVEL < FILE_LOG_LEVEL ? CONSOLE_LOG_LEVEL : FILE_LOG_LEVEL)

// --- TRACE ---
#if BIT_LEVEL_TRACE >= MIN_LOG_LEVEL
	#define LOG_TRACE(message) LOG_MESSAGE(LOG::Level::Trace, message)
#else
	#define LOG_TRACE(message)
#endif

// --- INFO ---
#if BIT_LEVEL_INFO >= MIN_LOG_LEVEL
	#define LOG_INFO(message) LOG_MESSAGE(LOG::Level::Info, message)
#else
	#define LOG_INFO(message)
#endif

// --- WARN ---
#if BIT_LEVEL_WARN >= MIN_LOG_LEVEL
	#define LOG_WARN(message) LOG_MESSAGE(LOG::Level::Warn, message)
#else
	#define LOG_WARN(message)
#endif

// --- ERROR ---
#if BIT_LEVEL_ERROR >= MIN_LOG_LEVEL
	#define LOG_ERROR(message) LOG_MESSAGE(LOG::Level::Error, message)
#else
	#define LOG_ERROR(message)
#endif

// --- FATAL ---
#define LOG_FATAL(message) LOG_MESSAGE(LOG::Level::Fatal, message)