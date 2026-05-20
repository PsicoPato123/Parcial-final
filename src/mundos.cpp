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
    std::vector<SDL_Rect> base = {
    {0, 10, 800, 20},      
    {0, 590, 800, 20},    
    {0, 0, 20, 600},      
    {770, 0, 20, 300},    
    {770, 400, 20, 200},  
    };
    
    nivel n1;
    n1.paredes = base;
    n1.paredes.push_back ({300, 200, 20, 200});
    n1.Fondo = {101,230,228,225};
    n1.oscuridad =0;
    n1.historia.push_back ("Interactua con C ");
    n1.historia.push_back ("¿Donde están todos?");
    n1.historia.push_back ("Seguramente estan jugando :D");
    n1.historia.push_back ("Los voy a buscar");
    n1.historia.push_back ("Cuack!");
    niveles.push_back(n1);

    nivel n2;
    n2.paredes.push_back({200, 100, 200, 20});
    n2.paredes.push_back({200, 100, 20, 250});
    n2.Fondo = {48,171,169,225};
    n2.oscuridad=1;
    n2.historia.push_back ("Son demasiado buenos ");
    n2.historia.push_back ("Deben estar por aqui ");
    n2.historia.push_back ("Me da un buen feeling \n este lugar");
    n2.historia.push_back ("Los voy a encontrar");
    personaje comadreja1 (100,100,2,nullptr, {103, 60, 25, 103}, 50);
    n2.enemigos.push_back(comadreja1);
    objeto flor(50,50);
    n2.objetos.push_back(flor);
    niveles.push_back(n2);

    nivel n3;
    n3.paredes = base;
    n3.paredes.push_back ({400, 300, 20, 200});
    n3.paredes.push_back({150, 200, 200, 20});
    n3.Fondo = {35,144,93,200};
    n3.oscuridad=2;
    n3.historia.push_back ("Han de estar cerca ...\nEscucho algo");
    n3.historia.push_back ("Se empieza a oscurecer");
    n3.historia.push_back ("El ambiente comienza a ...\ndistorsionarse ...");
    n3.historia.push_back ("Eso es un... ¿Águila?");
    personaje aguila (245,175,4,nullptr, {103, 37, 25, 103}, 100);
    n3.enemigos.push_back(comadreja1);
    n3.enemigos.push_back(aguila);
    objeto roca(150,250);
    n3.objetos.push_back(flor);
    n3.objetos.push_back(roca);
    niveles.push_back(n3);

    nivel n4;
    n4.paredes.push_back({150, 150, 20, 300});
    n4.paredes.push_back({400, 150, 20, 300});
    n4.Fondo = {6,71,40,200};
    n4.oscuridad=3;
    n4.historia.push_back ("¿Por que sigues caminando?...");
    n4.historia.push_back ("Ellos no están aquí");
    n4.historia.push_back ("Aquellas luces que no aceptan, \nse mantendran intermitentes toda la eternidad");
    n4.historia.push_back ("Otro plato para mi mesa...\nHmmm");
    n4.historia.push_back ("¿Cuack?");
    personaje zorro (300,200,3,nullptr, {227, 115,22, 227}, 120);
    n4.enemigos.push_back(aguila);
    n4.enemigos.push_back(zorro);
    n4.objetos.push_back(flor);
    n4.objetos.push_back(roca);
    niveles.push_back(n4);

    nivel n5;
    n5.paredes = base;
    n5.paredes.push_back({20, 300, 350, 20});
    n5.paredes.push_back({450, 300, 330, 20});
    n5.Fondo = {3,48,26,170};
    n5.oscuridad=4;
    n5.historia.push_back ("Aquí todos buscan algo\n que perdieron hace mucho");
    n5.historia.push_back ("¿A que se refiere?");
    n5.historia.push_back ("Los enemigos lo saben...");
    n5.historia.push_back ("No he perdido a nadie... Solo ... Estan jugando");
    n5.historia.push_back ("¿Verdad?");
    personaje zorro_fantasma (300,200,3,nullptr, {70,83,77, 227}, 120);
    personaje fantasmas (450,50,1,nullptr, {70,83,77, 227}, 180);
    n5.enemigos.push_back(zorro_fantasma);
    n5.enemigos.push_back(fantasmas);
    objeto pluma(200,200);
    n5.objetos.push_back(flor);
    n5.objetos.push_back(roca);
    n5.objetos.push_back(pluma);
    niveles.push_back(n5);

    nivel n6;
    n6.paredes.push_back({200, 200, 20, 200});
    n6.paredes.push_back({200, 200, 400, 20});
    n6.paredes.push_back({580, 200, 20, 200});
    n6.Fondo = {6,17,60,170};
    n6.oscuridad=5;
    n6.historia.push_back ("Debí quedarme cerca");
    n6.historia.push_back ("Hace frío...");
    n6.historia.push_back ("No hay ni una voz, solo presencia");
    n6.historia.push_back ("Mamá: Aún no estas listo");
    n6.historia.push_back ("Necesito estar con ustedes");
    n6.enemigos.push_back(zorro_fantasma);
    n6.enemigos.push_back(fantasmas);
    n6.objetos.push_back(flor);
    n6.objetos.push_back(roca);
    n6.objetos.push_back(pluma);
    niveles.push_back(n6);

    nivel n7;
    n7.paredes.push_back({100, 100, 600, 20});
    n7.paredes.push_back({100, 100, 20, 400});
    n7.paredes.push_back({680, 100, 20, 400});
    n7.Fondo = {13,18,38,170};
    n7.oscuridad=6;
    n7.historia.push_back ("Voy a estar con ellos");
    n7.historia.push_back ("Lucharé hasta el final...");
    n7.historia.push_back ("Solo queda un lugar...");
    personaje fantasmas2 (450,50,3,nullptr, {70,83,77, 227}, 190);
    n7.enemigos.push_back(fantasmas2);
    objeto huevo (250,360);
    n7.objetos.push_back(flor);
    n7.objetos.push_back(roca);
    n7.objetos.push_back(pluma);
    n7.objetos.push_back(huevo);
    niveles.push_back(n7);

    nivel n8;
    n8.paredes.push_back({530, 150, 20, 300});
    n8.paredes.push_back({250, 150, 300, 20});
    n8.paredes.push_back({250, 150, 20, 300});
    n8.paredes.push_back({250, 430, 300, 20});
    n8.Fondo = {22,25,34,170};
    n8.oscuridad=7;
    n8.historia.push_back ("...: ¿Sigues consciente?");
    n8.historia.push_back ("No pude hacer bien mi trabajo, patito...");
    n8.historia.push_back ("Ven aquí...");
    n8.historia.push_back ("¡SON ELLOS!");
    personaje perro (450,50,3,nullptr, {70,83,77, 227}, 190);
    personaje humano (500,450, 3,nullptr, {255,202,173,255},350);
    n8.enemigos.push_back(perro);
    n8.enemigos.push_back(humano);
    n8.objetos.push_back(flor);
    n8.objetos.push_back(roca);
    n8.objetos.push_back(pluma);
    n8.objetos.push_back(huevo);
    niveles.push_back(n8);

    nivel n9;
    n9.paredes = base;
    n9.Fondo = {22,25,34,170};
    n9.oscuridad=7;
    n9.historia.push_back ("Ya lo entendí...");
    n9.historia.push_back ("Debía decir adios...");
    n9.historia.push_back ("Ma: Ya puedes descansar...");
    n9.historia.push_back ("Ma: Ven con nosotros...");
    niveles.push_back(n9);
}
SDL_Color mundo::getFondo(){
return niveles[mundoActual].Fondo;
}
std::vector<SDL_Rect> mundo::get_pared() {
    return niveles[mundoActual].paredes;
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