    #include "juego.h"
    #include <iostream>
    #include "personaje.h"
    #include "mundos.h"
    #include "objeto.h"

    juego::juego() : personaje1(170, 250, 5, nullptr, {237, 249, 67, 237}) {
        SDL_Init(SDL_INIT_VIDEO);
        TTF_Init();
        fuente = TTF_OpenFont ("../letras.TTF", 18);
        if (!fuente){
            std::cout << TTF_GetError() << std::endl;
            std::cout<<"No hay una fuente cargada";
        }
        inicio = true;
        window = SDL_CreateWindow("Juego SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        paredes_ctual = mundo_mapa.get_pared();
        caminando = true;
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
        linea_dialogo = 0;
        chars_mostrados = 0;
        tiempo_escribiendo = 0;
        delay_escritura = 2;
        dialogo = true;
        
        mundo_mapa.cambiar_mundo(0);
        mundo_mapa.aplicar_reglas(enemigos,objetos,lvlluz);
        con_enemigos = !enemigos.empty();
        dialogo_ctual= mundo_mapa.get_historia();
        dialogo= true;

    }

    void juego ::inicializar() {
        SDL_RenderPresent(renderer);
    }
    
    void juego::mostrar_inicio(){

        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_Color blanco = {255,255,255};
        SDL_Surface* tituloS =
        TTF_RenderUTF8_Blended(
            fuente,
            "Duckling Limbo", blanco);
        if (!tituloS){
        std::cout << TTF_GetError() << std::endl;
        return;
    }
        SDL_Texture* tituloT =
        SDL_CreateTextureFromSurface(
            renderer, tituloS);
         SDL_Rect tituloRect = {
            180, 180,
            tituloS->w,tituloS->h
        };
        SDL_RenderCopy(
            renderer, tituloT,
            NULL, &tituloRect
        );

        SDL_Surface* startS =
        TTF_RenderUTF8_Blended(
            fuente,
            "Presiona ENTER", blanco);
        if (!startS) {
            std::cout << TTF_GetError() << std::endl;
        return;
        }
        SDL_Texture* startT =
        SDL_CreateTextureFromSurface(
            renderer,  startS);
        SDL_Rect startRect = {
            230,300,
            startS->w,startS->h};
        SDL_RenderCopy(
            renderer,startT,
            NULL,&startRect);
        SDL_RenderPresent(renderer);
        SDL_FreeSurface(tituloS);
        SDL_DestroyTexture(tituloT);
        SDL_FreeSurface(startS);
        SDL_DestroyTexture(startT);
    }
    
    void juego::loop() {
        while (caminando){
            teclado();
            if (inicio){
                mostrar_inicio();
            }else{
                actualizar();
                mostrar();
            }
            SDL_Delay (15);
    }  }

    void juego::mostrar(){
        SDL_Color fondo = mundo_mapa.getFondo();
        SDL_SetRenderDrawColor(
            renderer,
            fondo.r,fondo.g,fondo.b,fondo.a
        );
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect phb = personaje1.getHitbox();
        SDL_RenderDrawRect(renderer, &phb);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            for (int i = 0; i < paredes_ctual.size(); i++) {
            SDL_RenderFillRect(renderer, &paredes_ctual[i]);
            }
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
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, lvlluz * 40);
        SDL_Rect oscuridad = {0, 0, 750, 600};
        SDL_RenderFillRect(renderer, &oscuridad);

        if (dialogo && linea_dialogo < dialogo_ctual.size()) {
        SDL_Rect cajita = {50, 370, 550, 150};
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 200);
        SDL_RenderFillRect(renderer, &cajita);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderDrawRect(renderer, &cajita);

        if (chars_mostrados > 0) {
            SDL_Color blanco = {255, 255, 255};
            if (dialogo_ctual.empty()) {
                dialogo = false;
                return;
                }
            std::string visible = dialogo_ctual[linea_dialogo].substr(0, chars_mostrados);
            SDL_Surface* textoS = TTF_RenderUTF8_Blended(fuente, visible.c_str(), blanco);
            if (textoS) {
                SDL_Texture* textot = SDL_CreateTextureFromSurface(renderer, textoS);
                SDL_Rect textoRect = {80, 400, textoS->w, textoS->h};
                SDL_RenderCopy(renderer, textot, NULL, &textoRect);
                SDL_FreeSurface(textoS);
                SDL_DestroyTexture(textot);
            }
        }
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
            if (event.type == SDL_QUIT) {
            caminando = false;
        }
            if(event.type==SDL_KEYDOWN){
                if (inicio && event.key.keysym.sym == SDLK_RETURN) {
                inicio = false;
                continue;
            }
            if (event.key.keysym.sym == SDLK_c && dialogo) {
                linea_dialogo++;
                if (linea_dialogo >= dialogo_ctual.size()) {
                    dialogo = false;}
                continue;
            }
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:   
                izquierda = true;
                break;
                case SDLK_RIGHT: 
                derecha = true; 
                break;
                case SDLK_UP:    
                arriba = true; 
                break;
                case SDLK_DOWN:  
                abajo = true; 
                break;
                case SDLK_e:
                    ataque = true;
                    break;
            }
        }
        if (event.type == SDL_KEYUP) {
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:  
                izquierda = false; 
                break;
                case SDLK_RIGHT: 
                derecha = false; 
                break;
                case SDLK_UP:    
                arriba = false; 
                break;
                case SDLK_DOWN:  
                abajo = false; 
                break;
                case SDLK_e:     
                ataque = false;
                if (conObjeto) {
                    objeto nuevo(personaje1.getx(), personaje1.gety());
                    nuevo.lanzar(direccionx, direcciony);
                    proyectiles.push_back(nuevo);
                    conObjeto = false;
                }
                 break;}
        } }   } 

    void juego::actualizar() {

        if (dialogo && !dialogo_ctual.empty() && linea_dialogo < dialogo_ctual.size()){
            tiempo_escribiendo++;
            if (tiempo_escribiendo >= delay_escritura){
            tiempo_escribiendo = 0;
        if (chars_mostrados < dialogo_ctual[linea_dialogo].size()){
            chars_mostrados++;
        }
        } }
        if (damagetime > 0) {
            damagetime--;
        }
         if (cooldown > 0) {
            cooldown--;}  
         int oldx = personaje1.getx();
        int oldy = personaje1.gety();
        int dx = 0;
        int dy = 0;

        if (izquierda) dx -= personaje1.getvelocidad();
        if (derecha)  dx += personaje1.getvelocidad();
        if (arriba)   dy -= personaje1.getvelocidad();
        if (abajo)    dy += personaje1.getvelocidad();
        personaje1.mover(dx, dy);
        SDL_Rect playerHitbox = personaje1.getHitbox();
        bool colision = false;
        for (int i = 0; i < paredes_ctual.size(); i++) {
            if (SDL_HasIntersection(&playerHitbox, &paredes_ctual[i])) {
                colision = true;
                break;
            } }
        if (colision) {
            personaje1.setx(oldx);
            personaje1.sety(oldy);
        }
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
        for (int i = 0; i < paredes_ctual.size(); i++) {
            if (SDL_HasIntersection(&playerHitbox, &paredes_ctual[i])) {
            colision = true;
        break;
    }
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
            i --; }}

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
            for (int i = 0; i < paredes_ctual.size(); i++) {
                if (SDL_HasIntersection(&enemyHitbox, &paredes_ctual[i])) {
                colisionenemiga = true;
        break;
    } }
        if (colisionenemiga) {
            enemigos[i].setx(oldenemx);
            enemigos[i].sety(oldenemy); }
        if (SDL_HasIntersection(&playerHitbox, &enemyHitbox)) {
        if (damagetime ==0){
            vida -= 10;
            damagetime =60; }

        if (vida <= 0 && estado == vivo) {
            vida=0;
            damagetime=60;
            estado = muerto;
            std::cout << "Te han pateado :c\nLuz restante: " << vida << std::endl;
            vuelta_ala_tierra();
        }}}
        if (estado == muerto){
            return;
        } 
        if (enemigos.empty() && !dialogo) {
        bool puede_avanzar = con_enemigos || mundo_mapa.get_mundo_ctual() == 0;
        if (puede_avanzar) {
        if (mundo_mapa.get_mundo_ctual() < 8) {
            std::cout << "mundo: " << mundo_mapa.get_mundo_ctual() 
              << " nivel_tenia_enemigos: " << con_enemigos
              << " dialogo: " << dialogo << std::endl;
            mundo_mapa.cambiar_mundo(mundo_mapa.get_mundo_ctual() + 1);
            dialogo_ctual = mundo_mapa.get_historia();
            linea_dialogo = 0;
            chars_mostrados = 0;
            dialogo = true;
            mundo_mapa.aplicar_reglas(enemigos, objetos, lvlluz);
            con_enemigos = !enemigos.empty();
            paredes_ctual = mundo_mapa.get_pared();
            personaje1.setx(170);
            personaje1.sety(250);
            vida = 100;
            estado = vivo;}else{
            caminando =false;}
    }} }

    void juego::vuelta_ala_tierra() {
        memorias.push_back(lvlluz);
        SDL_ShowSimpleMessageBox(
        SDL_MESSAGEBOX_INFORMATION,
        "Duckling Limbo",
        "La luz se apaga... pero aun puedes intentarlo",
        window
    );
        enemigos.clear();
        mundo_mapa.aplicar_reglas(enemigos, objetos, lvlluz);
        con_enemigos = !enemigos.empty();
        paredes_ctual = mundo_mapa.get_pared();
        dialogo_ctual = mundo_mapa.get_historia();
        linea_dialogo = 0;
        chars_mostrados = 0;
        dialogo = true;
        personaje1.setx(170);
        personaje1.sety(250);
        vida = 100;
        estado = vivo;

        if(memorias.size() == 3) {
        std::cout<<"Siento que no debería estar aquí... " << std::endl;
        }
        if (memorias.size()== 2) {
        std::cout<<"Algo se siente diferente... " << std::endl;
        }
        if (memorias.size() == 1) {
        std::cout<<"La luz se aleja... " << std::endl;
        }
            izquierda = false;
            derecha = false;
            arriba = false;
            abajo = false;
            ataque = false;
    }
    juego::~juego(){
        if (fuente){
        TTF_CloseFont(fuente);
    }
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        TTF_Quit();
        SDL_Quit();
    }