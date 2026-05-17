#define SDL_MAIN_HANDLED
#ifndef GAME_H
#define GAME_H
#include <SDL2/SDL.h>


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
    int player_a;
    int player_b;
    int velocidad;
}; 
#endif // GAME_H
