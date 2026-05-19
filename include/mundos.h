#ifndef MUNDOS_H
#define MUNDOS_H 
#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include "personaje.h"

class Mundo {
public:
    Mundo();
    void cambiar_mundo(int nuevo);
    void aplicar_reglas(std::vector<personaje>& enemigos);
    void mensaje_historia();
    int get_mundo_ctual();

private:
    int mundoActual;
};

#endif // MUNDOS_H
