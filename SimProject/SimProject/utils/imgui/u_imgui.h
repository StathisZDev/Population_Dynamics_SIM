#include <libs/imgui/imgui.h>
#include <libs/imgui/backends/imgui_impl_sdlrenderer3.h>
#include <libs/imgui/backends/imgui_impl_sdl3.h>

// Definitions of functions for the u_imgui.cpp, u_implot.h, and u_implot.cpp files

// Window styling
extern ImVec4 graphWindowBgColor;
extern ImVec4 menuWindowBgColor;
extern ImVec4 dataWindowBgColor;

//ImVec4 graphWindowBgColor;
//ImVec4 dataWindowBgColor;
//ImVec4 menuWindowBgColor;

void CleanUpImGui(); 

void SetStyling();


// Functions for ImGui windows without ImPlot graphs.They will be removed from pushed code
void DisplayRibbon(ImFont* font);

void DisplayData(ImFont* font, float deltaTime);

void PrintImGuiSettings();