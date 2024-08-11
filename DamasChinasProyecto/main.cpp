#include <SFML/Graphics.hpp>
#include "MenuPrincipal.h"
#include <iostream>

using namespace std;
using namespace sf;

MenuPrincipal::MenuPrincipal(float ancho, float alto){
    if(!font.loadFromFile("Fuentes/LemonShakeShake.ttf")){
        cout << "No existe la fuente" << endl;
    }

    int posicion = 100;

    for(int i = 0; i<4; i++){
        menuPrincipal[i].setFont(font);
        menuPrincipal[i].setFillColor(Color::White);
        menuPrincipal[i].setCharacterSize(70);
        menuPrincipal[i].setPosition(250,posicion+i*100);
    }

    menuPrincipal[0].setString("Jugar");
    menuPrincipal[1].setString("Opciones");
    menuPrincipal[2].setString("Creditos");
    menuPrincipal[3].setString("Salir");
    MenuSeleccionado = 0;
}

MenuPrincipal::~MenuPrincipal(){
}

void MenuPrincipal::draw(RenderWindow& window){
    for(int i=0; i<4; i++){
        window.draw(menuPrincipal[i]);
    }
}

void MenuPrincipal::MoveUp(){
        menuPrincipal[MenuSeleccionado].setFillColor(Color::White);
        MenuSeleccionado--;

        if(MenuSeleccionado == -1){
            MenuSeleccionado = 3;
        }

        menuPrincipal[MenuSeleccionado].setFillColor(Color::Yellow);
}

void MenuPrincipal::MoveDown(){
        menuPrincipal[MenuSeleccionado].setFillColor(Color::White);
        MenuSeleccionado++;

        if(MenuSeleccionado == 4){
            MenuSeleccionado =0;
        }
        menuPrincipal[MenuSeleccionado].setFillColor(Color::Yellow);
}
