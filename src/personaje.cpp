#include "personaje.h"
#include <cstdlib>
#include <iostream>

personaje::personaje(int x, int y, int velocidad, SDL_Texture* textura) {
    this -> x = x;
    this -> y = y;
    this -> velocidad = velocidad;
    this -> textura = textura;
    hitbox.x = x;
    hitbox.y = y;
    hitbox.w = 50; 
    hitbox.h = 50;
}
void personaje::mover(int dx, int dy) {
    x += dx * velocidad;
    y += dy * velocidad;
    actualizar();
}
void personaje::dibujar(SDL_Renderer* renderer) {
    SDL_RenderFillRect(renderer, &hitbox);
}   
void personaje::actualizar() {
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > 750) x = 750;
    if (y > 550) y = 550;    
    hitbox.x = x;
    hitbox.y = y;
}   
personaje::~personaje(){
    SDL_DestroyTexture(textura);
}
 SDL_Rect personaje::getHitbox(){
        return hitbox;
    }
