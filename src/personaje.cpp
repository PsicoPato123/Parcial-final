#include "personaje.h"
#include <cstdlib>
#include <iostream>

personaje::personaje(int x, int y, int velocidad, SDL_Texture* textura, SDL_Color color, int vida) {
    this -> x = x;
    this -> y = y;
    this -> velocidad = velocidad;
    this -> textura = textura;
    this -> color = color;
    this -> vida = vida;
    hitbox.x = x;
    hitbox.y = y;
    hitbox.w = 50; 
    hitbox.h = 50;
    bool activo = true; 
}
void personaje::mover(int dx, int dy) {
    x += dx * velocidad;
    y += dy * velocidad;
    actualizar();
}
void personaje::dibujar(SDL_Renderer* renderer) {
    SDL_Rect cuerpo = {x, y + 15, 40, 30};
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &cuerpo);
    SDL_Rect cabeza = {x + 22, y, 22, 20};
    SDL_RenderFillRect(renderer, &cabeza);
    SDL_Rect pico = {x + 44, y + 6, 10, 6};
    SDL_SetRenderDrawColor(renderer, 255, 140, 0, 255);
    SDL_RenderFillRect(renderer, &pico);
    SDL_Rect ojo = {x + 36, y + 4, 4, 4};
    SDL_SetRenderDrawColor(renderer, 70,230,251, 255);
    SDL_RenderFillRect(renderer, &ojo);
    SDL_Rect ala = {x + 8, y + 20, 16, 10};
    SDL_SetRenderDrawColor(renderer, 
        color.r > 20 ? color.r - 20 : 0,
        color.g > 20 ? color.g - 20 : 0,
        color.b > 20 ? color.b - 20 : 0,
        color.a);
    SDL_RenderFillRect(renderer, &ala);
    SDL_SetRenderDrawColor(renderer, 255, 140, 0, 255);
    SDL_Rect pata1 = {x + 10, y + 44, 6, 8};
    SDL_Rect pata2 = {x + 24, y + 44, 6, 8};
    SDL_RenderFillRect(renderer, &pata1);
    SDL_RenderFillRect(renderer, &pata2);
}

void personaje::actualizar() {
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > 750) x = 750;
    if (y > 550) y = 550;    
    hitbox.x = x;
    hitbox.y = y;
}   
 int personaje::getx(){
    return x;
    }
    int personaje::gety(){
        return y;
    }
    void personaje::setx(int x){
        this -> x = x;
        actualizar();
    }
    void personaje::sety(int y){
        this -> y = y;
        actualizar();
    }
int personaje::getvida(){
    return vida;
}
void personaje::setvida(int vida){
    this -> vida = vida;
}
personaje::~personaje(){
    if (textura !=nullptr){
    SDL_DestroyTexture(textura);
}}
 SDL_Rect personaje::getHitbox(){
        return hitbox;
    }
