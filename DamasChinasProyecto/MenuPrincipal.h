#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;
using namespace sf;


class MenuPrincipal{
private:
    int MenuSeleccionado;
    Font font;
    Text menuPrincipal[4];

public:
    MenuPrincipal(float ancho, float alto);

    void draw(RenderWindow& window);
    void MoveUp();
    void MoveDown();

    int MenuPressed(){
        return MenuSeleccionado;
    }
    ~MenuPrincipal();
};
