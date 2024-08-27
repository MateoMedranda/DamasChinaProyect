#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Boton.h"
#include <string>
#include <iostream>
#include <sstream>
#include "Jugador.h"


using namespace std;
using namespace sf;

int indexTutorial = 1;

// Definimos las dimensiones del tablero
const int FILAS = 17;
const int COLUMNAS = 25;

// Definimos los valores para cada celda
const int VACIO = -1;
const int MOV = 0;
const int JUGADOR1 = 1;
const int JUGADOR2 = 2;
const int JUGADOR3 = 3;
const int JUGADOR4 = 4;
const int JUGADOR5 = 5;
const int JUGADOR6 = 6;


void crearMatrizNJugadoresDamas(int tablero[FILAS][COLUMNAS], int numJugadores){
    for (int i = 0; i < FILAS; i++) {
        for (int j = 0; j < COLUMNAS; j++) {
            tablero[i][j] = VACIO;
        }
    }

    for (int i = 8; i < 17; i+=2) {
  	    tablero[4][i] = MOV;
    }

    for (int i = 7; i < 18; i+=2) {
  	    tablero[5][i] = MOV;
    }

    for (int i = 6; i < 19; i+=2) {
  	    tablero[6][i] = MOV;
    }

    for (int i = 5; i < 20; i+=2) {
  	    tablero[7][i] = MOV;
    }

    for (int i = 4; i < 21; i+=2) {
  	    tablero[8][i] = MOV;
    }

    for (int i = 5; i < 20; i+=2) {
  	    tablero[9][i] = MOV;
    }

    for (int i = 6; i < 19; i+=2) {
  	    tablero[10][i] = MOV;
    }

    for (int i = 7; i < 18; i+=2) {
  	    tablero[11][i] = MOV;
    }

    for (int i = 8; i < 17; i+=2) {
  	    tablero[12][i] = MOV;
    }

    if(numJugadores >= 2){
    // Jugador 1 (parte superior)
    tablero[0][12] = JUGADOR1;
    tablero[1][11] = tablero[1][13] = JUGADOR1;
    tablero[2][10] = tablero[2][12] = tablero[2][14] = JUGADOR1;
    tablero[3][9] = tablero[3][11] = tablero[3][13] = tablero[3][15] = JUGADOR1;

    // Jugador 2 (parte inferior)
    tablero[16][12] = JUGADOR2;
    tablero[15][11] = tablero[15][13] = JUGADOR2;
    tablero[14][10] = tablero[14][12] = tablero[14][14] = JUGADOR2;
    tablero[13][9] = tablero[13][11] = tablero[13][13] = tablero[13][15] = JUGADOR2;
    }

    if(numJugadores >= 3){
    // Jugador 3 (parte inferior izquierda)
    tablero[9][3] = JUGADOR3;
    tablero[10][2] = tablero[10][4] = JUGADOR3;
    tablero[11][1] = tablero[11][3] = tablero[11][5] = JUGADOR3;
    tablero[12][0] = tablero[12][2] = tablero[12][4] = tablero[12][6] = JUGADOR3;
    }

    if(numJugadores >= 4){
    // Jugador 4 (parte superior derecha)
    tablero[7][21] = JUGADOR4;
    tablero[6][20] = tablero[6][22] = JUGADOR4;
    tablero[5][19] = tablero[5][21] = tablero[5][23] = JUGADOR4;
    tablero[4][18] = tablero[4][20] = tablero[4][22] = tablero[4][24] = JUGADOR4;
    }

    if(numJugadores >= 5){
    // Jugador 5 (parte superior izquierda)
    tablero[7][3] = JUGADOR5;
    tablero[6][2] = tablero[6][4] = JUGADOR5;
    tablero[5][1] = tablero[5][3] = tablero[5][5] = JUGADOR5;
    tablero[4][0] = tablero[4][2] = tablero[4][4] = tablero[4][6] = JUGADOR5;
    }

    if(numJugadores == 6){
    // Jugador 6 (parte inferior derecha)
    tablero[9][21] = JUGADOR6;
    tablero[10][20] = tablero[10][22] = JUGADOR6;
    tablero[11][19] = tablero[11][21] = tablero[11][23] = JUGADOR6;
    tablero[12][18] = tablero[12][20] = tablero[12][22] = tablero[12][24] = JUGADOR6;
    }
}

void crearMatrizDamas(int damas[8][8]){
    int tablero[8][8] = {
                {-1,1,-1,1,-1,1,-1,1},
                {1,-1,1,-1,1,-1,1,-1},
                {-1,1,-1,1,-1,1,-1,1},
                {0,-1,0,-1,0,-1,0,-1},
                {-1,0,-1,0,-1,0,-1,0},
                {2,-1,2,-1,2,-1,2,-1},
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

void ventanaRegistro(RenderWindow& window, Font& font);

// Función para mostrar la ventana de mensajes
void mostrarMensaje(RenderWindow& window, const string& mensaje, Font& font) {
    Text texto(mensaje, font, 24);
    texto.setFillColor(Color::White);
    texto.setPosition(50, 200);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear(Color::Black);
        window.draw(texto);
        window.display();
    }
}

// Función para mostrar la ventana de entrada de usuario
void ventanaEntradaUsuario(RenderWindow& window, Font& font) {
    RectangleShape fondo(Vector2f(1280,720));
    Texture texturaModos;
    texturaModos.loadFromFile("Texturas/fondoModosDeJuego.png");
    fondo.setTexture(&texturaModos);

    Text titulo("Ingrese Usuario", font, 24);
    titulo.setPosition(50, 50);

    Text usuarioTexto("Usuario:", font, 20);
    usuarioTexto.setPosition(50, 100);
    usuarioTexto.setFillColor(Color::White);

    RectangleShape usuarioBox(Vector2f(400, 40));
    usuarioBox.setPosition(150, 100);
    usuarioBox.setFillColor(Color::Black);
    usuarioBox.setOutlineColor(Color::White);
    usuarioBox.setOutlineThickness(1);

    Text usuarioInput("", font, 24);
    usuarioInput.setPosition(155, 105);
    usuarioInput.setFillColor(Color::White);

    Text continuarButton("Continuar", font, 24);
    continuarButton.setPosition(50, 200);
    continuarButton.setFillColor(Color::White);

    RectangleShape continuarBox(Vector2f(150, 40));
    continuarBox.setPosition(50, 200);
    continuarBox.setFillColor(Color::Blue);

    string usuarioStr = "";

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            // Captura de texto para usuario
            if (event.type == Event::TextEntered) {
                if ((event.text.unicode >= 'A' && event.text.unicode <= 'Z') ||
                    (event.text.unicode >= 'a' && event.text.unicode <= 'z') ||
                    (event.text.unicode >= '0' && event.text.unicode <= '9') ||
                    event.text.unicode == '\b') {
                    if (event.text.unicode != '\b') {
                        usuarioStr += static_cast<char>(event.text.unicode);
                    } else if (!usuarioStr.empty()) {
                        usuarioStr.pop_back();
                    }
                    usuarioInput.setString(usuarioStr);
                }
            }

            // Manejo del clic en el botón Continuar
            if (event.type == Event::MouseButtonPressed) {
                if (continuarBox.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    cout << "Verificando usuario: " << usuarioStr << endl;
                    if (Jugador::usuarioExisteEnArchivo(usuarioStr, "jugadores.txt")) {
                        window.close();
                    } else {
                        cout << "Usuario no existe, abriendo ventana de registro" << endl;
                        // Usuario no existe, redirigir a ventana de registro
                        ventanaRegistro(window, font);
                    }
                    return;
                }
            }
        }

        window.clear(Color::Black);
        window.draw(titulo);
        window.draw(usuarioTexto);
        window.draw(usuarioBox);
        window.draw(continuarBox);
        window.draw(continuarButton);
        window.draw(usuarioInput);
        window.display();
    }
}

void ventanaRegistro(RenderWindow& window, Font& font) {
    RectangleShape fondo;
    Texture texturaModos;
    fondo.setSize(Vector2f(1280,720));
    texturaModos.loadFromFile("Texturas/fondoModosDeJuego.png");
    fondo.setTexture(&texturaModos);

    Text titulo("Registro de Jugador", font, 24);
    titulo.setPosition(50, 50);

    Text nombreTexto("Nombre:", font, 20);
    nombreTexto.setPosition(50, 100);
    nombreTexto.setFillColor(Color::White);

    Text usuarioTexto("Usuario:", font, 20);
    usuarioTexto.setPosition(50, 150);
    usuarioTexto.setFillColor(Color::White);

    RectangleShape nombreBox(Vector2f(400, 40));
    nombreBox.setPosition(150, 100);
    nombreBox.setFillColor(Color::Black);
    nombreBox.setOutlineColor(Color::White);
    nombreBox.setOutlineThickness(1);

    RectangleShape usuarioBox(Vector2f(400, 40));
    usuarioBox.setPosition(150, 150);
    usuarioBox.setFillColor(Color::Black);
    usuarioBox.setOutlineColor(Color::White);
    usuarioBox.setOutlineThickness(1);

    Text guardarButton("Guardar", font, 24);
    guardarButton.setPosition(50, 250);
    guardarButton.setFillColor(Color::White);

    RectangleShape guardarBox(Vector2f(150, 40));
    guardarBox.setPosition(50, 250);
    guardarBox.setFillColor(Color::Blue);

    Text nombreInput("", font, 24);
    nombreInput.setPosition(155, 105);
    nombreInput.setFillColor(Color::White);

    Text usuarioInput("", font, 24);
    usuarioInput.setPosition(155, 155);
    usuarioInput.setFillColor(Color::White);

    string nombreStr = "";
    string usuarioStr = "";
    bool nombreActivo = true;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            // Manejo de la selección de caja de texto
            if (event.type == Event::MouseButtonPressed) {
                // Verificar si se seleccionó la caja de nombre
                if (nombreBox.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    nombreActivo = true;
                }
                // Verificar si se seleccionó la caja de usuario
                else if (usuarioBox.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    nombreActivo = false;
                }
                // Verificar si se hizo clic en el botón Guardar
                else if (guardarBox.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    if (nombreStr.empty() || usuarioStr.empty()) {
                        mostrarMensaje(window, "Por favor, complete todos los campos.", font);
                    } else if (Jugador::usuarioExisteEnArchivo(usuarioStr, "jugadores.txt")) {
                        mostrarMensaje(window, "Usuario ya existe. Intente con otro.", font);
                    } else {
                        // Crear objeto Jugador y guardarlo
                        Jugador nuevoJugador(nombreStr, usuarioStr);
                        nuevoJugador.guardarEnArchivo("jugadores.txt");
                        cout << "Jugador registrado exitosamente." << endl;

                        window.close();
                    }
                }
            }

            // Captura de texto para nombre y usuario
            if (event.type == Event::TextEntered) {
                if (nombreActivo) {
                    if ((event.text.unicode >= 'A' && event.text.unicode <= 'Z') ||
                        (event.text.unicode >= 'a' && event.text.unicode <= 'z') ||
                        (event.text.unicode >= '0' && event.text.unicode <= '9') ||
                        event.text.unicode == ' ' || event.text.unicode == '\b') {
                        if (event.text.unicode != '\b') {
                            nombreStr += static_cast<char>(event.text.unicode);
                        } else if (!nombreStr.empty()) {
                            nombreStr.pop_back();
                        }
                        nombreInput.setString(nombreStr);
                    }
                } else {
                    if ((event.text.unicode >= 'A' && event.text.unicode <= 'Z') ||
                        (event.text.unicode >= 'a' && event.text.unicode <= 'z') ||
                        (event.text.unicode >= '0' && event.text.unicode <= '9') ||
                        event.text.unicode == '\b') {
                        if (event.text.unicode != '\b') {
                            usuarioStr += static_cast<char>(event.text.unicode);
                        } else if (!usuarioStr.empty()) {
                            usuarioStr.pop_back();
                        }
                        usuarioInput.setString(usuarioStr);
                    }
                }
            }
        }

        window.clear(Color::Black);
        window.draw(titulo);
        window.draw(nombreTexto);
        window.draw(usuarioTexto);
        window.draw(nombreBox);
        window.draw(usuarioBox);
        window.draw(guardarBox);
        window.draw(guardarButton);
        window.draw(nombreInput);
        window.draw(usuarioInput);
        window.display();
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

    Sprite fichaBlanca, fichaNegra, damaBlanca, damaNegra;
    fichaBlanca.setTexture(textura1);
    fichaNegra.setTexture(textura2);
    damaBlanca.setTexture(textura3);
    damaNegra.setTexture(textura4);

    CircleShape movimiento(30.0f); // Tamaño del círculo para mostrar los movimientos
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

                    int temp;
                    if (aevent.mouseButton.button == Mouse::Left){
                        float x = Mouse::getPosition(Damas).x;
                        float y = Mouse::getPosition(Damas).y;


                        int i = (y-offsetY)/tamanoCasilla;
                        int j = (x-offsetX)/tamanoCasilla;

                        cout << "i: " << i << "j: " << j << endl;


                        if((i>=0) && (i<8) && (j>=0) && (j<8)){
                            if((tablero[i][j] == 1) || (tablero[i][j] == 2) || (tablero[i][j] == 3) || (tablero[i][j] == 4)){

                                if (fichaSeleccionada) {
                                    fichaSeleccionada = false; // Deselecciona la ficha
                                } else {
                                    fichaSeleccionada = true; // Selecciona una ficha
                                    fichaSeleccionadaX = j;
                                    fichaSeleccionadaY = i;
                                }

                            }else if(tablero[i][j] == 0 && fichaSeleccionada){

                                int dx[4];
                                int dy[4];
                                int n;

                                if(tablero[fichaSeleccionadaY][fichaSeleccionadaX] == 1){

                                    dx[0] = -1;
                                    dx[1] = 1;
                                    dy[0] = 1;
                                    dy[1] = 1;
                                    n = 2;

                                }else if(tablero[fichaSeleccionadaY][fichaSeleccionadaX] == 2){

                                    dx[0] = -1;
                                    dx[1] = 1;
                                    dy[0] = -1;
                                    dy[1] = -1;
                                    n = 2;

                                }else if(tablero[fichaSeleccionadaY][fichaSeleccionadaX] == 3 || tablero[fichaSeleccionadaY][fichaSeleccionadaX]){
                                    dx[0] = -1;
                                    dx[1] = 1;
                                    dx[2] = -1;
                                    dx[3] = 1;
                                    dy[0] = -1;
                                    dy[1] = -1;
                                    dy[2] = 1;
                                    dy[3] = 1;
                                    n = 4;
                                }

                                for (int k = 0; k < n; ++k) {
                                    int newX = fichaSeleccionadaX + dx[k];
                                    int newY = fichaSeleccionadaY + dy[k];

                                    if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 && (tablero[newY][newX] == 0)) {
                                        cout << "fichax: " << fichaSeleccionadaX << "fichaY: " << fichaSeleccionadaY << endl;
                                        cout << "x: " << newX << "y: " << newY << endl;
                                        if(newX == j && newY == i){
                                            temp = tablero[fichaSeleccionadaY][fichaSeleccionadaX];
                                            tablero[fichaSeleccionadaY][fichaSeleccionadaX] = 0;
                                            tablero[newY][newX] = temp;

                                            if(newY == 0 && temp == 2){
                                                tablero[newY][newX] = 4;

                                            }
                                            if(newY == 7 && temp == 1){
                                                tablero[newY][newX] = 3;

                                            }
                                        }
                                    }
                                    if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 && (tablero[newY][newX] != tablero[fichaSeleccionadaY][fichaSeleccionadaX]) && (tablero[newY][newX] != 0) && !(tablero[newY][newX]+2 == tablero[fichaSeleccionadaY][fichaSeleccionadaX])) {
                                        int antx = newX , anty = newY;
                                        newX = newX + dx[k];
                                        newY = newY + dy[k];

                                        if(newX == j && newY == i && tablero[newY][newX] == 0){
                                            temp = tablero[fichaSeleccionadaY][fichaSeleccionadaX];
                                            tablero[fichaSeleccionadaY][fichaSeleccionadaX] = 0;
                                            tablero[newY][newX] = temp;
                                            tablero[anty][antx]=0;

                                            if(newY == 0 && temp == 2){
                                                tablero[newY][newX] = 4;

                                            }
                                            if(newY == 7 && temp == 1){
                                                tablero[newY][newX] = 3;

                                            }
                                        }

                                    }
                                }
                                fichaSeleccionada = false;
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
                if(tablero[i][j] == 3){
                    damaBlanca.setPosition(x,y);
                    Damas.draw(damaBlanca);
                }
                if(tablero[i][j] == 4){
                    damaNegra.setPosition(x,y);
                    Damas.draw(damaNegra);
                }
            }
        }

        if (fichaSeleccionada) {
            int dx[4];
            int dy[4];
            int n;

            if(tablero[fichaSeleccionadaY][fichaSeleccionadaX] == 1){

                dx[0] = -1;
                dx[1] = 1;
                dy[0] = 1;
                dy[1] = 1;
                n = 2;

            }else if(tablero[fichaSeleccionadaY][fichaSeleccionadaX] == 2){

                dx[0] = -1;
                dx[1] = 1;
                dy[0] = -1;
                dy[1] = -1;
                n = 2;

            }else if (tablero[fichaSeleccionadaY][fichaSeleccionadaX] == 3 || tablero[fichaSeleccionadaY][fichaSeleccionadaX] == 4 ){
                dx[0] = -1;
                dx[1] = 1;
                dx[2] = -1;
                dx[3] = 1;
                dy[0] = -1;
                dy[1] = -1;
                dy[2] = 1;
                dy[3] = 1;
                n = 4;
            }

            for (int i = 0; i < n; ++i) {
                int newX = fichaSeleccionadaX + dx[i];
                int newY = fichaSeleccionadaY + dy[i];

                if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 && (tablero[newY][newX] == 0)) {
                    movimiento.setPosition(offsetX + newX*tamanoCasilla + (tamanoCasilla/2 - movimiento.getRadius()),offsetY + newY*tamanoCasilla + (tamanoCasilla/ 2 - movimiento.getRadius()));
                    Damas.draw(movimiento);
                }
                if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8 && (tablero[newY][newX] != tablero[fichaSeleccionadaY][fichaSeleccionadaX]) && (tablero[newY][newX] != 0) && !(tablero[newY][newX]+2 == tablero[fichaSeleccionadaY][fichaSeleccionadaX])) {
                    newX = newX+ dx[i];
                    newY = newY + dy[i];
                    if(tablero[newY][newX] == 0){
                        movimiento.setPosition(offsetX + newX*tamanoCasilla + (tamanoCasilla/2 - movimiento.getRadius()),offsetY + newY*tamanoCasilla + (tamanoCasilla/ 2 - movimiento.getRadius()));
                        Damas.draw(movimiento);
                    }
                }
            }

        }
        Damas.display();
    }
}


void jugarDamasChinas(Font &font){

    int tablero[FILAS][COLUMNAS];
    crearMatrizNJugadoresDamas(tablero,6);

    RenderWindow DamasChinas(VideoMode(1280,720),"Damas Chinas");

    RectangleShape fondo;
    Texture textura, textura1;
    fondo.setSize(Vector2f(1280,720));
    textura.loadFromFile("Texturas/tableroDamasChinas.png");
    textura1.loadFromFile("Texturas/texturaBase_ficha.png");
    fondo.setTexture(&textura);

    Sprite ficha;
    ficha.setTexture(textura1);

    const float offsetX = 350.0f;
    const float offsetY = 15.0f;
    const float tamanoCasilla = 23.0f;

    while(DamasChinas.isOpen()){
        Event aevent;
        while(DamasChinas.pollEvent(aevent)){

            switch(aevent.type){
                case Event::Closed:
                    DamasChinas.close();
                    break;

                case Event::MouseMoved:

                    break;

                case Event::MouseButtonPressed:{
                    int x = Mouse::getPosition(DamasChinas).x;
                    int y = Mouse::getPosition(DamasChinas).y;

                    cout << x << endl;
                    cout << y << endl;

                }

                    break;
            }
        }

        DamasChinas.clear();
        DamasChinas.draw(fondo);

        for(int i = 0; i < 17; i++){
            int cont = 0;
            for(int j = 0; j < 25; j++){

                if(tablero[i][j] != -1){
                    float x = offsetX + (j) * tamanoCasilla;
                    float y = offsetY + (i) * 40;

                    if(tablero[i][j] == 1){
                        ficha.setColor(Color(0, 255, 0));
                        ficha.setPosition(x, y);
                        DamasChinas.draw(ficha);
                    }
                    if(tablero[i][j] == 2){
                        ficha.setColor(Color(128, 0, 128));
                        ficha.setPosition(x, y);
                        DamasChinas.draw(ficha);
                    }
                    if(tablero[i][j] == 3){
                        ficha.setColor(Color(255, 0, 0));
                        ficha.setPosition(x, y);
                        DamasChinas.draw(ficha);
                    }
                    if(tablero[i][j] == 4){
                        ficha.setColor(Color(255, 165, 0));
                        ficha.setPosition(x, y);
                        DamasChinas.draw(ficha);
                    }
                    if(tablero[i][j] == 5){
                        ficha.setColor(Color(255, 255, 0));
                        ficha.setPosition(x, y);
                        DamasChinas.draw(ficha);
                    }
                    if(tablero[i][j] == 6){
                        ficha.setColor(Color(0, 255, 255));
                        ficha.setPosition(x, y);
                        DamasChinas.draw(ficha);
                    }
                }else{
                    cont = cont + 1;
                }
            }
        }
        DamasChinas.display();
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
                if(modosJuego[1].isMouseOver(Jugar)){
                    Jugar.close();
                    RenderWindow window(VideoMode(1280, 720), "Ingreso de Usuario", Style::Default);
                    ventanaEntradaUsuario(window, font);
                    jugarDamasChinas(font);
                    Jugar.create(VideoMode(1280,720), "Jugar", Style::Default);
                }
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

    Music musica;
    musica.openFromFile("Audios/musicaMenu.ogg");


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

    musica.play();
    musica.setPlayingOffset(seconds(10.f));
    musica.setVolume(30);
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
