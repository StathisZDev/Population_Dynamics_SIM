#include <utils/imgui/u_imgui.h>

void CleanUpImGui()
{
	ImGui_ImplSDLRenderer3_Shutdown();
	ImGui_ImplSDL3_Shutdown();
	ImGui::DestroyContext();
}

void ImGuiTest(float deltaTime)
{
	ImGui::Begin("Hello World");
	ImGui::Text("Text Test");
	ImGui::Text("Current Population Goes HERE");
	ImGui::NewLine();
	ImGui::Text("elapsed time : %.2f ", deltaTime);
	ImGui::Button("label", { 100,20 });
	ImGui::End();
	ImGui::Render();
}
