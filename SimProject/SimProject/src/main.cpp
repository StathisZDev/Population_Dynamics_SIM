#include <SDL3/SDL.h>
#include <stdio.h>
#include <libs/imgui/backends/imgui_impl_sdlrenderer3.h>
#include <libs/imgui/backends/imgui_impl_sdl3.h>
#include <libs/imgui/imgui.h>
#include <includes/timer_manager.h>
#include <utils/imgui/u_imgui.h>
#include <utils/sdl/u_sdl.h>

void FunctionTest(); 

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
	
	window = SDL_CreateWindow("SDL3 Test Window!", 0, 0, WINDOW_SETTING_DEFAULT);  
	SDL_SetWindowSize(window, windowWidth, windowHeight);
	renderer = SDL_CreateRenderer(window, nullptr);
 
	ImGui::CreateContext();
	
	ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer3_Init(renderer);

	float curTime = 0.f;

	bool running = true;

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
		number++;
		ImGui_ImplSDLRenderer3_NewFrame();
		ImGui_ImplSDL3_NewFrame();
		ImGui::NewFrame();

		TimerManager::Update();
		TimerManager::SetTimerByEvent(FunctionTest, 5, TimerManager::deltaTime);
		ImGuiTest(TimerManager::deltaTime);

		SDL_SetRenderDrawColor(renderer, 36, 36, 36, 1);
		SDL_RenderClear(renderer);

		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

		SDL_RenderPresent(renderer);
	}
	CleanUpImGui();
	CleanUpSDL(renderer, window);
	exit(0);
}

void FunctionTest()
{
	printf("Function Call by timer Succesfull\n");
}
//https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html