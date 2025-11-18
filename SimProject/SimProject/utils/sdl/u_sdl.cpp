#include <utils/sdl/u_sdl.h>

void CleanUpSDL(SDL_Renderer* renderer, SDL_Window* window)
{
	SDL_DestroyRenderer(renderer); 
	SDL_DestroyWindow(window);
	SDL_Quit();
}