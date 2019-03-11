#include <Windows.h>
#include "Timer.h"
typedef unsigned long long int uint64;
namespace Phantom {

	struct Members
	{
		LARGE_INTEGER m_Start;
		double m_Frequency;//   1/cpu ±÷”∆µ¬    (second)
	};

	Timer::Timer()
		: m_Members(new Members())
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		m_Members->m_Frequency = 1.0 / frequency.QuadPart;

		Reset();
	}

	void Timer::Reset()
	{
		QueryPerformanceCounter(&m_Members->m_Start);
	}

	float Timer::Elapsed()
	{
		LARGE_INTEGER current;
		QueryPerformanceCounter(&current);
		uint64 cycles = current.QuadPart - m_Members->m_Start.QuadPart;
		return (float)(cycles * m_Members->m_Frequency);
	}

	float Timer::ElapsedMillis()
	{
		return Elapsed() * 1000.0f;  //∫¡√Î
	}

}