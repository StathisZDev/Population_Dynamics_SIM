#pragma once

#include <SDL3/SDL.h> 


namespace TimerManager
{
	extern float currentFrame;
	extern float lastFrame;
	extern float deltaTime; 
	extern float temp;
	extern bool  bIsCounting;
	/// <summary>
	/// Converts frame generation difference bettwen last frame
	/// and current frame to time to delta time
	/// </summary>
	void Update();
	/// <summary>
	/// Set a delay to infinetly call a function with a timer
	/// </summary>
	/// <param name="function -->">The function to call when timer expires</param>
	/// <param name="delay -->">Delay in seconds before calling the function</paarm>    
	/// Delay should be > 0 else the function will stop excecuting and reuturn void
	void SetTimerByEvent(void function(),int delay,float deltaTime);
}


