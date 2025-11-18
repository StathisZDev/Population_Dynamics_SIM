#pragma once

#include "SDL3/SDL_time.h"


namespace TimerManager
{
	float currentFramem = 0;
	float lastFramem = 0;
	float deltaTimem = 0;

	void Update();
}

void TimerManager::Update()
{
	lastFramem = currentFramem;
	currentFramem = (float)SDL_GetTicks();
	deltaTimem += (currentFramem - lastFramem) / 1000.0f;//1000 converts ms->seconds
}

