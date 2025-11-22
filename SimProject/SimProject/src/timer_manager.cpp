#include <includes/timer_manager.h> 
#include <stdio.h>
#include <SDL3/SDL.h>

namespace TimerManager
{
	float currentFrame = 0;
	float lastFrame = 0;
	float deltaTime = 0;
	float temp = 0;
	bool bIsCounting = false;

	void Update()
	{
		lastFrame = currentFrame;
		currentFrame = (float)SDL_GetTicks();
		deltaTime += (currentFrame - lastFrame) / 1000.0f;
	}

	void SetTimerByEvent(void function(), float delay, float deltaTime)
	{
		if (delay <= 0)
		{
			printf("Cant have 0 or negative delay");
			return;
		}
		if (!bIsCounting)
		{
			temp = delay + deltaTime;
			bIsCounting = true;
		}
		else if (bIsCounting)
		{
			if (deltaTime >= temp)
			{
				function();
				bIsCounting = false;
			}
		}

	}
}
