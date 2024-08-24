#include <SFML/Graphics.hpp>
#include "Boton.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
using namespace sf;

int indexTutorial = 1;

void crearMatrizDamas(int damas[8][8]){
    int tablero[8][8] = {
                {-1,1,-1,1,-1,1,-1,1},
                {1,-1,1,-1,1,-1,1,-1},
                {-1,0,-1,0,-1,0,-1,0},
                {0,-1,0,-1,0,-1,0,-1},
                {-1,0,-1,0,-1,0,-1,0},
                {0,-1,0,-1,0,-1,0,-1},
                {-1,2,-1,2,-1,2,-1,2},
                {2,-1,2,-1,2,-1,2,-1},
                };
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            damas[i][j] = tablero[i][j];
        }
    }
}

void cambiarColorBoton(Boton &boton, RenderWindow &ventana) {
    if (boton.isMouseOver(ventana)) {
        boton.setBackColor(Color::Black);
    } else {
        boton.setBackColor(Color(255, 255, 255, 0));
    }
}

void jugarDamas(Font &font){

    RenderWindow Damas(VideoMode(1280,720),"Damas");

    int tablero[8][8];
    crearMatrizDamas(tablero);

    RectangleShape fondo;
    Texture textura, textura1, textura2, textura3, textura4;
    fondo.setSize(Vector2f(1280,720));
    textura.loadFromFile("Texturas/tablero_damas.png");
    textura1.loadFromFile("Texturas/damaBaseBlanca.png");
    textura2.loadFromFile("Texturas/damaBaseNegra.png");
    textura3.loadFromFile("Texturas/damaBlanca.png");
    textura4.loadFromFile("Texturas/damaNegra.png");
    fondo.setTexture(&textura);

    Sprite fichaBlanca, fichaNegra;
    fichaBlanca.setTexture(textura1);
    fichaNegra.setTexture(textura2);

    CircleShape movimiento(15.0f); // Tamaño del círculo para mostrar los movimientos
    movimiento.setFillColor(Color(0, 255, 0, 100)); // Color verde transparente

    const float offsetX = 280.0f;
    const float offsetY = 0.0f;
    const float tamanoCasilla = 90.0f;

    bool fichaSeleccionada = false;
    int fichaSeleccionadaX = -1;
    int fichaSeleccionadaY = -1;

    while(Damas.isOpen()){
        Event aevent;
        while(Damas.pollEvent(aevent)){
            switch(aevent.type){
                case Event::Closed:
                    Damas.close();
                    break;

                case Event::MouseMoved:

                    break;

                case Event::MouseButtonPressed:{

                    if (aevent.mouseButton.button == Mouse::Left){
                        float x = Mouse::getPosition(Damas).x;
                        float y = Mouse::getPosition(Damas).y;
                        cout << x << endl;
                        cout << y << endl;

                        int i = (y-offsetY)/tamanoCasilla;
                        int j = (x-offsetX)/tamanoCasilla;

                        if((i>=0) && (i<8) && (j>=0) && (j<8)){
                            if((tablero[i][j] == 1) || (tablero[i][j] == 2)){

                                if (fichaSeleccionada) {

                                    fichaSeleccionada = false; // Deselecciona la ficha
                                } else {
                                    fichaSeleccionada = true; // Selecciona una ficha
                                    fichaSeleccionadaX = j;
                                    fichaSeleccionadaY = i;
                                }
                            }
                        }

                    }

                }
                break;
            }
        }
        Damas.clear();
        Damas.draw(fondo);

        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                float x = offsetX + j * tamanoCasilla;
                float y = offsetY + i * tamanoCasilla;

                if(tablero[i][j] == 1){
                    fichaBlanca.setPosition(x, y);
                    Damas.draw(fichaBlanca);
                }
                if(tablero[i][j] == 2){
                    fichaNegra.setPosition(x, y);
                    Damas.draw(fichaNegra);
                }
            }
        }

        if (fichaSeleccionada) {
            int dx[2];
            int dy[2];

            if(tablero[fichaSeleccionadaY][fichaSeleccionadaX] == 1){

                dx[0] = -1;
                dx[1] = 1;
                dy[0] = 1;
                dy[1] = 1;

            }else if(tablero[fichaSeleccionadaY][fichaSeleccionadaX] == 2){

                dx[0] = -1;
                dx[1] = 1;
                dy[0] = -1;
                dy[1] = -1;

            }
            for (int i = 0; i < 2; ++i) {
                int newX = fichaSeleccionadaX + dx[i];
                int newY = fichaSeleccionadaY + dy[i];

                if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 && (tablero[newY][newX] == 0)) {
                    movimiento.setPosition(offsetX + newX*tamanoCasilla + (tamanoCasilla/2 - movimiento.getRadius()),offsetY + newY*tamanoCasilla + (tamanoCasilla/ 2 - movimiento.getRadius()));
                    Damas.draw(movimiento);
                }
            }
        }
        Damas.display();
    }
}

void abrirJugar(RenderWindow &Jugar, Font &font, Boton modosJuego[]){
    RectangleShape fondo;
    Texture texturaModos;
    fondo.setSize(Vector2f(1280,720));
    texturaModos.loadFromFile("Texturas/fondoModosDeJuego.png");
    fondo.setTexture(&texturaModos);

    Event aevent;
    while(Jugar.pollEvent(aevent)){
        switch(aevent.type){
            case Event::Closed:
                Jugar.close();
                break;

            case Event::MouseMoved:
                for (int i = 0; i < 8; ++i) {
                    cambiarColorBoton(modosJuego[i], Jugar);
                }
                break;

            case Event::MouseButtonPressed:{
                if(modosJuego[7].isMouseOver(Jugar)){


                    Jugar.close();
                    jugarDamas(font);
                    Jugar.create(VideoMode(1280,720), "Jugar", Style::Default);
                }
            }

                break;
        }
    }

    Jugar.clear();
    Jugar.draw(fondo);
    for(int i = 0; i < 8; i++){
        modosJuego[i].drawTo(Jugar);
    }
}

void abrirTutorial(RenderWindow &Opcion, Font &font, Boton &siguiente){
    RectangleShape fondo;
    Texture texturaTutorial;
    string tutorial = "tutorial_";
    stringstream ss;
    ss << tutorial << indexTutorial;
    string archivo = ss.str();
    Event aevent;

    fondo.setSize(Vector2f(1280,720));
    texturaTutorial.loadFromFile("Texturas/" + archivo+ ".png");
    fondo.setTexture(&texturaTutorial);

    while(Opcion.pollEvent(aevent)){
        if(aevent.type == Event::Closed){
            Opcion.close();
        }
        if(aevent.type == Event::KeyPressed){
            if(aevent.key.code == Keyboard::Escape)
            {
                Opcion.close();
            }
        }

        switch(aevent.type){
            case Event::Closed:{
                Opcion.close();
            }
            break;
            case Event::KeyPressed:{
                if(aevent.key.code == Keyboard::Escape)
                {
                    Opcion.close();
                }
            }
            break;
            case Event::MouseMoved:{
                if(siguiente.isMouseOver(Opcion)){
                    siguiente.setBackColor(Color::Black);
                }else{
                    siguiente.setBackColor(Color(255, 255, 255, 0));
                }
            }
            break;
            case Event::MouseButtonPressed:{
                if(siguiente.isMouseOver(Opcion) && (indexTutorial != 7)){
                    indexTutorial +=1;
                }
            }
            break;
        }

    }
    Opcion.clear();
    Opcion.draw(fondo);
    siguiente.drawTo(Opcion);
}

void iniciarJuego(){
    RenderWindow MENU(VideoMode(1280,720), "Menu Principal", Style::Default);

    RectangleShape fondo;

    fondo.setSize(Vector2f(1280,720));
    Texture texturaPrincipal;
    texturaPrincipal.loadFromFile("Texturas/fondoMenuPrincipal.png");
    fondo.setTexture(&texturaPrincipal);

    Font font;
    font.loadFromFile("Fuentes/LemonShakeShake.ttf");

    Boton botones[4];
    int posicion = 100;

    string textoBotonesMenu[] = {"Jugar", "Tutorial", "Creditos", "Salir"};

    for (int i = 0; i<4; i++){
        botones[i] = Boton(textoBotonesMenu[i],{325,80},70,Color(255, 255, 255, 10),Color::White);
        botones[i].setPosition({225, posicion + i*100});
        botones[i].setFont(font);

    }

    Boton siguiente = Boton("Siguiente",{310,80},60,Color(255, 255, 255, 0),Color::White);
    siguiente.setPosition({850, 600});
    siguiente.setFont(font);

    posicion = 125;
    Boton modosJuego[8];
    string textoBotonesJugar[] = {"1 Jugador", "2 Jugadores", "3 Jugadores", "4 Jugadores", "5 Jugadores", "6 Jugadores", "1 Jugador", "2 Jugadores"};

    for (int i = 0; i<6; i++){
        modosJuego[i] = Boton(textoBotonesJugar[i],{325,55},35,Color(255, 255, 255, 0),Color::White);
        modosJuego[i].setPosition({100,posicion + i*60});
        modosJuego[i].setFont(font);
    }

    for (int i = 6; i<8; i++){
        modosJuego[i] = Boton(textoBotonesJugar[i],{325,55},40,Color(255, 255, 255, 0),Color::White);
    }

    modosJuego[6].setPosition({100,600});
    modosJuego[6].setFont(font);

    modosJuego[7].setPosition({550,600});
    modosJuego[7].setFont(font);

    /*
    Texture texturaSprite;
    texturaSprite.loadFromFile("Texturas/texturaBase_ficha.png");
    Sprite sprite;
    sprite.setTexture(texturaSprite);
    sprite.setColor(Color::Green);
    sprite.setPosition(Vector2f(10.f, 50.f));
*/
    while(MENU.isOpen()){
        Event evento;
        while(MENU.pollEvent(evento)){

            switch(evento.type){
                case Event::Closed:{
                    MENU.close();
                }
                break;
                case Event::MouseMoved:
                    for (int i = 0; i < 4; ++i) {
                        cambiarColorBoton(botones[i], MENU);
                    }
                break;
                case Event::MouseButtonPressed:{
                    if(botones[0].isMouseOver(MENU) || botones[1].isMouseOver(MENU) || botones[2].isMouseOver(MENU) || botones[3].isMouseOver(MENU)){
                        RenderWindow Jugar(VideoMode(1280,720),"Damas Chinas");
                        RenderWindow Opcion(VideoMode(1280,720), "¿Como Jugar?");
                        RenderWindow Creditos(VideoMode(1280,720),"Creditos");

                        if(botones[0].isMouseOver(MENU)){
                            MENU.close();
                            while(Jugar.isOpen()){
                                abrirJugar(Jugar, font, modosJuego);
                                Opcion.close();
                                Creditos.close();
                                Jugar.display();
                            }
                            MENU.create(VideoMode(1280,720), "Menu Principal", Style::Default);
                        }

                        if(botones[1].isMouseOver(MENU)){
                            MENU.close();
                            while(Opcion.isOpen()){
                                abrirTutorial(Opcion, font, siguiente);
                                Jugar.close();
                                Creditos.close();
                                Opcion.display();
                            }
                            MENU.create(VideoMode(1280,720), "Menu Principal", Style::Default);
                        }

                        if(botones[2].isMouseOver(MENU)){
                            while(Creditos.isOpen()){
                                Event aevent;
                                while(Creditos.pollEvent(aevent)){
                                    if(aevent.type == Event::Closed){
                                        Creditos.close();
                                    }
                                    if(aevent.type == Event::KeyPressed){
                                        if(aevent.key.code == Keyboard::Escape){
                                            Creditos.close();
                                        }
                                    }
                                }
                                Jugar.close();
                                Opcion.clear();
                                Creditos.clear();
                                Creditos.display();
                            }
                        }

                        if(botones[3].isMouseOver(MENU)){
                            MENU.close();
                        }

                    }
                }
                break;
            }
        }
        MENU.clear();
        MENU.draw(fondo);
        for(int i = 0; i<4; i++){
            botones[i].drawTo(MENU);
        }
        MENU.display();
    }
}

int main(){
    iniciarJuego();
    return 0;
}
