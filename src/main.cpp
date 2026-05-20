#define SDL_MAIN_HANDLED
#include <iostream>
#include <SDL2/SDL.h>
#include "juego.h"

int main() {
    juego juego;

    juego.inicializar();
    juego.loop();

    return 0;
}