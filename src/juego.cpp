#include "juego.h"
#include <iostream>
#include "personaje.h"

juego::juego() : personaje1(300, 250, 5, nullptr) {
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Juego SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    caminando = true;
}
void juego ::inicializar() {
    SDL_RenderPresent(renderer);
}
void juego::loop() {
    while (caminando){
        teclado();
        actualizar();
        mostrar();
        SDL_Delay(16);
}  }

void juego::mostrar(){
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); 
    personaje1.dibujar(renderer);
    SDL_RenderPresent (renderer);
 };

void juego::teclado() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_ESCAPE) {
                caminando = false;
            }
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    personaje1.mover(-1, 0);
                break;
                case SDLK_RIGHT:
                    personaje1.mover(1, 0);
                break;
                case SDLK_UP:
                    personaje1.mover(0, -1);
                break;
                case SDLK_DOWN:
                    personaje1.mover(0, 1);
                break;
            }
        }
    }
}


void juego::actualizar() {

}
juego::~juego(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}