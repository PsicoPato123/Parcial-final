#include "juego.h"
#include <iostream>
#include "personaje.h"

juego::juego() {
    personaje personaje1(100, 100, 5, nullptr);
    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("Juego SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    caminando = true;
    player_a = 300;
    player_b = 250;
    velocidad = 5;
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
    SDL_SetRenderDrawColor(renderer, 255, 255, 0, 1); 
    SDL_Rect player = { player_a, player_b, 100, 100 };
    personaje.dibujar(renderer);
    SDL_RenderFillRect(renderer, &player);
  
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
                    player_a -= velocidad;
                    break;
                case SDLK_RIGHT:
                    player_a += velocidad;
                    break;
                case SDLK_UP:
                    player_b -= velocidad;
                    break;
                case SDLK_DOWN:
                    player_b += velocidad;
                    break;
            }
        }
    }
}


void juego::actualizar() {

}