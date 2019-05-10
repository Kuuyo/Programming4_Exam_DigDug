#include "MiniginPCH.h"
#include "Log.h"

#include "Time.h"

#include <iostream>

namespace dae
{
	HANDLE Log::m_ConsoleHandle = nullptr;

	void Log::Initialize()
	{
#ifdef _DEBUG
		if (AllocConsole())
		{
			FILE* pCout;
			freopen_s(&pCout, "CONIN$", "r", stdin);
			freopen_s(&pCout, "CONOUT$", "w", stdout);
			freopen_s(&pCout, "CONOUT$", "w", stderr);

			std::wcout.clear();
			std::cout.clear();
			std::wcerr.clear();
			std::cerr.clear();
			std::wcin.clear();
			std::cin.clear();
			std::cin.clear();

			m_ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTitle("DebugConsole");
		}
#endif

		m_ConvertBuffer = new char[m_ConvertBufferSize];
	}

	void Log::CleanUp()
	{
#ifdef _DEBUG
		FreeConsole();
#endif

		delete[] m_ConvertBuffer;
	}

	void Log::SetGlobalTime(Time* pTime)
	{
		m_pGlobalTime = pTime;
	}

	void Log::SetSceneTime(Time* pTime)
	{
		m_pSceneTime = pTime;
	}

	void Log::LogFormat(LogLevel level, const std::string& caller, const char* msg, ...)
	{
		va_list ap;

		va_start(ap, msg);
		_vsnprintf_s(&m_ConvertBuffer[0], m_ConvertBufferSize, m_ConvertBufferSize, msg, ap);
		va_end(ap);

		InternalLog(level, std::string(&m_ConvertBuffer[0]), caller);
	}

	void Log::LogInfo(const std::string& msg, const std::string& caller)
	{
#ifdef _DEBUG
		InternalLog(LogLevel::Info, msg, caller);
#else
		(msg);
		(caller);
#endif
	}

	void Log::LogDebug(const std::string& msg, const std::string& caller)
	{
#ifdef _DEBUG
		InternalLog(LogLevel::Debug, msg, caller);
#else
		(msg);
		(caller);
#endif
	}

	void Log::LogWarning(const std::string& msg, const std::string& caller)
	{
		InternalLog(LogLevel::Warning, msg, caller);
	}

	void Log::LogError(const std::string& msg, const std::string& caller)
	{
		InternalLog(LogLevel::Error, msg, caller);
	}

	void Log::InternalLog(LogLevel level, const std::string& msg, const std::string& caller)
	{
		std::stringstream ss;

		if (m_pGlobalTime != nullptr)
		{
			SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			ss << "[" << m_pGlobalTime->GetTotalTimeFormatted() << "] ";
			std::cout << ss.str();
			ss = std::stringstream();
		}

		switch (level)
		{
		case dae::LogLevel::Info:
			SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			ss << "[INFO]:: << ";
			break;
		case dae::LogLevel::Debug:
			SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			ss << "[DEBUG]:: << ";
			break;
		case dae::LogLevel::Warning:
			SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN);
			ss << "[WARNING]:: << ";
			break;
		case dae::LogLevel::Error:
			SetConsoleTextAttribute(m_ConsoleHandle, FOREGROUND_INTENSITY | FOREGROUND_RED);
			ss << "[ERROR]:: << ";
			break;
		default:
			break;
		}

		ss << caller << " >> ";
		ss << msg;
		ss << "\n";

		std::cout << ss.str();
	}
}