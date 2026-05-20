#ifndef MUNDOS_H
#define MUNDOS_H 
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "personaje.h"
#include <string>

struct nivel {  
    std::vector<personaje>enemigos;
    std::vector<std::string>historia;
    std::vector<SDL_Rect>paredes;
};

class mundo {
public:
    mundo();
    void cambiar_mundo(int neww);
    void aplicar_reglas(std::vector<personaje>& enemigos);
    std::vector<std::string> get_historia(); 
    int get_mundo_ctual(){
        return mundoActual;
    };

private:
    int mundoActual;
    void crearNivel();
    std::vector<nivel>niveles;
    bool mundoInicializado;
    bool mundo_cambio;
};

#endif // MUNDOS_H
