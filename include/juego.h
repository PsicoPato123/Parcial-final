#define SDL_MAIN_HANDLED
#ifndef JUEGO_H
#define JUEGO_H
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "personaje.h"
#include <vector>
#include "mundos.h"


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
    int lvlluz; 
    enum estado_jugador{
    vivo, muerto, en_transicion
    };
    ~juego();

private:   
    personaje personaje1;
    std::vector<personaje> enemigos;
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
    int direccionx;
    int direcciony;
    void vuelta_ala_tierra();
    std::vector<int> memorias;
    estado_jugador estado;
    mundo mundo;
    bool dialogo = false;
    int linea_dialogo = 0;
    std::vector<std::string> dialogo_ctual;  
    TTF_Font* fuente;

    int chars_mostrados = 0;
    int delay_escritura = 2; 
    int tiempo_escribiendo= 0;
}; 
#endif // JUEGO_H
