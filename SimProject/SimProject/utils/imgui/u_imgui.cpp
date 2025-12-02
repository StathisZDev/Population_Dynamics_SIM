#include <utils/imgui/u_imgui.h>
#include <includes/global_state.h>
#include <includes/timer_manager.h>
#include <includes/settings.h>

ImVec4 graphWindowBgColor(0.89f, 0.91f, 0.95f, 1.0f);
ImVec4 menuWindowBgColor(0.90f, 0.88f, 0.83f, 1.0f);
ImVec4 dataWindowBgColor(0.95f, 0.94f, 0.89f, 1.0f);

void SetStyling()
{
	// 1. Get a reference to the global style
	ImGuiStyle& style = ImGui::GetStyle();

	// 1. Fix the "Bloat" (Optional: Manually force scale if auto-detection is wrong)
	// This is not the recommended approach
	//ImGui::GetIO().FontGlobalScale = 0.6f; // Tweak this if fonts are too big

	// 2. Fix the "Rounded Corners" (Explicitly force square look)
	style.WindowRounding = 0.0f;
	style.FrameRounding = 0.0f;
	style.GrabRounding = 0.0f;
	style.TabRounding = 0.0f;
	style.ScrollbarRounding = 0.0f;
	style.ChildRounding = 0.0f;
	style.PopupRounding = 0.0f;

	// 3. Compact the spacing if it feels "bloated"
	style.ItemSpacing = ImVec2(8, 4);
	style.FramePadding = ImVec2(4, 3);

	// 2. Define your color (Red, Green, Blue, Alpha)
	// Let's make a dark grey color
	/*ImVec4 graphWindowBgColor(0.89f, 0.91f, 0.95f, 1.0f);
	ImVec4 menuWindowBgColor(0.90f, 0.88f, 0.83f, 1.0f);
	ImVec4 dataWindowBgColor(0.95f, 0.94f, 0.89f, 1.0f);*/

	// 3. Assign it to the WindowBg index
	//style.Colors[ImGuiCol_WindowBg] = customBgColor;

	// Optional: You can also change floats directly
	//style.WindowRounding = 5.0f;
}

void CleanUpImGui()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
}

using namespace GlobalState;


// ------------------------------------------
// DISPLAY DATA FUNCTIONS
// ------------------------------------------
void DisplayData(ImFont* font, float deltaTime)
{
	// Running data display
	ImGui::PushStyleColor(ImGuiCol_WindowBg, dataWindowBgColor); // RGB F5F2E6
	ImGui::Begin("Running Simulation Data");
	if (font)  // Check if font was loaded successfully
	{
		ImGui::PushFont(font);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));

		ImGui::Text("Global Statistics");
		//ImGui::Separator(); 
		ImGui::Text("Total Population Size %d\n", GetPopulation());
		ImGui::Text("Total Resources %d", food);
		ImGui::NewLine();
		ImGui::Text("Temperature %d", temperature);
		ImGui::Text("Optimal Temperature %d", optimalTemperature);
		ImGui::Text("Required Food %d", requiredEnergy);
		ImGui::NewLine();
		//ImGui::Separator(); 
		ImGui::Text("Matured Population: %d ", maturedPopulation);
		ImGui::Text("Premature Deaths: %d ", GetPrematureDeaths());
		ImGui::NewLine();
		//ImGui::Separator();   
		ImGui::Text("deltaTime: %.2f ", deltaTime);
		ImGui::Text("Elapsed Time: %.2f ", TimerManager::elapsedTime);
		ImGui::Text("Fps: %d\n", TimerManager::fps);
		ImGui::PopStyleColor();
	}
	ImGui::PopFont();
	ImGui::PopStyleColor();
	ImGui::End();
}

void DisplayRibbon(ImFont* font) {
	ImGui::PushStyleColor(ImGuiCol_WindowBg, menuWindowBgColor); // Set window background to red
	ImGui::Begin("Simulation Parameters Ribbon");
	if (font)
	{
		ImGui::PushFont(font);
		ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.0f, 0.0f, 0.0f, 1.0f));
		ImGui::Button("Options", ImVec2(100, 30));
		ImGui::PopStyleColor();
	}
	ImGui::PopFont();
	ImGui::End();
	ImGui::PopStyleColor();
}