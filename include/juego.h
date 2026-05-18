#define SDL_MAIN_HANDLED
#ifndef JUEGO_H
#define JUEGO_H
#include <SDL2/SDL.h>
#include "personaje.h"
#include <vector>

class juego {
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool caminando; 
    bool izquierda; 
    bool derecha;
    bool arriba;
    bool abajo;    

public:
   juego();
    void inicializar();
    void loop();
    void actualizar();
    void mostrar();
    void teclado ();
    void limpiar();  
    int vida;     
    int damagetime;
    bool ataque;
private:   
personaje personaje1;
std::vector<personaje> enemigos;
~juego();
SDL_Rect paredarriba;
SDL_Rect paredabajo;
SDL_Rect paredizquierda;    
SDL_Rect paredderecha;
SDL_Rect paredderecha_up;
SDL_Rect paredderecha_down;
int oldx;
int oldy;
int oldenemx;
int oldenemy;
SDL_Rect ataquehitbox;
int cooldown;

}; 
#endif // JUEGO_H
