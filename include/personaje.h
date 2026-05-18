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
    SDL_Color color;
    int vida;

public: 
    personaje(int x, int y, int velocidad, SDL_Texture* textura, SDL_Color color, int vida = 100);
    void mover (int dx, int dy);
    void actualizar();
    void dibujar (SDL_Renderer* renderer);
    SDL_Rect getHitbox ();
    int getx();
    int gety();
    void setx(int x);
    void sety(int y);
    int getvida();
    void setvida(int vida);
    ~personaje();
};

#endif // PERSONAJE_H
