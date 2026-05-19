#ifndef MUNDOS_H
#define MUNDOS_H 
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "personaje.h"
#include <string>

class mundo {
public:
    mundo();
    void cambiar_mundo(int nuevo);
    void aplicar_reglas(std::vector<personaje>& enemigos);
    void mensaje_historia();
    int get_mundo_ctual(){
        return mundoActual;
    };

private:
    int mundoActual;
    bool mundoInicializado;
    struct nivel {
        int lugar;
        int enemigo;
        int luz;
        std::string historia;
    };
    std::vector<nivel> nivel; 
};

#endif // MUNDOS_H
