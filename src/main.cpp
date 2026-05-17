#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>

int main(){
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if(window == NULL)
{   std::cout << SDL_GetError();
}
    SDL_Delay(3000);
    std::cout << "FUNCIONA\n";
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}   