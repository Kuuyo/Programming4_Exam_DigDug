#pragma once
#include "Singleton.h"

// TODO: Finish the logger and start logging
// Based on OverLord Logger
namespace dae
{
	enum class LogLevel
	{
		Info,
		Debug,
		Warning,
		Error
	};

	class Time;

	class Log final : public Singleton<Log>
	{
	public:
		Log() = default;

		void Initialize();
		void CleanUp();

		void SetGlobalTime(Time* pTime);
		void SetSceneTime(Time* pTime);

		void LogFormat(LogLevel level, const std::string& caller, const char* msg, ...);
		void LogInfo(const std::string& msg, const std::string& caller);
		void LogDebug(const std::string& msg, const std::string& caller);
		void LogWarning(const std::string& msg, const std::string& caller);
		void LogError(const std::string& msg, const std::string& caller);

		Log(const Log &) = delete;
		Log(Log &&) = delete;
		Log& operator= (const Log&) = delete;
		Log& operator= (const Log&&) = delete;

	private:
		void InternalLog(LogLevel level, const std::string& msg, const std::string& caller ="");

		Time* m_pGlobalTime = nullptr;
		Time* m_pSceneTime = nullptr;

		static HANDLE m_ConsoleHandle;
		const unsigned int m_ConvertBufferSize = 1024;
		char* m_ConvertBuffer = nullptr;	
	};

	// The C stands for it returns the caller
#define LogFormatC(lvl, msg, ...) dae::Log::GetInstance().LogFormat(lvl, __FUNCTION__, msg, __VA_ARGS__)
#define LogInfoC(msg) dae::Log::GetInstance().LogInfo(msg, __FUNCTION__)
#define LogDebugC(msg)  dae::Log::GetInstance().LogDebug(msg, __FUNCTION__)
#define LogWarningC(msg) dae::Log::GetInstance().LogWarning(msg, __FUNCTION__)
#define LogErrorC(msg) dae::Log::GetInstance().LogError(msg, __FUNCTION__)
}
