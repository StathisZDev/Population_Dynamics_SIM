#include <SDL3/SDL.h>
#include <stdio.h>
#include <libs/imgui/backends/imgui_impl_sdlrenderer3.h>
#include <libs/imgui/backends/imgui_impl_sdl3.h>
#include <libs/imgui/imgui.h>
#include  <includes/TimerManager.h>


//TEMPORARY CODE TO TEST LIBRARIES. 

int width = 1700;
int height = 1000;

#define WINDOWSETTINGS001 SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_TRANSPARENT
//ImGuiIO& io = ImGui::GetIO(); (void)io;       

void CleanUpSDL(SDL_Renderer* ren, SDL_Window* win);
void CleanUpImGui();


int main(int argc, char* argv[])
{

	SDL_Window* window;
	SDL_Renderer* renderer;

	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		printf("Failed to Initialize Video....\n");
		SDL_Quit();
		return -1;
	}

	int number = 0;

	window = SDL_CreateWindow("SDL3 Test Window!", width, height, WINDOWSETTINGS001);
	renderer = SDL_CreateRenderer(window, nullptr);

	//Create Context for ImGui    
	ImGui::CreateContext();

	//Initialize ImGui for SDL 
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

		//Simple ImGui UI 
		{
			ImGui::Begin("Hello World");

			ImGui::Text("Text Test");


			//ImGui::Text((const char*) number);

			ImGui::Text("Current Population Goes HERE");
			ImGui::NewLine();
			ImGui::Text("Population: %.1f ", TimerManager::deltaTimem);
			ImGui::Button("label", { 100,20 });
			ImGui::End();

			ImGui::Render();


		}
		//https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html
		//number++;
		//SDL_Delay(59);


		SDL_SetRenderDrawColor(renderer, 36, 36, 36, 1);
		SDL_RenderClear(renderer);

		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

		SDL_RenderPresent(renderer);
		//SDL_Delay(59);
	}


	CleanUpImGui();
	CleanUpSDL(renderer, window);

	exit(0);
}

void CleanUpSDL(SDL_Renderer* ren, SDL_Window* win)
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
}

void CleanUpImGui()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
}




