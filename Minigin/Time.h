#pragma once
#include "Singleton.h"

// Based on "3D Game Programming with DirectX11" by Frank D. Luna: Chapter 4 section 3 "Timing and Animation"
// TODO: consider using std::chrono::high_resolution_clock or _Query_perf_counter()

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		void Initialize();

		float GetTotalTime()const;
		float GetDeltaTime()const;

		void Reset();
		void Start();
		void Stop();
		void Tick();
		
	private:
		float m_SecondsPerCount;
		float m_DeltaTime;

		__int64 m_BaseTime;
		__int64 m_PausedTime;
		__int64 m_StopTime;

		__int64 m_PrevTime;
		__int64 m_CurrTime;

		bool m_bIsStopped;
	};
}