    #include "juego.h"
    #include <iostream>
    #include "personaje.h"

    juego::juego() : personaje1(300, 250, 5, nullptr, {237, 249, 67, 237}) {
        SDL_Init(SDL_INIT_VIDEO);
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
        enemigos.push_back(personaje(450,50,1,nullptr, {227, 36, 22, 227}, 180));
        izquierda = false;
        derecha = false;
        arriba = false;
        abajo = false;
        vida=100;
        damagetime=0;
        ataque = false;
        ataquehitbox = {0, 0, 35, 35};
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
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &paredarriba);
        SDL_RenderFillRect(renderer, &paredabajo);      
        SDL_RenderFillRect(renderer, &paredizquierda);
        SDL_RenderFillRect(renderer, &paredderecha_up);
        SDL_RenderFillRect(renderer, &paredderecha_down); 
        personaje1.dibujar(renderer);
        
        for (int i = 0; i < enemigos.size(); i++) {
        enemigos[i].dibujar(renderer);}
        
        SDL_Rect barravida = {10, 10, vida * 2, 20};
        SDL_Rect fondoVida = {10, 10, 200, 20};
        SDL_SetRenderDrawColor(renderer, 8, 7, 7, 255);
        SDL_RenderFillRect(renderer, &fondoVida);
        SDL_SetRenderDrawColor(renderer, 43, 255, 0, 255);
        SDL_RenderFillRect(renderer, &barravida);

        if (ataque){
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            SDL_RenderFillRect(renderer, &ataquehitbox);
        }

        SDL_RenderPresent (renderer);
    }; 

    void juego::teclado() {
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT){
                caminando= false; 
                    }
                oldx= personaje1.getx();
                oldy= personaje1.gety();
            if (event.type== SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    izquierda= true;
                break;
                case SDLK_RIGHT:
                    derecha= true;
                break;
                case SDLK_UP:
                    arriba= true;
                break;
                case SDLK_DOWN:
                    abajo= true;
                break;
                case SDLK_SPACE:
                    ataque= true;
                break;
                }}
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
        if (damagetime > 0) {
            damagetime--;
        }
        if (izquierda) {
            personaje1.mover(-1, 0);
        }
        if (derecha) {
            personaje1.mover(1, 0);
        }
        if (arriba) {
            personaje1.mover(0, -1);
        }
        if (abajo) {
            personaje1.mover(0, 1);
        }

        SDL_Rect playerHitbox= personaje1.getHitbox();
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

        ataquehitbox.x = personaje1.getx() + 25;
        ataquehitbox.y = personaje1.gety() + 25;
        ataquehitbox.w = 35;
        ataquehitbox.h = 35;

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
        if (ataque && SDL_HasIntersection(&ataquehitbox, &enemyHitbox)) {
            int vidaenemiga = enemigos[i].getvida();
            vidaenemiga -= 20;
            enemigos[i].setvida(vidaenemiga);
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
            if (vida < 0) vida = 0;
            damagetime=60;
            std::cout << "Te han pateado :c\n Vida restante: " << vida << std::endl;
        }
        if (vida <= 0) {
            caminando= false;
        std::cout << "Te han desplumado.\n Fin del juego X.X" << std::endl;
    }  }} }

    juego::~juego(){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }