#include "pchEng.h"
#include "Logging.h"

namespace LOG
{
	static std::string s_FileName;
	static std::ofstream s_LogFile;

	static const std::unordered_map<Level, const char*> s_Colors = {
		{ Level::None, "\033[0m" },		// default
		{ Level::Trace, "\033[0;90m" }, // Gray
		{ Level::Info, "\033[1;32m" },	// Bold Green
		{ Level::Warn, "\033[1;33m" },	// Bold Yellow
		{ Level::Error, "\033[1;31m" }, // Bold Red
		{ Level::Fatal, "\033[1;41m" }	// Bold Red Background
	};

	static const std::unordered_map<Level, const char*> s_Prefix = {
		{ Level::Trace, "--TRACE-- " },
		{ Level::Info, "--INFO-- " },
		{ Level::Warn, "--WARN-- " },
		{ Level::Error, "--ERROR-- " },
		{ Level::Fatal, "--FATAL-- " }
	};

	static inline void sLogConsole(Level level, std::string_view message, const std::string& timeStamp)
	{
		if (level < CONSOLE_LOG_LEVEL)
			return;

		std::cout << s_Colors.at(level) << "[" << timeStamp << "] " << s_Prefix.at(level) << message << s_Colors.at(Level::None) << std::endl;
	}

	static inline void sLogFile(Level level, std::string_view message, const std::string& timeStamp, const std::string& fileName)
	{
		if (level < FILE_LOG_LEVEL)
			return;

		if (s_FileName.empty())
		{
			std::filesystem::path path(SDL_GetBasePath());

			path /= "Logs";

			std::filesystem::create_directory(path);

			path /= fileName;

			s_FileName = path.string();

			s_LogFile.open(s_FileName, std::ios_base::app);
		}

		if (s_LogFile.is_open())
		{
			s_LogFile << "[" << timeStamp << "] " << s_Prefix.at(level) << message << std::endl;

			if (level > Level::Warn)
				s_LogFile.flush();
		}
	}

	void Message(Level level, std::string_view message)
	{
		if (level == Level::None)
			return;

		auto miliSeconds = std::chrono::current_zone()->to_local(std::chrono::system_clock::now());

		auto seconds = std::chrono::floor<std::chrono::seconds>(miliSeconds);

		std::string timeStamp = std::format("{:%H:%M:%S}", seconds);

		std::string fileName = std::format("Log_{:%Y-%m-%d_%H-%M-%S}.log", seconds);

		sLogConsole(level, message, timeStamp);
		sLogFile(level, message, timeStamp, fileName);

		if (level == Level::None || level == Level::Fatal)
		{
			std::cout << "FATAL ERROR. Terminating..." << std::endl;
			std::abort();
		}
	}

} // namespace LOG
