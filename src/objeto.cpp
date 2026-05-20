#include "objeto.h"

objeto::objeto(int x, int y) {
    this->x = x;
    this->y = y;
    recogido = false;
    lanzado = false; 
    velocidad = 5;
    direccionx=0;
    direcciony=0;
    hitbox = {x, y, 20, 20};
}

void objeto::dibujar(SDL_Renderer* renderer) {
    if (!recogido) {
        SDL_SetRenderDrawColor(renderer, 255,255,255,255);
        SDL_RenderFillRect(renderer, &hitbox);
    } }

void objeto::cambio(){
    if (lanzado){
        x+= direccionx * velocidad;
        y+= direcciony * velocidad; 
        hitbox.x=x;
        hitbox.y=y;
        if (x < 0 || x > 800 || y < 0 || y > 600){
        lanzado = false; }}
}
void objeto::lanzar(int dx, int dy){
    lanzado=true;
    direccionx=dx;
    direcciony=dy;
}
SDL_Rect objeto::getHitbox() {
    return hitbox;
}
bool objeto::en_mano() {
    return recogido;
}
bool objeto::lanzando(){
    return lanzado;
}
void objeto::recoger() {
    recogido = true;
}
int objeto::getx() {
    return x;
}
int objeto::gety() {
    return y;
}
void objeto::setx(int x) {
    this->x = x;
    hitbox.x=x;
}
void objeto::sety(int y) {
    this->y = y;
    hitbox.y=y;
}