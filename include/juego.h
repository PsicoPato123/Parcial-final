#define SDL_MAIN_HANDLED
#ifndef JUEGO_H
#define JUEGO_H
#include <SDL2/SDL.h>
#include "personaje.h"


class juego {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool caminando; 

public:
   juego();
    void inicializar();
    void loop();
    void actualizar();
    void mostrar();
    void teclado ();
    void limpiar();  
        
private:   
personaje personaje1;
~juego();
SDL_Rect paredarriba;
SDL_Rect paredabajo;
SDL_Rect paredizquierda;    
SDL_Rect paredderecha;
SDL_Rect paredderecha_up;
SDL_Rect paredderecha_down;
int oldx;
int oldy;
}; 
#endif // JUEGO_H
