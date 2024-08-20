#include <SFML/Graphics.hpp>
#include "Boton.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
using namespace sf;

int indexTutorial = 1;

void abrirJugar(RenderWindow &Jugar, Font &font){
    RectangleShape fondo;
    Texture texturaModos;
    fondo.setSize(Vector2f(1280,720));
    texturaModos.loadFromFile("Texturas/fondoModosDeJuego.png");
    fondo.setTexture(&texturaModos);

    int posicion = 100;
    Boton modosJuego[6];
    string textoBotones[] = {"1 Jugador", "2 Jugadores", "3 Jugadores", "4 Jugadores", "5 Jugadores", "6 Jugadores"};

    for (int i = 0; i<6; i++){
        modosJuego[i] = Boton(textoBotones[i],{325,75},50,Color(255, 255, 255, 10),Color::White);
        modosJuego[i].setPosition({100,posicion + i*75});
        modosJuego[i].setFont(font);
    }

    Event aevent;
    while(Jugar.pollEvent(aevent)){
        if(aevent.type == Event::Closed){
            Jugar.close();
        }
        if(aevent.type == Event::KeyPressed){
            if(aevent.key.code == Keyboard::Escape){
                Jugar.close();
            }
        }
    }
    Jugar.clear();
    Jugar.draw(fondo);
    for(int i = 0; i<6; i++){
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
                if(siguiente.isMouseOver(Opcion)){
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

int main(){
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

    string textoBotones[] = {"Jugar", "Tutorial", "Creditos", "Salir"};

    for (int i = 0; i<4; i++){
        botones[i] = Boton(textoBotones[i],{325,80},70,Color(255, 255, 255, 10),Color::White);
        botones[i].setPosition({225, posicion + i*100});
        botones[i].setFont(font);

    }

    Boton siguiente = Boton("Siguiente",{310,80},60,Color(255, 255, 255, 0),Color::White);
    siguiente.setPosition({850, 600});
    siguiente.setFont(font);

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
                                abrirJugar(Jugar, font);
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
