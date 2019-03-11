#pragma once

namespace Phantom {

	struct Members;

	class Timer
	{
	private:
		Members* m_Members;
	public:
		// Creates and starts timer
		Timer();
		// Resets and restarts timer
		virtual void Reset();
		// Returns time in seconds
		virtual float Elapsed();
		// Returns time in milliseconds
		virtual float ElapsedMillis();
	};

}