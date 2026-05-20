#include "mundos.h"
#include "objeto.h"
#include "personaje.h"

mundo::mundo(){
    mundoActual = 0;
    mundoInicializado= false;
    mundo_cambio = false;
    crearNivel();
}
void mundo:: cambiar_mundo(int neww){
    mundoActual = neww;
    mundoInicializado = true;
    mundo_cambio = true;

    if (mundoActual < 0 || mundoActual>= niveles.size());{
    return;}
}
std::vector<std::string> mundo::get_historia() {
    return niveles[mundoActual].historia;

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

void mundo::crearNivel (){
    niveles.clear();
    nivel n1;
    n1.paredes = {
    };
    n1.Fondo = {101,230,228,225};
    n1.oscuridad =0;
    n1.historia.push_back ("¿Dónde están todos?");
    n1.historia.push_back ("Seguramente están jugando :D");
    n1.historia.push_back ("Los encontraré");
    niveles.push_back(n1);

    nivel n2;
    n2.paredes = {
    };
    n2.Fondo = {48,171,169,225};
    n2.oscuridad=1;
    n2.historia.push_back ("Son demasiado buenos");
    n2.historia.push_back ("Sé que están por aquí");
    n2.historia.push_back ("Los encontraré");
    personaje comadreja (100,100,2,nullptr, {103, 60, 25, 103}, 50);
    n2.enemigos.push_back(comadreja);
    objeto flor(50,50);
    n2.objetos.push_back(flor);
    niveles.push_back(n2);
}

void mundo::aplicar_reglas(std::vector<personaje>& enemigos, std::vector<objeto>& objetos, int& oscuridad){
    enemigos.clear();
    objetos.clear();
    enemigos =
    niveles[mundoActual].enemigos;
    objetos =
    niveles[mundoActual].objetos;
    oscuridad =
    niveles[mundoActual].oscuridad;
}

//n4, ¿por que sigues caminando? Ellos ya no estan aqui
//n4Las almas que no aceptan el final vagaran eternamente
//n5 Aqui todos buscan algo que perdieron hace mucho
// n6 aun no estas listo
//n7 luchare hasta el final 
//n8 Ya puedes descansar