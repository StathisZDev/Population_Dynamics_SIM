#include <utils/imgui/u_imgui.h>
#include <includes/global_state.h>
#include <includes/timer_manager.h>
#include <includes/settings.h>
void CleanUpImGui()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
}

using namespace GlobalState;

void ImGuiTest(float deltaTime)
{
	ImGui::Begin("-");
	ImGui::Text("Global Statistics");
	//ImGui::Separator(); 
	ImGui::Text("population %d\n", GetPopulation());
	ImGui::Text("resources %d", food);
	ImGui::NewLine();
	ImGui::Text("temperature %d", temperature); 
	ImGui::Text("optimal temperature %d", optimalTemperature);   
	ImGui::Text("required food %d", requiredEnergy);
	ImGui::NewLine(); 
	//ImGui::Separator(); 
	ImGui::Text("matured population: %d ", maturedPopulation); 
	ImGui::Text("premature deaths: %d ", GetPrematureDeaths()); 
	ImGui::NewLine(); 
	//ImGui::Separator();   
	ImGui::Text("deltaTime: %.2f ", deltaTime);
	ImGui::Text("elapsed time: %.2f ", TimerManager::elapsedTime);
	ImGui::Text("fps: %d\n", TimerManager::fps);  
	ImGui::End();
	ImGui::Render();
}
