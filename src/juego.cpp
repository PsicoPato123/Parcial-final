    #include "juego.h"
    #include <iostream>
    #include "personaje.h"
    #include "mundos.h"
    #include "objeto.h"

    juego::juego() : personaje1(300, 250, 5, nullptr, {237, 249, 67, 237}) {
        SDL_Init(SDL_INIT_VIDEO);
        TTF_Init();
        fuente = TTF_OpenFont ("04B_11_.ttf", 20);
        if (!fuente){
            std::cout<<"No hay una fuente cargada";
        }
        window = SDL_CreateWindow("Juego SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        paredarriba = {0, 0, 800, 20};
        paredabajo = {0, 580, 800, 20};
        paredizquierda = {0, 0, 20, 600};
        paredderecha_up = {780, 400, 20, 200};
        paredderecha_down = {780, 0, 20, 200};
        caminando = true;

        enemigos.push_back(personaje(100,100,2,nullptr, {103, 60, 25, 103}, 50));
        enemigos.push_back(personaje(245,175,4,nullptr, {103, 37, 25, 103}, 100));
        enemigos.push_back(personaje(300,200,3,nullptr, {227, 115,22, 227}, 120));
        enemigos.push_back(personaje(450,50,1,nullptr, {70,83,77, 227}, 180));
        enemigos.push_back(personaje(500,450, 3,nullptr, {255,202,173,255},350));
        izquierda = false;
        derecha = false;
        arriba = false;
        abajo = false;
        vida=100;
        damagetime=0;
        ataque= false;
        ataquehitbox= {0, 0, 35, 35};
        cooldown=0;
        direccionx=1;
        direcciony=0;
        lvlluz=0;
        estado = vivo; 

        conObjeto=false;
        objeto_ctual = 0;
        objetos.push_back(objeto(200,200));
        objetos.push_back(objeto(150,250));
        objetos.push_back(objeto(250,360));
        objetos.push_back(objeto(50,50));
    }
    void juego ::inicializar() {
        SDL_RenderPresent(renderer);
    }
    void juego::loop() {
        while (caminando){
            teclado();
            actualizar();
            mostrar();
            SDL_Delay(16);
    }  }

    void juego::mostrar(){
        SDL_Color fondo = mundo.getFondo();
        SDL_SetRenderDrawColor(
            renderer,
            fondo.r,fondo.g,fondo.b,fondo.a
        );
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &paredarriba);
        SDL_RenderFillRect(renderer, &paredabajo);      
        SDL_RenderFillRect(renderer, &paredizquierda);
        SDL_RenderFillRect(renderer, &paredderecha_up);
        SDL_RenderFillRect(renderer, &paredderecha_down); 
        personaje1.dibujar(renderer);
        
        for (int i = 0; i < enemigos.size(); i++) {
        enemigos[i].dibujar(renderer);
        
        SDL_Rect barra_vida_enemigo = {
            enemigos[i].getx(),
            enemigos[i].gety() - 10,
            50 * enemigos[i].getvida() / 100,
            5
        };
        SDL_Rect vida_enemigo = {
            enemigos[i].getx(),
            enemigos[i].gety() - 10,
            enemigos[i].getvida() /2, 5 
        };

        SDL_SetRenderDrawColor(renderer, 8, 7, 7, 255);
        SDL_RenderFillRect(renderer, &vida_enemigo);
        SDL_SetRenderDrawColor(renderer, 43, 255, 0, 255);
        SDL_RenderFillRect(renderer, &barra_vida_enemigo);} 

        if (ataque){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &ataquehitbox);
        }

        if(lvlluz >=1){ 
            SDL_SetRenderDrawColor(renderer, 25, 25, 0, 255);
        }
        if (lvlluz >=3){
            SDL_SetRenderDrawColor(renderer, 5, 5, 0, 255);
        }
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, lvlluz * 40);
        SDL_Rect oscuridad = {0, 0, 750, 600};
        SDL_RenderFillRect(renderer, &oscuridad);

        if (dialogo) {
            SDL_Color blanco = {255,255,255};
            std::string visible =
            dialogo_ctual[linea_dialogo].substr(0, chars_mostrados);
            SDL_Surface* textoS = TTF_RenderUTF8_Blended(
                fuente,
                visible.c_str(), blanco
            );
            SDL_Texture* textot =
            SDL_CreateTextureFromSurface(
                renderer, textoS
            );
            SDL_Rect textoRect = {
                80,
                400,
                textoS->w,
                textoS->h
            };
            SDL_Rect cajita = {50, 370, 550, 150};
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
            SDL_RenderFillRect(renderer, &cajita);
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderDrawRect(renderer, &cajita);

            SDL_RenderCopy(
                renderer,
                textot,
                NULL,
                &textoRect
            );
            SDL_FreeSurface(textoS);
            SDL_DestroyTexture(textot);
        }        
        for (int i = 0; i < objetos.size(); i++) {
            if (!objetos[i].en_mano()) {
                objetos[i].dibujar(renderer);
            } }
        for (int i = 0; i < proyectiles.size(); i++) {
            proyectiles[i].dibujar(renderer);
        }

        SDL_RenderPresent (renderer);
    }; 

    void juego::teclado() {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {            
            oldx= personaje1.getx();
            oldy= personaje1.gety();
            if(event.type == SDL_QUIT){
                caminando= false;  }

            if (event.type== SDL_KEYDOWN) {
                if (event.key.keysym. sym == SDLK_SPACE && dialogo){
                    linea_dialogo ++;
                    if (linea_dialogo >= dialogo_ctual.size()) {
                    dialogo = false;
                }else{
                    chars_mostrados = 0;
                    tiempo_escribiendo = 0;
                }
                continue; }
            if (!dialogo){
                switch (event.key.keysym.sym){
                    case SDLK_LEFT: izquierda = true; 
                    break;
                    case SDLK_RIGHT: derecha = true; 
                    break;
                    case SDLK_UP: arriba = true; 
                    break;
                    case SDLK_DOWN: abajo = true; 
                    break;
                    case SDLK_SPACE: ataque = true;              
            if (conObjeto){
                objeto nuevo(
                    personaje1.getx(),
                    personaje1.gety()
                );
                nuevo.lanzar(
                    direccionx,
                    direcciony
                );
                proyectiles.push_back(nuevo);
                conObjeto = false;}
                    break; }
            } }

            if (event.type== SDL_KEYUP){
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    izquierda= false;
                break;
                case SDLK_RIGHT:        
                    derecha= false;
                break;
                case SDLK_UP:
                    arriba= false;
                break;
                case SDLK_DOWN:
                    abajo= false;
                break;    
                case SDLK_SPACE:
                    ataque= false;
                break;
            }; 
    }   }
    }

    void juego::actualizar() {
        if (dialogo){
            tiempo_escribiendo ++;

            if (tiempo_escribiendo >= delay_escritura){
            tiempo_escribiendo = 0;
            
            if (chars_mostrados < dialogo_ctual[linea_dialogo].size()){
                chars_mostrados++;
            } }
        };
        if (mundo.get_mundo_ctual() ==1){
        if (damagetime > 0) {
            damagetime--;
        }}
         if (cooldown > 0) {
            cooldown--;}  
    
        if (izquierda) {
            personaje1.mover(-1, 0);
            direccionx= -1;
            direcciony= 0;
        }
        if (derecha) {
            personaje1.mover(1, 0);
            direccionx= 1;
            direcciony= 0;
        }
        if (arriba) {
            personaje1.mover(0, -1);
            direccionx= 0;
            direcciony= -1;
        }
        if (abajo) {
            personaje1.mover(0, 1);
            direccionx= 0;
            direcciony= 1;
        }  
        SDL_Rect playerHitbox= personaje1.getHitbox();
        
        for (int i = 0; i < objetos.size(); i++) {
            if (!objetos[i].en_mano()) {
            SDL_Rect objetoHitbox = objetos[i].getHitbox();
            if (SDL_HasIntersection(&playerHitbox, &objetoHitbox)) {
            objetos[i].recoger();
            conObjeto = true;
            objeto_ctual = i;
            std::cout << "Objeto en el ala\n";
        } }
}
        bool colision= false;
        if (SDL_HasIntersection(&playerHitbox, &paredarriba)) { 
            colision= true;
            std::cout << "No puedes pasar la pared" << std::endl;
        }
        if (SDL_HasIntersection(&playerHitbox, &paredabajo)) {
            colision= true;
            std::cout << "No puedes pasar la pared" << std::endl;
        }
        if (SDL_HasIntersection(&playerHitbox, &paredderecha_up) || SDL_HasIntersection(&playerHitbox, &paredderecha_down)) {
            colision= true;
            std::cout << "No puedes pasar la pared" << std::endl;
        }
        if (SDL_HasIntersection(&playerHitbox, &paredizquierda)) {
            colision= true;
            std::cout << "No puedes pasar la pared" << std::endl;
        }
        if (colision) {
            personaje1.setx(oldx);
            personaje1.sety(oldy);
        }

        ataquehitbox.x = personaje1.getx() + (direccionx * 40);
        ataquehitbox.y = personaje1.gety() + (direcciony * 40);
        ataquehitbox.w = 35;
        ataquehitbox.h = 35;

        for(int i=0; i< proyectiles.size(); i++ ){
            proyectiles[i].cambio();
            if (!proyectiles[i].lanzando()){
                proyectiles.erase(
                    proyectiles.begin() +i);
            }}

        for (int i = 0; i < enemigos.size(); i++) {
            oldenemx= enemigos[i].getx();
            oldenemy= enemigos[i].gety();   

            if (enemigos[i].getx() < personaje1.getx()) {
                enemigos[i].mover(1, 0);
            }
            if (enemigos[i].getx() > personaje1.getx()) {
            enemigos[i].mover(-1, 0);
            }
            if (enemigos[i].gety() < personaje1.gety()){
                enemigos[i].mover(0, 1);
            }
            if (enemigos[i].gety() > personaje1.gety()){
                enemigos[i].mover(0, -1);}

        SDL_Rect enemyHitbox= enemigos[i].getHitbox();
        for (int j = 0; j < proyectiles.size(); j++) {
        SDL_Rect proyectilHitbox =
        proyectiles[j].getHitbox();

        if (SDL_HasIntersection(
            &enemyHitbox,
            &proyectilHitbox
        )) {
            enemigos[i].setvida(
                enemigos[i].getvida() - 25
            );
            proyectiles.erase(
                proyectiles.begin() + j
            );
            break;
        }}
        if (ataque && SDL_HasIntersection(&ataquehitbox, &enemyHitbox)&& ataque && cooldown == 0) {
            int vidaenemiga = enemigos[i].getvida();
            vidaenemiga -= 20;
            enemigos[i].setvida(vidaenemiga);
            enemigos[i].mover(direccionx * 20, direcciony * 20);
            cooldown = 30; 
        }
        if (enemigos[i].getvida() <= 0) {
            enemigos.erase(enemigos.begin() + i);
            i--;
            continue;
        }

        bool colisionenemiga= false;
        if (SDL_HasIntersection(&enemyHitbox, &paredarriba)) {
            colisionenemiga= true;
        }
        if (SDL_HasIntersection(&enemyHitbox, &paredabajo)) {
            colisionenemiga= true;
        }
        if (SDL_HasIntersection(&enemyHitbox, &paredderecha_up) || SDL_HasIntersection(&enemyHitbox, &paredderecha_down)) {
            colisionenemiga= true;
        }
        if (SDL_HasIntersection(&enemyHitbox, &paredizquierda)) {
            colisionenemiga= true;
        }
        if (colisionenemiga) {
            enemigos[i].setx(oldenemx);
            enemigos[i].sety(oldenemy); }
        if (SDL_HasIntersection(&playerHitbox, &enemyHitbox)) {
        if (damagetime ==0){
            vida -= 10;

        if (vida <= 0 && estado == vivo) {
            vida=0;
            damagetime=60;
            estado = muerto;
            std::cout << "Te han pateado :c\nLuz restante: " << vida << std::endl;
            vuelta_ala_tierra();
        }
        if (estado == muerto){
            return;
        }   
    }} }}

    void juego::vuelta_ala_tierra() {
        memorias.push_back(lvlluz);
        if (mundo.get_mundo_ctual() <7) {
        mundo.cambiar_mundo(mundo.get_mundo_ctual() + 1);}
        
        dialogo_ctual= mundo.get_historia();
        linea_dialogo=0;
        dialogo=true;
        
        enemigos.clear();
        mundo.aplicar_reglas(enemigos, objetos, lvlluz);
        if(memorias.size() == 3) {
        std::cout<<"Siento que no debería estar aquí... " << std::endl;
        }
        if (memorias.size()== 2) {
        std::cout<<"Algo se siente diferente... " << std::endl;
        }
        if (memorias.size() == 1) {
        std::cout<<"La luz se aleja... " << std::endl;
        }

        personaje1.setx(300);
        personaje1.sety(250);
        vida = 100;
        }

     void juego::limpiar() {
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
    juego::~juego(){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }