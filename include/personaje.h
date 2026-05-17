#ifndef PERSONAJE_H
#define PERSONAJE_H 
#include <SDL2/SDL.h>

class personaje {
private:
    int x;
    int y;
    int velocidad;
    SDL_Texture* textura;
    SDL_Rect hitbox;

public: 
    personaje(int x, int y, int velocidad, SDL_Texture* textura);
    void mover (int dx, int dy);
    void actualizar();
    void dibujar (SDL_Renderer* renderer);
    ~personaje();
};

#endif // PERSONAJE_H
