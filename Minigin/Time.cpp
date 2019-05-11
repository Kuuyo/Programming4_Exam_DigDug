#include "MiniginPCH.h"
#include "Time.h"

#include <iomanip>

namespace dae
{
	Time::Time()
		: m_DeltaTime(-1.f)
		, m_BaseTime(0)
		, m_PausedTime(0)
		, m_PrevTime(0)
		, m_CurrTime(0)
		, m_bIsStopped(false)
		, m_ElapsedTime(0.f)
		, m_FrameCount(0)
		, m_FPS(0)
	{
		__int64 countsPerSec;
		QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&countsPerSec));
		m_SecondsPerCount = 1.f / static_cast<float>(countsPerSec);

		Reset();
	}

	float Time::GetTotalTime() const
	{
		if (m_bIsStopped)
			return static_cast<float>(((m_StopTime - m_PausedTime) - m_BaseTime) * m_SecondsPerCount);
		else
			return static_cast<float>(((m_CurrTime - m_PausedTime) - m_BaseTime) * m_SecondsPerCount);
	}

	std::string Time::GetTotalTimeFormatted() const
	{
		std::ios_base::fmtflags f(std::cout.flags());

		float seconds = glm::max(GetTotalTime(), 0.f);

		int secs = int(seconds);
		int hour = secs / 3600;
		int min = (secs / 60) % 60;
		int sec = secs % 60;

		int prec = int((seconds - int(seconds)) * 10000);

		std::stringstream ss;

		ss << std::setfill('0')
			<< std::setw(2) << hour
			<< ":" << std::setw(2) << min
			<< ":" << std::setw(2) << sec
			<< "." << std::setw(5) << prec;

		std::cout.flags(f);

		return ss.str();
	}

	float Time::GetDeltaTime() const
	{
		return static_cast<float>(m_DeltaTime);
	}

	unsigned int Time::GetFPS() const
	{
		return m_FPS;
	}

	void Time::Reset()
	{
		__int64 currTime;
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime));
		m_BaseTime = currTime;
		m_PrevTime = currTime;
		m_StopTime = 0;
		m_bIsStopped = false;
	}

	void Time::Start()
	{
		if (m_bIsStopped)
		{
			__int64 startTime;
			QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&startTime));

			m_PausedTime += (startTime - m_StopTime);

			m_PrevTime = startTime;

			m_StopTime = 0;
			m_bIsStopped = false;
		}
	}

	void Time::Stop()
	{
		if (!m_bIsStopped)
		{
			__int64 currTime;
			QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime));

			m_StopTime = currTime;
			m_bIsStopped = true;
		}
	}

	void Time::Tick()
	{
		if (m_bIsStopped)
		{
			m_DeltaTime = 0.0;
			return;
		}

		__int64 currTime;
		QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&currTime));
		m_CurrTime = currTime;

		m_DeltaTime = static_cast<float>((m_CurrTime - m_PrevTime) * m_SecondsPerCount);
		m_PrevTime = m_CurrTime;

		if (m_DeltaTime < 0.0)
			m_DeltaTime = 0.0;
	}

	void Time::CalculateFrameStats()
	{
		++m_FrameCount;

		if (GetTotalTime() - m_ElapsedTime >= 1.f)
		{
			m_FPS = m_FrameCount;
			m_FrameCount = 0;
			m_ElapsedTime += 1.f;
		}
	}
}