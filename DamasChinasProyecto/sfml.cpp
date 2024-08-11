#include <SFML/Graphics.hpp>
#include "MenuPrincipal.h"
#include <iostream>

using namespace std;
using namespace sf;

int main(){
    RenderWindow MENU(VideoMode(1280,720), "Menu Principal", Style::Default);
    MenuPrincipal menuPrincipal(MENU.getSize().x, MENU.getSize().y);

    RectangleShape fondo;
    fondo.setSize(Vector2f(1280,720));
    Texture texturaPrincipal;
    texturaPrincipal.loadFromFile("Texturas/fondoMenuPrincipal.png");
    fondo.setTexture(&texturaPrincipal);


    while(MENU.isOpen()){
        Event evento;
        while(MENU.pollEvent(evento)){
            if(evento.type == Event::Closed){
                MENU.close();
            }

            if(evento.type == Event::KeyReleased){
                if(evento.key.code == Keyboard::Up){
                    menuPrincipal.MoveUp();
                    break;
                }

                if(evento.key.code == Keyboard::Down){
                    menuPrincipal.MoveDown();
                    break;
                }

                if(evento.key.code == Keyboard::Return){
                    RenderWindow Jugar(VideoMode(960,720),"Damas Chinas");
                    RenderWindow Opcion(VideoMode(960,720), "Opciones");
                    RenderWindow Creditos(VideoMode(960,720),"Créditos");

                    int x = menuPrincipal.MenuPressed();
                    if(x == 0){
                        while(Jugar.isOpen()){
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
                            Opcion.close();
                            Creditos.close();
                            Jugar.clear();
                            Jugar.display();
                        }
                    }
                    if(x == 1){
                        while(Opcion.isOpen()){
                            Event aevent;
                            while(Opcion.pollEvent(aevent)){
                                if(aevent.type == Event::Closed){
                                    Opcion.close();
                                }
                                if(aevent.type == Event::KeyPressed){
                                    if(aevent.key.code == Keyboard::Escape){
                                        Opcion.close();
                                    }
                                }
                            }
                            Jugar.close();
                            Opcion.clear();
                            Creditos.close();
                            Opcion.display();
                        }
                    }
                    if(x == 2){
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
                    if(x == 3){
                        MENU.close();
                    }
                    break;
                }
            }
        }
        MENU.clear();
        MENU.draw(fondo);
        menuPrincipal.draw(MENU);
        MENU.display();
    }
}
