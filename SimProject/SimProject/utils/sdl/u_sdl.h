#include <SDL3/SDL.h>

#define WINDOW_SETTING_DEFAULT SDL_WINDOW_RESIZABLE | SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_TRANSPARENT //| SDL_WINDOW_FULLSCREEN
/// <summary>
/// Destroys the renderer the window and then SDL_Quit is called
/// </summary>
/// <param name="ren"></param>
/// <param name="win"></param>
void CleanUpSDL(SDL_Renderer* renderer, SDL_Window* window);

//void SetWindowDimensions(); 
extern int windowWidth;
extern int windowHeight; 