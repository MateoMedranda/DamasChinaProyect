#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Boton{
private:
    RectangleShape boton;
    Text texto;
public:
    Boton(){}

    Boton(string t, Vector2f size,int charSize, Color bgcolor, Color textColor) {
        texto.setString(t);
        texto.setColor(textColor);
        texto.setCharacterSize(charSize);

        boton.setSize(size);
        boton.setFillColor(bgcolor);

    }

    void setFont(Font &font){
        texto.setFont(font);
    }

    void setBackColor(Color color){
        boton.setFillColor(color);
    }

    void setTextColor(Color color){
        texto.setFillColor(color);
    }

    void setPosition(Vector2f pos){
        boton.setPosition(pos);

        float xPos = (pos.x + boton.getLocalBounds().width/20) - (texto.getLocalBounds().width/2);
        float yPos = (pos.y) - (texto.getLocalBounds().height/2);
        texto.setPosition(xPos, yPos);
    }

    void drawTo(RenderWindow &window){
        window.draw(boton);
        window.draw(texto);
    }

    bool isMouseOver(RenderWindow &window){
        float mouseX = Mouse::getPosition(window).x;
        float mouseY = Mouse::getPosition(window).y;

        float btnPosX = boton.getPosition().x;
        float btnPosY = boton.getPosition().y;

        float btnPosWidth = boton.getPosition().x + boton.getLocalBounds().width;
        float btnPosHeigh = boton.getPosition().y + boton.getLocalBounds().height;

        if((mouseX < btnPosWidth) && (mouseX > btnPosX) && (mouseY < btnPosHeigh) && (mouseY > btnPosY)){
            return true;
        }else{
            return false;
        }
    }

};
