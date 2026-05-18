    #include "juego.h"
    #include <iostream>
    #include "personaje.h"

    juego::juego() : personaje1(300, 250, 5, nullptr), enemigo1(00, 250, 5, nullptr) {
        SDL_Init(SDL_INIT_VIDEO);
        window = SDL_CreateWindow("Juego SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        paredarriba = {0, 0, 800, 20};
        paredabajo = {0, 580, 800, 20};
        paredizquierda = {0, 0, 20, 600};
        paredderecha_up = {780, 400, 20, 200};
        paredderecha_down = {780, 0, 20, 200};
        caminando = true;
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
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); 
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(renderer, &paredarriba);
        SDL_RenderFillRect(renderer, &paredabajo);      
        SDL_RenderFillRect(renderer, &paredizquierda);
        SDL_RenderFillRect(renderer, &paredderecha_up);
        SDL_RenderFillRect(renderer, &paredderecha_down);

        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255); 
        personaje1.dibujar(renderer);
        SDL_SetRenderDrawColor(renderer, 149, 159, 233, 255);
        enemigo1.dibujar(renderer);
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

        if (enemigo1.getx() < personaje1.getx()) {
            enemigo1.mover(1, 0);
        }
        if (enemigo1.getx() > personaje1.getx()) {
            enemigo1.mover(-1, 0);
        }
        if (enemigo1.gety() < personaje1.gety()){
            enemigo1.mover(0, 1);
        }
        if (enemigo1.gety() > personaje1.gety()){
            enemigo1.mover(0, -1);
        }
    }

    juego::~juego(){
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }