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
        enemigos.push_back(personaje(100,100,2,nullptr, {103, 60, 25, 103}));
        enemigos.push_back(personaje(245,175,4,nullptr, {103, 37, 25, 103}));
        enemigos.push_back(personaje(300,200,3,nullptr, {227, 115,22, 227}));
        enemigos.push_back(personaje(450,50,1,nullptr, {227, 36, 22, 227}));
        izquierda = false;
        derecha = false;
        arriba = false;
        abajo = false;
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

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &paredarriba);
        SDL_RenderFillRect(renderer, &paredabajo);      
        SDL_RenderFillRect(renderer, &paredizquierda);
        SDL_RenderFillRect(renderer, &paredderecha_up);
        SDL_RenderFillRect(renderer, &paredderecha_down); 
        personaje1.dibujar(renderer);
        for (int i = 0; i < enemigos.size(); i++) {
            enemigos[i].dibujar(renderer);
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
            }; 
    }   }
    }

    void juego::actualizar() {
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
        if (colision) {
            personaje1.setx(oldx);
            personaje1.sety(oldy);
        }

        for (int i = 0; i < enemigos.size(); i++) {
            personaje& enemigo = enemigos[i];
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
    if (SDL_HasIntersection(&playerHitbox, &enemyHitbox)) {
        caminando= false;
        std::cout << "Te han desplumado.\n Fin del juego X.X" << std::endl;
    }  }}

    juego::~juego(){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }