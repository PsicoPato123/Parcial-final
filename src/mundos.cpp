#include "mundos.h"

mundo::mundo(){
    mundoActual = 0;
    mundoInicializado= false;
}
void mundo:: cambiar_mundo(int neww){
    mundoActual = neww;
    
}
void mundo::mensaje_historia() {
    switch (mundoActual) {
        case 0:
            std::cout << "Iniciando sistema...\n";
            break;
        case 1:
            std::cout << "La luz es bastante brillante...\n";
            break;
        case 2:
            std::cout << "Algo me observa...\n";
            break;
        case 3:
            std::cout << "El ambiente comienza a distorsionar...\n";
            break;
        case 4:
            std::cout << "Los enemigos saben...\n";
            break;
        case 5:
            std::cout << "No hay ni una voz... solo presencia...\n";
            break;
        case 6:
            std::cout << "Recuerdos llegando...\n";
            break;
        case 7:
            std::cout << "No debería haber llegado hasta aquí...\n";
            break;
    }
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