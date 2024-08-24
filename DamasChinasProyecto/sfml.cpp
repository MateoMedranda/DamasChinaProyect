#include <SFML/Graphics.hpp>
#include "Boton.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
using namespace sf;

int indexTutorial = 1;

void abrirJugar(RenderWindow &Jugar, Font &font, Boton modosJuego[]){
    RectangleShape fondo;
    Texture texturaModos;
    fondo.setSize(Vector2f(1280,720));
    texturaModos.loadFromFile("Texturas/fondoModosDeJuego.png");
    fondo.setTexture(&texturaModos);

    Event aevent;
    while(Jugar.pollEvent(aevent)){
        switch(aevent.type){
            case Event::Closed:{
                    Jugar.close();
                }
                break;
            case Event::MouseMoved:{
                if(modosJuego[0].isMouseOver(Jugar)){
                    modosJuego[0].setBackColor(Color::Black);
                }else{
                    modosJuego[0].setBackColor(Color(255, 255, 255, 0));
                }
                if(modosJuego[1].isMouseOver(Jugar)){
                    modosJuego[1].setBackColor(Color::Black);
                }else{
                    modosJuego[1].setBackColor(Color(255, 255, 255, 0));
                }
                if(modosJuego[2].isMouseOver(Jugar)){
                    modosJuego[2].setBackColor(Color::Black);
                }else{
                    modosJuego[2].setBackColor(Color(255, 255, 255, 0));
                }
                if(modosJuego[3].isMouseOver(Jugar)){
                    modosJuego[3].setBackColor(Color::Black);
                }else{
                    modosJuego[3].setBackColor(Color(255, 255, 255, 0));
                }
                if(modosJuego[4].isMouseOver(Jugar)){
                    modosJuego[4].setBackColor(Color::Black);
                }else{
                    modosJuego[4].setBackColor(Color(255, 255, 255, 0));
                }
                if(modosJuego[5].isMouseOver(Jugar)){
                    modosJuego[5].setBackColor(Color::Black);
                }else{
                    modosJuego[5].setBackColor(Color(255, 255, 255, 0));
                }
                if(modosJuego[6].isMouseOver(Jugar)){
                    modosJuego[6].setBackColor(Color::Black);
                }else{
                    modosJuego[6].setBackColor(Color(255, 255, 255, 0));
                }
                if(modosJuego[7].isMouseOver(Jugar)){
                    modosJuego[7].setBackColor(Color::Black);
                }else{
                    modosJuego[7].setBackColor(Color(255, 255, 255, 0));
                }
                }
                break;
            case Event::MouseButtonPressed:{

            }
            break;
        }
    }
    Jugar.clear();
    Jugar.draw(fondo);
    for(int i = 0; i<8; i++){
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
                case Event::MouseMoved:{
                    if(botones[0].isMouseOver(MENU)){
                        botones[0].setBackColor(Color::Black);
                    }else{
                        botones[0].setBackColor(Color(255, 255, 255, 0));
                    }

                    if(botones[1].isMouseOver(MENU)){
                        botones[1].setBackColor(Color::Black);
                    }else{
                        botones[1].setBackColor(Color(255, 255, 255, 0));
                    }

                    if(botones[2].isMouseOver(MENU)){
                        botones[2].setBackColor(Color::Black);
                    }else{
                        botones[2].setBackColor(Color(255, 255, 255, 0));
                    }

                    if(botones[3].isMouseOver(MENU)){
                        botones[3].setBackColor(Color::Black);
                    }else{
                        botones[3].setBackColor(Color(255, 255, 255, 0));
                    }
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
