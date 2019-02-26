/*Simple stopwatch based on chrono library by Kuba Maruszczyk*/
#pragma once
#include <chrono>
#include <ctime>
#include <ratio>
namespace RA_FRAMEWORK
{
	class Stopwatch
	{
	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_End;
		std::chrono::duration<double> m_Elapsed_seconds;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_PauseStart;
		std::chrono::duration<double > m_Paused_seconds;
		bool isRunning;
		bool isPaused;
	public:
		Stopwatch();
		Stopwatch(const Stopwatch&) = delete;
		Stopwatch &operator=(const Stopwatch&) = delete;
		~Stopwatch();
	public:
		void		Start();
		void		Stop();
		void		UnPause();
		void		Pause();
		double		ElapsedTime()const;
	};
}