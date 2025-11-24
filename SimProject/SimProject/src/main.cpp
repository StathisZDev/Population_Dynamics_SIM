#include <SDL3/SDL.h>
#include <stdio.h>
#include <libs/imgui/backends/imgui_impl_sdlrenderer3.h>
#include <libs/imgui/backends/imgui_impl_sdl3.h>
#include <libs/imgui/imgui.h>
#include <includes/timer_manager.h>
#include <utils/imgui/u_imgui.h>
#include <utils/sdl/u_sdl.h>
#include <includes/global_state.h>
#include <includes/settings.h>

int main(int argc, char* argv[])
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	int windowWidth = 1500;
	int windowHeight = 500;
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		printf("Failed to Initialize Video....\n");
		SDL_Quit();
		return -1;
	}

	int number = 0;

	window = SDL_CreateWindow("Population Dynamics SIM", 0, 0, WINDOW_SETTING_DEFAULT);
	SDL_SetWindowSize(window, windowWidth, windowHeight);
	renderer = SDL_CreateRenderer(window, nullptr);

	ImGui::CreateContext();

	ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer3_Init(renderer);

	float curTime = 0.f;

	bool running = true;
	
	GlobalState::InitializeGlobalState(STARTING_FOOD, STARTING_TEMPERATURE, ToxityLevel::DISABLED, Fertility::DISABLED, STARTING_POPULATION); 
	GlobalState::livingPopulation.reserve(100000);
	while (running)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_QUIT)
			{
				running = false;
			}
			ImGui_ImplSDL3_ProcessEvent(&event);
		}
		ImGui_ImplSDLRenderer3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();

		TimerManager::Update();
		TimerManager::SetTimerByEvent(GlobalState::Update, WORLD_UPDATE_FREQUENCY, TimerManager::elapsedTime);
		ImGuiTest(TimerManager::accumulatedTime);  

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

		SDL_RenderPresent(renderer);
	}
	CleanUpImGui();
	CleanUpSDL(renderer, window);
	exit(0);
}

