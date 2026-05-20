#ifndef OBJETO_H
#define OBJETO_H
#include <SDL2/SDL.h>

class objeto {

private:
    int x;
    int y;
    int direccionx;
    int direcciony;
    bool recogido;
    bool lanzado;
    int velocidad;
    SDL_Rect hitbox;

public:
    objeto(int x, int y);
    void dibujar(SDL_Renderer* renderer);
    void lanzar (int dx, int dy);   
    void cambio ();
    SDL_Rect getHitbox();
    bool en_mano();
    bool lanzando();
    void recoger();
    
    int getx();
    int gety();
    void setx(int x);
    void sety(int y);
};
#endif