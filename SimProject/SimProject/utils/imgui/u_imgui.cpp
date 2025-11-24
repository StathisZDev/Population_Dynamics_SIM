#include <utils/imgui/u_imgui.h>
#include <includes/global_state.h>
#include <includes/timer_manager.h>
void CleanUpImGui()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiTest(float deltaTime)
{
	ImGui::Begin("-");
	ImGui::Text("Global Statistics");
	//ImGui::Separator(); 
	ImGui::Text("population %d\n", GlobalState::GetPopulation());
	ImGui::Text("resources %d", GlobalState::food);
	ImGui::NewLine(); 
	//ImGui::Separator(); 
	ImGui::Text("matured population: %d ", GlobalState::maturedPopulation); 
	ImGui::Text("premature deaths: %d ", GlobalState::GetPrematureDeaths()); 
	ImGui::NewLine(); 
	ImGui::NewLine(); 
	ImGui::NewLine();   
	//ImGui::Separator();   
	ImGui::Text("deltaTime: %.2f ", deltaTime);
	ImGui::Text("elapsed time: %.2f ", TimerManager::elapsedTime);
	ImGui::Text("fps: %d\n", TimerManager::fps);  
	ImGui::End();
	ImGui::Render();
}
