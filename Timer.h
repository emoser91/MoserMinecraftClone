#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

#include <SDL2\SDL.h>
#include <iostream>

class Timer
{
	public:
		void TimerStart()
		{
			startTime = SDL_GetTicks();
		}

		void TimerEnd(const std::string& message)
		{
			unsigned int endTime = SDL_GetTicks();
			std::cout << message << (endTime - startTime) << "ms" << std::endl;
		}

		void TimerClock()
		{
			unsigned elapsedTime = SDL_GetTicks(); //found in ms
			unsigned elapsedMilSecs = elapsedTime;
			unsigned elapsedSecs = (elapsedTime / 1000);
			unsigned elapsedMins = elapsedSecs / 60;

			std::cout << "\r" <<"Total Game Time: " << elapsedMins << ":" << elapsedSecs  - (60* elapsedMins ) << ":" << elapsedMilSecs - (1000* elapsedSecs);
			
		}

	protected:
	private:

		unsigned int startTime;

};

#endif // TIMER_H_INCLUDED

