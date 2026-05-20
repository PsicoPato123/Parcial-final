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
    if (neww < 0 || neww >= niveles.size()){
        return; 
    }
    mundoActual = neww;
    mundoInicializado = true;
    mundo_cambio = true;
}

std::vector<std::string> mundo::get_historia() {
return niveles[mundoActual].historia;
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
    n1.historia.push_back ("Cuack!");
    niveles.push_back(n1);

    nivel n2;
    n2.paredes = {
    };
    n2.Fondo = {48,171,169,225};
    n2.oscuridad=1;
    n2.historia.push_back ("Son demasiado buenos");
    n2.historia.push_back ("Sé que están por aquí");
    n2.historia.push_back ("Me da una buena sensación este lugar");
    n2.historia.push_back ("Los encontraré");
    personaje comadreja (100,100,2,nullptr, {103, 60, 25, 103}, 50);
    n2.enemigos.push_back(comadreja);
    objeto flor(50,50);
    n2.objetos.push_back(flor);
    niveles.push_back(n2);

    nivel n3;
    n3.paredes = {
    };
    n3.Fondo = {35,144,93,200};
    n3.oscuridad=2;
    n3.historia.push_back ("Están cerca ... Escucho algo");
    n3.historia.push_back ("Se empieza a oscurecer");
    n3.historia.push_back ("El ambiente comienza a distorsionarse ...");
    n3.historia.push_back ("Eso es un... ¿Águila?");
    personaje comadreja (100,100,2,nullptr, {103, 60, 25, 103}, 50);
    personaje aguila (245,175,4,nullptr, {103, 37, 25, 103}, 100);
    n3.enemigos.push_back(comadreja);
    n3.enemigos.push_back(aguila);
    objeto flor(50,50);
    objeto roca(150,250);
    n3.objetos.push_back(flor);
    n3.objetos.push_back(roca);
    niveles.push_back(n3);

    nivel n4;
    n4.paredes = {
    };
    n4.Fondo = {6,71,40,200};
    n4.oscuridad=3;
    n4.historia.push_back ("¿Por qué sigues caminando?...");
    n4.historia.push_back ("Ellos no están aquí");
    n4.historia.push_back ("Aquellas luces que no aceptan, vivirán intermitentes toda la eternidad");
    n4.historia.push_back ("Otro plato para mi mesa...Hmmm");
    n4.historia.push_back ("¿Cuack?");
    personaje aguila (245,175,4,nullptr, {103, 37, 25, 103}, 100);
    personaje zorro (300,200,3,nullptr, {227, 115,22, 227}, 120);
    n4.enemigos.push_back(aguila);
    n4.enemigos.push_back(zorro);
    objeto flor(50,50);
    objeto roca(150,250);
    n4.objetos.push_back(flor);
    n4.objetos.push_back(roca);
    niveles.push_back(n4);

    nivel n5;
    n5.paredes = {
    };
    n5.Fondo = {3,48,26,170};
    n5.oscuridad=4;
    n5.historia.push_back ("Aquí todos buscan algo que perdieron hace mucho");
    n5.historia.push_back ("¿A qué se refiere?");
    n5.historia.push_back ("Los enemigos lo saben...");
    n5.historia.push_back ("No perdí a nadie... Sólo ... Estan jugando");
    n5.historia.push_back ("¿Verdad?");
    personaje zorro_fantasma (300,200,3,nullptr, {70,83,77, 227}, 120);
    personaje fantasmas (450,50,1,nullptr, {70,83,77, 227}, 180);
    n5.enemigos.push_back(zorro_fantasma);
    n5.enemigos.push_back(fantasmas);
    objeto flor(50,50);
    objeto roca(150,250);
    objeto pluma(200,200);
    n5.objetos.push_back(flor);
    n5.objetos.push_back(roca);
    n5.objetos.push_back(pluma);
    niveles.push_back(n5);

    nivel n6;
    n6.paredes = {
    };
    n6.Fondo = {6,17,60,170};
    n6.oscuridad=5;
    n6.historia.push_back ("Debí quedarme cerca");
    n6.historia.push_back ("Hace frío...");
    n6.historia.push_back ("No hay ni una voz, solo presencia");
    n6.historia.push_back ("Mamá: Aún no estás listo");
    n6.historia.push_back ("Necesito estar con ustedes");
    personaje zorro_fantasma (300,200,4,nullptr, {70,83,77, 227}, 120);
    personaje fantasmas (450,50,3,nullptr, {70,83,77, 227}, 190);
    n6.enemigos.push_back(zorro_fantasma);
    n6.enemigos.push_back(fantasmas);
    objeto flor(50,50);
    objeto roca(150,250);
    objeto pluma(200,200);
    n6.objetos.push_back(flor);
    n6.objetos.push_back(roca);
    n6.objetos.push_back(pluma);
    niveles.push_back(n6);

    nivel n7;
    n7.paredes = {
    };
    n7.Fondo = {13,18,38,170};
    n7.oscuridad=6;
    n7.historia.push_back ("Estaré con ellos");
    n7.historia.push_back ("Lucharé hasta el final...");
    n7.historia.push_back ("Sólo queda un lugar...");
    personaje fantasmas (450,50,3,nullptr, {70,83,77, 227}, 190);
    n7.enemigos.push_back(fantasmas);
    objeto flor(50,50);
    objeto roca(150,250);
    objeto pluma(200,200);
    objeto huevo (250,360);
    n7.objetos.push_back(flor);
    n7.objetos.push_back(roca);
    n7.objetos.push_back(pluma);
    n7.objetos.push_back(huevo);
    niveles.push_back(n7);

    nivel n8;
    n8.paredes = {
    };
    n8.Fondo = {22,25,34,170};
    n8.oscuridad=7;
    n8.historia.push_back ("...: ¿Sigues consciente?");
    n8.historia.push_back ("No logré hacer bien mi trabajo, patito...");
    n8.historia.push_back ("Ven aquí...");
    n8.historia.push_back ("¡SON ELLOS!");
    personaje perro (450,50,3,nullptr, {70,83,77, 227}, 190);
    personaje humano (500,450, 3,nullptr, {255,202,173,255},350);
    n8.enemigos.push_back(perro);
    n8.enemigos.push_back(humano);
    objeto flor(50,50);
    objeto roca(150,250);
    objeto pluma(200,200);
    objeto huevo (250,360);
    n8.objetos.push_back(flor);
    n8.objetos.push_back(roca);
    n8.objetos.push_back(pluma);
    n8.objetos.push_back(huevo);
    niveles.push_back(n8);

    nivel n9;
    n9.paredes = {
    };
    n9.Fondo = {22,25,34,170};
    n9.oscuridad=7;
    n9.historia.push_back ("Ya lo entendí...");
    n9.historia.push_back ("Debía decir adios...");
    n9.historia.push_back ("Mamá: Ya puedes descansar...");
    n9.historia.push_back ("Mamá: Ven con nosotros...");
    niveles.push_back(n9);
}
SDL_Color mundo::getFondo(){
return niveles[mundoActual].Fondo;
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