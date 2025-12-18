#include <SDL3/SDL.h>
#include <SDL3/SDL_Log.h>
#include <libs/imgui/backends/imgui_impl_sdlrenderer3.h>
#include <libs/imgui/backends/imgui_impl_sdl3.h>
#include <libs/imgui/imgui.h>
#include <libs/implot/implot.h>
#include <includes/timer_manager.h>
#include <utils/imgui/u_imgui.h>
#include <utils/implot/u_implot.h>
#include <utils/sdl/u_sdl.h>
#include <includes/global_state.h>
#include <includes/settings.h>
#include <iostream>

void FunctionTest();


int main(int argc, char* argv[])
{
	// ---------------------------------
	// Basic SDL Setup
	// ---------------------------------

	SDL_Window* window;
	SDL_Renderer* renderer;

	int windowWidth = 1500;
	int windowHeight = 500;
	if (!SDL_Init(SDL_INIT_VIDEO))
	{
		SDL_Log("Failed to initialize SDL: %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}

	int number = 0;   


	// SDL window properties
	SDL_PropertiesID props = SDL_CreateProperties();
	if (props == 0) {
		SDL_Log("Unable to create properties: %s", SDL_GetError());
		return -1;
	}

	SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_ALWAYS_ON_TOP_BOOLEAN, false);
	SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_HIGH_PIXEL_DENSITY_BOOLEAN, true);
	SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_RESIZABLE_BOOLEAN, true);
	SDL_SetBooleanProperty(props, SDL_PROP_WINDOW_CREATE_MAXIMIZED_BOOLEAN, true);
	SDL_SetStringProperty(props, SDL_PROP_WINDOW_CREATE_TITLE_STRING, "Bacteria Population Simulation");
	SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_X_NUMBER, SDL_WINDOWPOS_CENTERED);
	SDL_SetNumberProperty(props, SDL_PROP_WINDOW_CREATE_Y_NUMBER, SDL_WINDOWPOS_CENTERED);
	
	//window = SDL_CreateWindow("Population Dynamics SIM", 0, 0, WINDOW_SETTING_DEFAULT);
	window = SDL_CreateWindowWithProperties(props);
	if (window == NULL) {
		SDL_Log("Failed to create SDL Window: %s\n", SDL_GetError());
		return -1;
	}

	//SDL_SetWindowSize(window, windowWidth, windowHeight);
	SDL_SetWindowSize(window, windowWidth, windowHeight);

	renderer = SDL_CreateRenderer(window, nullptr);

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 1);
	SDL_RenderClear(renderer);

	// ------------------------------------
	// ImGui & ImPlot setup
	// ------------------------------------
	ImGui::CreateContext();
	ImPlot::CreateContext();  // Create ImPlot context AFTER ImGui context

	SetStyling();
	// Set font style
	ImGuiIO& io = ImGui::GetIO();
	ImFont* font = io.Fonts->AddFontFromFileTTF("fonts/static/OpenSans-Regular.ttf", 24.0f);
	
	ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
	ImGui_ImplSDLRenderer3_Init(renderer);
	io.Fonts->Build();

	// Main loop setup
	float curTime = 0.f;
	bool running = true;
	
	InitializeData();  // Defined in u_implot.cpp
	GlobalState::InitializeGlobalState(STARTING_FOOD, STARTING_TEMPERATURE, ToxityLevel::DISABLED, Fertility::DISABLED, STARTING_POPULATION,BacteriaTempType::PSYCHROPHILES); 
	GlobalState::livingPopulation.reserve(100000);
	
	// ------------------------------------
	// MAIN LOOP
	// ------------------------------------

	bool done = false;
	bool opened = true;
	bool checkbox1 = false;
	bool checkbox2 = false;
	float value1 = 0.1f;
	int zoom = 1;

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
		TimerManager::SetTimerByEvent(GlobalState::Update, WORLD_UPDATE_FREQUENCY, TimerManager::elapsedTime);
		
		// ---------------------------------------------
		// DEBUG & STYLING EXPERIMENTATION WINDOWS
		// ---------------------------------------------
		
		// Activate this if you want to experiment with styling.
		// When you're done, go to the SetStyling() function in u_imgui.cpp and add the necessary lines to the code
		//ImGui::ShowStyleEditor();
		
		// Debug Window. It shows what ImGui perceives the Display Size, Framebuffer Scale, and Font Global Scale are
		//PrintImGuiSettings();
		
		// ------------------------------------------------------------------
		// IMGUI WINDOWS
		// Add each new window using the format below
		// ------------------------------------------------------------------
		// MENU WINDOW
		ImGui::SetNextWindowSize(ImVec2(200, 300));
		if (ImGui::Begin("Menu", &opened, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize)) {
			//BUTTONS
			if (ImGui::Button("Start")) {

			}
			if (ImGui::Button("Stop")) {

			}
			if (ImGui::Button("Reset")) {

			}

			//CHECKBOXES
			ImGui::Checkbox("Turn On/Off", &checkbox1);
			ImGui::Checkbox("Turn On/Off No2", &checkbox2);

			//SLIDERS
			ImGui::SliderFloat("Slider 1", &value1, 0.0f, 10.0f);
			ImGui::SliderInt("Zoom", &zoom, 0, 10);
		}
		ImGui::End();

		// Window 1: This window will store a ribbon of options
		DisplayRibbon(font);

		// Window 2: This window displays a plot with Time on the x-axis and Population Size, Food & Temperature on the y-axis
		PrepareData();  // Defined in u_implot.cpp
		LinePlotTime("Line Graph", "Population Size, Food, and Temperature as a function of Time");  // Defined in u_implot.cpp
		
		// Window 3: This window displays simulation running data	
		DisplayData(font, TimerManager::accumulatedTime);  

		// --------------------------------------------
		// RENDERING
		// --------------------------------------------
		ImGui::Render();

		TimerManager::Update();
		TimerManager::SetTimerByEvent(FunctionTest, 5, TimerManager::deltaTime);
		


		SDL_SetRenderDrawColor(renderer, 36, 36, 36, 1);
		SDL_RenderClear(renderer);

		ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData(), renderer);

		SDL_RenderPresent(renderer);
	}
	// ----------------------------
	// WRAPPING UP
	// ----------------------------
	ImPlot::DestroyContext();  // Destroy ImPlot context BEFORE ImGui context
	CleanUpImGui();   // Wrapper function defined in u_imgui.cpp
	CleanUpSDL(renderer, window);
	SDL_DestroyProperties(props);

	exit(0);
}

void FunctionTest()
{
	printf("Function Call by timer Succesfull\n");
}
//https://pthom.github.io/imgui_manual_online/manual/imgui_manual.html