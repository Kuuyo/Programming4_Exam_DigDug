#pragma once
#include "Singleton.h"

// Based on "3D Game Programming with DirectX11" by Frank D. Luna: Chapter 4 section 3 "Timing and Animation"
// And Chapter 4 Section 4 Point 4 for CalculateFrameStat();

// TODO: consider using std::chrono::high_resolution_clock or _Query_perf_counter(); SetThreadAffinity if still QPC to avoid it misbehaving?

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		void Initialize();

		float GetTotalTime()const;
		float GetDeltaTime()const;
		unsigned int GetFPS()const;

		void Reset();
		void Start();
		void Stop();
		void Tick();

		void CalculateFrameStats();
		
	private:	

		float m_SecondsPerCount;
		float m_DeltaTime;
		float m_ElapsedTime;

		unsigned int m_FrameCount;
		unsigned int m_FPS;

		__int64 m_BaseTime;
		__int64 m_PausedTime;
		__int64 m_StopTime;

		__int64 m_PrevTime;
		__int64 m_CurrTime;

		bool m_bIsStopped;
	};
}