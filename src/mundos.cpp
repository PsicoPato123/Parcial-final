#include "mundos.h"

mundo::mundo(){
    mundoActual = 0;
    mundoInicializado= false;
    mundo_cambio = false;
}
void mundo:: cambiar_mundo(int neww){
    mundoActual = neww;
    mundoInicializado = true;
    mundo_cambio = true;
}
std::vector<std::string> mundo::get_historia() {
    if (mundoActual == 1){
        return {
            "Despierta...",
            "Este lugar resulta desconocido",
            "¿Por qué se siente un vacio?"
        };
    }
    if (mundoActual == 2){
        return {
            "La luz aún es brillante",
            "Me da una buena sensación este lugar",
            "Cuack! ^w^ ", 
    };}
    if (mundoActual == 3){
        return{
            "Algo me observa...",
            "¿Hay alguien aquí?",
            "Que extraño...",
    };}
    if (mundoActual == 4) {
        return{
            "El ambiente comienza a distorsionarse ...",
            "Ya no se ve de la misma manera",
            "¿Cuack?",
    };}
    if (mundoActual == 5) {
        return{
            "Los enemigos lo saben...",
            "¿Qué es lo que yo debo saber?",
            "Qué sucede?"
    };}
    if (mundoActual == 6){
        return{
             "No hay ni una voz, solo presencia",
             "Es esto ... ¿Un recuerdo?",
             "Debo salir..."
        };
    }
    if (mundoActual == 7){
        return{
            "No debería haber llegado hasta aquí...",
            "¿Eres tú...?",
            "¿M-ma...Mamá?",
        };}
    return{};
}
void mundo::aplicar_reglas(std::vector<personaje>& enemigos) {
    enemigos.clear();
    switch (mundoActual) {
        case 0:
            enemigos.push_back(personaje(100,100,2,nullptr, {103, 60, 25, 103}, 50));
        break;
        case 1:
            enemigos.push_back(personaje(200,120,2,nullptr,{120,40,40,255},60));
        break;
        case 2:
            enemigos.push_back(personaje(245,175,4,nullptr, {103, 37, 25, 103}, 100));
            enemigos.push_back(personaje(400,200,2,nullptr,{80,80,80,255},80));
        break;
        case 3:
            enemigos.push_back(personaje(300,200,3,nullptr,{227,115,22,255},120));
        break;
        case 4:
            enemigos.push_back(personaje(300,200,3,nullptr, {227, 115,22, 227}, 120));
        break;
        case 5:
            enemigos.push_back(personaje(250,250,4,nullptr,{50,50,50,255},180));
        break;
        case 6:
            enemigos.push_back(personaje(450,50,1,nullptr, {227, 36, 22, 227}, 180));
        break;
        case 7: 
            enemigos.push_back(personaje(400,300,8,nullptr,{0,0,0,255},250));
        break;
    }
}