#include <includes/timer_manager.h> 
#include <stdio.h>
#include <SDL3/SDL.h>

float TimerManager::currentFrame = 0;
float TimerManager::lastFrame = 0;
float TimerManager::deltaTime = 0;
float TimerManager::temp = 0;
bool TimerManager::bIsCounting = false;

void TimerManager::Update()
{
	lastFrame = currentFrame; 
	currentFrame = (float)SDL_GetTicks(); 
	deltaTime += (currentFrame - lastFrame) / 1000.0f;
}

void TimerManager::SetTimerByEvent(void function(), int delay, float deltaTime)
{
	if (delay <= 0)
	{
		printf("Cant have 0 or negative delay");
		return;
	}
	if (!TimerManager::bIsCounting)
	{
		temp = delay + deltaTime;
		TimerManager::bIsCounting = true;
	}
	else if (TimerManager::bIsCounting)
	{
		if (deltaTime >= temp)
		{
			function();
			TimerManager::bIsCounting = false;
		}
	}
	
}