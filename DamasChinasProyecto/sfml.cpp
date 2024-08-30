#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <string>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

#include "Boton.h"
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

int generarTurnosAleatorios(int n){

    int turno;
    if(n== 1){
        for(int i=0; i<2;i++){
            srand(time(0));
            turno = rand() % 2 + 1;
        }
    }else{
        for(int i=0; i<6;i++){
            srand(time(0));
            turno = rand() % 6 + 1;
        }
    }

    return turno;
}

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
        boton.setTextColor(Color::Yellow);
    } else {
        boton.setBackColor(Color(255, 255, 255, 0));
        boton.setTextColor(Color::White);
    }
}

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

vector<string> ventanaEntradaUsuario(RenderWindow& parentWindow, Font& font, int numJugadores) {
    int windowHeight = 200 + 70 * numJugadores;
    RenderWindow window(VideoMode(400, windowHeight), "Jugadores", Style::Close);
    VideoMode desktopMode = VideoMode::getDesktopMode();
    window.setPosition(Vector2i((desktopMode.width - window.getSize().x) / 2,
                                (desktopMode.height - window.getSize().y) / 2));

    Texture backgroundTexture;
    backgroundTexture.loadFromFile("Texturas/usuarioLogin.png");
    RectangleShape background(Vector2f(400, windowHeight));
    background.setTexture(&backgroundTexture);

    Text titulo("Ingresar Jugadores", font, 24);
    titulo.setFillColor(Color::White);
    titulo.setStyle(Text::Bold);
    titulo.setPosition(75, 20);

    vector<RectangleShape> usuarioBoxes(numJugadores);
    vector<Text> usuarioInputs(numJugadores, Text("", font, 24));
    vector<Text> usuarioLabels(numJugadores, Text("", font, 20));

    for (int i = 0; i < numJugadores; ++i) {
        usuarioLabels[i].setString("Jugador " + to_string(i + 1) + ":");
        usuarioLabels[i].setPosition(50, 70 + i * 70);
        usuarioLabels[i].setFillColor(Color::White);

        usuarioBoxes[i].setSize(Vector2f(300, 40));
        usuarioBoxes[i].setPosition(50, 100 + i * 70);
        usuarioBoxes[i].setFillColor(Color::White);
        usuarioBoxes[i].setOutlineColor(Color::Black);
        usuarioBoxes[i].setOutlineThickness(1);

        usuarioInputs[i].setPosition(55, 105 + i * 70);
        usuarioInputs[i].setFillColor(Color::Black);
    }

    RectangleShape continuarBox(Vector2f(150, 40));
    continuarBox.setPosition(125, 100 + numJugadores * 70 + 10);
    continuarBox.setFillColor(Color(50, 205, 50));

    Text continuarButton("Jugar", font, 24);
    continuarButton.setPosition(170, 105 + numJugadores * 70 + 10);
    continuarButton.setFillColor(Color::White);

    vector<string> usuarioStr(numJugadores, "");
    int cajaActiva = -1;

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                return {};
            }

            if (event.type == Event::TextEntered && cajaActiva != -1) {
                if ((event.text.unicode >= 'A' && event.text.unicode <= 'Z') ||
                    (event.text.unicode >= 'a' && event.text.unicode <= 'z') ||
                    (event.text.unicode >= '0' && event.text.unicode <= '9') ||
                    event.text.unicode == '\b') {
                    if (event.text.unicode != '\b') {
                        usuarioStr[cajaActiva] += static_cast<char>(event.text.unicode);
                    } else if (!usuarioStr[cajaActiva].empty()) {
                        usuarioStr[cajaActiva].pop_back();
                    }
                    usuarioInputs[cajaActiva].setString(usuarioStr[cajaActiva]);
                }
            }

            if (event.type == Event::MouseButtonPressed) {
                for (int i = 0; i < numJugadores; ++i) {
                    if (usuarioBoxes[i].getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                        cajaActiva = i;
                        break;
                    }
                }
                if (continuarBox.getGlobalBounds().contains(Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    bool todasCompletas = true;
                    for (int i = 0; i < numJugadores; ++i) {
                        if (usuarioStr[i].empty()) {
                            todasCompletas = false;
                            break;
                        }
                    }

                    if (todasCompletas) {
                        window.close();

                        string gameName = Jugador::generarNombreArchivo();
                        Jugador::inicializarArchivo(gameName);

                        cout << "Nuevo juego iniciado: " << gameName << endl;
                        cout << "Jugadores: ";
                        for (const auto& jugador : usuarioStr) {
                            cout << jugador << " ";
                        }
                        cout << endl;

                        //Guardo el nombre del jugador
                        for (const auto& jugador : usuarioStr) {
                            Jugador nuevoJugador(jugador);
                            nuevoJugador.guardarEnArchivo(gameName);
                        }


                        return usuarioStr;
                    } else {
                        cout << "Debe completar todas las cajas de texto antes de continuar" << endl;
                    }
                }
            }
        }

        window.clear(Color::Black);
        window.draw(background);
        window.draw(titulo);
        for (int i = 0; i < numJugadores; ++i) {
            window.draw(usuarioLabels[i]);
            window.draw(usuarioBoxes[i]);
            window.draw(usuarioInputs[i]);
        }
        window.draw(continuarBox);
        window.draw(continuarButton);
        window.display();
    }

    return {};
}

void jugarDamas(Font &font, vector<string> jugadores){

    SoundBuffer moverBuffer, comerBuffer,damaBuffer;
    Sound sonidoMover, sonidoComer, sonidoDama;
    /*
    Font cipher;
    cipher.loadFromFile("Fuentes/CipherFontA.ttf");

    Text cifrados;
    cifrados.setFont(cipher);
    cifrados.setCharacterSize(20);
    cifrados.setFillColor(Color::Black);
    cifrados.setString("Hola mundo");
    cifrados.setPosition(10,10);
    */

    Text texto[2];
    for(int i = 0; i<2; i++){
        texto[i].setCharacterSize(30);
        texto[i].setFont(font);
        texto[i].setString(jugadores[i]);
        texto[i].setPosition(50+(i*944), 226);
        texto[i].setColor(Color::Cyan);
    }

    moverBuffer.loadFromFile("Audios/moverPieza.ogg");
    sonidoMover.setBuffer(moverBuffer);
    sonidoMover.setVolume(100);
    comerBuffer.loadFromFile("Audios/comerPieza.ogg");
    sonidoComer.setBuffer(comerBuffer);
    sonidoComer.setVolume(100);
    damaBuffer.loadFromFile("Audios/obtenerDama.wav");
    sonidoDama.setBuffer(damaBuffer);
    sonidoDama.setVolume(15);

    RenderWindow Damas(VideoMode(1200,675),"Damas");
    Damas.setPosition(Vector2i(0,0));

    int tablero[8][8];
    crearMatrizDamas(tablero);

    RectangleShape fondo;
    Texture textura, textura1, textura2, textura3, textura4;
    fondo.setSize(Vector2f(1200,675));
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

    const float offsetX = 260.0f;
    const float offsetY = 0.0f;
    const float tamanoCasilla = 85.0f;

    bool fichaSeleccionada = false;
    int fichaSeleccionadaX = -1;
    int fichaSeleccionadaY = -1;
    int turno = generarTurnosAleatorios(1);

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

                        cout << x << endl;
                        cout << y << endl;

                        int i = (y-offsetY)/tamanoCasilla;
                        int j = (x-offsetX)/tamanoCasilla;

                        cout << "i: " << i << "j: " << j << endl;


                        if((i>=0) && (i<8) && (j>=0) && (j<8)){
                            if(((tablero[i][j] == 1) || (tablero[i][j] == 2) || (tablero[i][j] == 3) || (tablero[i][j] == 4)) && (tablero[i][j] == turno || tablero[i][j] == turno+2)){

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
                                            sonidoMover.play();
                                            if(turno == 1){
                                                turno = 2;
                                            }else{
                                                turno = 1;
                                            }

                                            if(newY == 0 && temp == 2){
                                                tablero[newY][newX] = 4;
                                                sonidoDama.play();
                                            }
                                            if(newY == 7 && temp == 1){
                                                tablero[newY][newX] = 3;
                                                sonidoDama.play();
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
                                            sonidoMover.play();
                                            sonidoComer.play();
                                            if(turno == 1){
                                                turno = 2;
                                            }else{
                                                turno = 1;
                                            }

                                            if(newY == 0 && temp == 2){
                                                tablero[newY][newX] = 4;
                                                sonidoDama.play();
                                            }
                                            if(newY == 7 && temp == 1){
                                                tablero[newY][newX] = 3;
                                                sonidoDama.play();
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
        for(int i = 0; i<2; i++){
            Damas.draw(texto[i]);
        }

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

void jugarDamasChinas(Font &font, int n){

    SoundBuffer moverBuffer, saltarBuffer;
    Sound sonidoMover, sonidoSaltar;

    moverBuffer.loadFromFile("Audios/moverPieza.ogg");
    sonidoMover.setBuffer(moverBuffer);
    sonidoMover.setVolume(100);
    saltarBuffer.loadFromFile("Audios/comerPieza.ogg");
    sonidoSaltar.setBuffer(saltarBuffer);
    sonidoSaltar.setVolume(100);

    int tablero[FILAS][COLUMNAS];
    crearMatrizNJugadoresDamas(tablero,n);

    RenderWindow DamasChinas(VideoMode(1200,675),"Damas Chinas");
    DamasChinas.setPosition(Vector2i(0,0));

    RectangleShape fondo;
    Texture textura, textura1, textura2;
    fondo.setSize(Vector2f(1200,675));
    textura.loadFromFile("Texturas/tableroDamasChinas.png");
    textura1.loadFromFile("Texturas/texturaBase_ficha.png");
    textura2.loadFromFile("Texturas/texturaVacio.png");
    fondo.setTexture(&textura);

    Sprite ficha, espacio;
    ficha.setTexture(textura1);
    espacio.setTexture(textura2);

    CircleShape movimiento(10.0f); // Tamaño del círculo para mostrar los movimientos
    movimiento.setFillColor(Color(255,100 , 0, 150)); // Color verde transparente

    const float offsetX = 250.0f;
    const float offsetY = 45.0f;
    const float tamanoCasilla = 28.0f;

    bool fichaSeleccionada = false;
    int fichaSeleccionadaX = -1;
    int fichaSeleccionadaY = -1;

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
                    int temp;

                    int x = Mouse::getPosition(DamasChinas).x;
                    int y = Mouse::getPosition(DamasChinas).y;

                    cout << x << endl;
                    cout << y << endl;

                    int i = (y-offsetY)/34;
                    int j = (x-offsetX)/tamanoCasilla;

                    cout << i << endl;
                    cout << j << endl;

                    if((i>=0) && (i<17) && (j>=0) && (j<25)){
                            if((tablero[i][j] == 1) || (tablero[i][j] == 2) || (tablero[i][j] == 3) || (tablero[i][j] == 4 || tablero[i][j] == 5 || tablero[i][j] == 6 )){

                                if (fichaSeleccionada) {
                                    fichaSeleccionada = false; // Deselecciona la ficha
                                } else {
                                    fichaSeleccionada = true; // Selecciona una ficha
                                    fichaSeleccionadaX = j;
                                    fichaSeleccionadaY = i;
                                }

                            }else if(tablero[i][j] == 0 && fichaSeleccionada){

                                int dx[6];
                                int dy[6];

                                if(tablero[fichaSeleccionadaY][fichaSeleccionadaX] != 0){
                                    dx[0] = -1;
                                    dx[1] = 1;
                                    dx[2] = -2;
                                    dx[3] = 2;
                                    dx[4] = -1;
                                    dx[5] = 1;
                                    dy[0] = -1;
                                    dy[1] = -1;
                                    dy[2] = 0;
                                    dy[3] = 0;
                                    dy[4] = 1;
                                    dy[5] = 1;
                                }

                                for (int k = 0; k < 6; ++k) {
                                    int newX = fichaSeleccionadaX + dx[k];
                                    int newY = fichaSeleccionadaY + dy[k];

                                    if (newX >= 0 && newX < 25 && newY >= 0 && newY < 17 && (tablero[newY][newX] == 0)) {
                                        cout << "fichax: " << fichaSeleccionadaX << "fichaY: " << fichaSeleccionadaY << endl;
                                        cout << "x: " << newX << "y: " << newY << endl;
                                        if(newX == j && newY == i){
                                            temp = tablero[fichaSeleccionadaY][fichaSeleccionadaX];
                                            tablero[fichaSeleccionadaY][fichaSeleccionadaX] = 0;
                                            tablero[newY][newX] = temp;
                                            sonidoMover.play();
                                        }
                                    }
                                    if (newX >= 0 && newX < 25 && newY >= 0 && newY < 17 && (tablero[newY][newX] != 0) ){
                                        int antx = newX , anty = newY;
                                        newX = newX + dx[k];
                                        newY = newY + dy[k];

                                        if(newX == j && newY == i && tablero[newY][newX] == 0){
                                            temp = tablero[fichaSeleccionadaY][fichaSeleccionadaX];
                                            tablero[fichaSeleccionadaY][fichaSeleccionadaX] = 0;
                                            tablero[newY][newX] = temp;
                                            sonidoSaltar.play();
                                            sonidoMover.play();
                                        }

                                    }
                                }
                                fichaSeleccionada = false;
                            }
                        }

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
                    float y = offsetY + (i) * 34;

                    if(tablero[i][j] == 0){
                        espacio.setPosition(x,y);
                        DamasChinas.draw(espacio);
                    }

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

        if (fichaSeleccionada) {
            int dx[6];
            int dy[6];

            if(tablero[fichaSeleccionadaY][fichaSeleccionadaX] != 0){
                dx[0] = -1;
                dx[1] = 1;
                dx[2] = -2;
                dx[3] = 2;
                dx[4] = -1;
                dx[5] = 1;
                dy[0] = -1;
                dy[1] = -1;
                dy[2] = 0;
                dy[3] = 0;
                dy[4] = 1;
                dy[5] = 1;
            }

            for (int i = 0; i < 6; ++i) {
                int newX = fichaSeleccionadaX + dx[i];
                int newY = fichaSeleccionadaY + dy[i];

                if (newX >= 0 && newX < 25 && newY >= 0 && newY < 17 && (tablero[newY][newX] == 0)) {
                    movimiento.setPosition(offsetX + newX*tamanoCasilla + (tamanoCasilla/2 - movimiento.getRadius()) + 3,offsetY + newY*34 + (34/ 2 - movimiento.getRadius()));
                    DamasChinas.draw(movimiento);
                }
                if (newX >= 0 && newX < 25 && newY >= 0 && newY < 17 && (tablero[newY][newX] != 0)) {
                    newX = newX+ dx[i];
                    newY = newY + dy[i];
                    if(tablero[newY][newX] == 0){
                        movimiento.setPosition(offsetX + newX*tamanoCasilla + (tamanoCasilla/2 - movimiento.getRadius())+3,offsetY + newY*34 + (34/ 2 - movimiento.getRadius()));
                        DamasChinas.draw(movimiento);
                    }
                }
            }

        }

        DamasChinas.display();
    }

}

void abrirJugar(RenderWindow &Jugar, Font &font, Boton modosJuego[]){
    RectangleShape fondo;
    Texture texturaModos;
    fondo.setSize(Vector2f(1200,675));
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
                bool cerrado = false;
                if(modosJuego[1].isMouseOver(Jugar)){

                    vector<string> jugadores = ventanaEntradaUsuario(Jugar, font, 2);
                    Jugar.close();
                    if (!jugadores.empty()) {
                        jugarDamasChinas(font, 2);
                        cerrado = true;
                    }
                }
                if(modosJuego[2].isMouseOver(Jugar)){
                    //Jugar.close();
                    vector<string> jugadores = ventanaEntradaUsuario(Jugar, font, 3);
                    if (!jugadores.empty()) {
                        jugarDamasChinas(font, 3);
                        cerrado = true;
                    }
                }
                if(modosJuego[3].isMouseOver(Jugar)){
                    //Jugar.close();
                    vector<string> jugadores = ventanaEntradaUsuario(Jugar, font, 4);
                    if (!jugadores.empty()) {
                        jugarDamasChinas(font, 4);
                        cerrado = true;
                    }
                }
                if(modosJuego[4].isMouseOver(Jugar)){
                    //Jugar.close();
                    vector<string> jugadores = ventanaEntradaUsuario(Jugar, font, 5);
                    if (!jugadores.empty()) {
                        jugarDamasChinas(font, 5);
                        cerrado = true;
                    }
                }
                if(modosJuego[5].isMouseOver(Jugar)){
                    //Jugar.close();
                    vector<string> jugadores = ventanaEntradaUsuario(Jugar, font, 6);
                    if (!jugadores.empty()) {
                        jugarDamasChinas(font, 6);
                        cerrado = true;
                    }

                }
                if(modosJuego[7].isMouseOver(Jugar)){
                    //Jugar.close();
                    vector<string> jugadores = ventanaEntradaUsuario(Jugar, font, 2);
                    if (!jugadores.empty()) {
                        jugarDamas(font, jugadores);
                        cerrado = true;
                    }

                }
                if(cerrado){
                    Jugar.create(VideoMode(1200,675), "Jugar", Style::Default);
                    Jugar.setPosition(Vector2i(0,0));
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

void abrirTutorial(RenderWindow &Opcion, Font &font, Boton &siguiente, Boton &anterior){
    RectangleShape fondo;
    Texture texturaTutorial;
    string tutorial = "tutorial_";
    stringstream ss;
    ss << tutorial << indexTutorial;
    string archivo = ss.str();
    Event aevent;

    fondo.setSize(Vector2f(1200,675));
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
                if(anterior.isMouseOver(Opcion)){
                    anterior.setBackColor(Color::Black);
                }else{
                    anterior.setBackColor(Color(255, 255, 255, 0));
                }
            }
            break;
            case Event::MouseButtonPressed:{
                if(siguiente.isMouseOver(Opcion) && (indexTutorial != 12)){
                    indexTutorial +=1;
                }
                if(anterior.isMouseOver(Opcion) && (indexTutorial != 1)){
                    indexTutorial -=1;
                }
            }
            break;
        }

    }
    Opcion.clear();
    Opcion.draw(fondo);
    anterior.drawTo(Opcion);
    siguiente.drawTo(Opcion);
}

void iniciarJuego(){
    RenderWindow MENU(VideoMode(1200,675), "Menu Principal", Style::Default);

    MENU.setPosition(Vector2i(0,0));

    Music musica;
    musica.openFromFile("Audios/musicaMenu.ogg");


    RectangleShape fondo, fondoC;

    fondo.setSize(Vector2f(1200,675));
    fondoC.setSize(Vector2f(1200,675));
    Texture texturaPrincipal, texturaCreditos;
    texturaCreditos.loadFromFile("Texturas/Creditos.png");

    texturaPrincipal.loadFromFile("Texturas/fondoMenuPrincipal.png");
    fondo.setTexture(&texturaPrincipal);
    fondoC.setTexture(&texturaCreditos);

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

    Boton siguiente = Boton("Siguiente",{310,60},45,Color(255, 255, 255, 0),Color::White);
    siguiente.setPosition({850, 600});
    siguiente.setFont(font);

    Boton anterior = Boton("Anterior",{310,60},45,Color(255, 255, 255, 0),Color::White);
    anterior.setPosition({850, 540});
    anterior.setFont(font);

    posicion = 125;
    Boton modosJuego[8];
    string textoBotonesJugar[] = {"1 Jugador", "2 Jugadores", "3 Jugadores", "4 Jugadores", "5 Jugadores", "6 Jugadores", "1 Jugador", "2 Jugadores"};

    for (int i = 0; i<6; i++){
        modosJuego[i] = Boton(textoBotonesJugar[i],{325,55},35,Color(255, 255, 255, 0),Color::White);
        modosJuego[i].setPosition({100,posicion + i*55});
        modosJuego[i].setFont(font);
    }

    for (int i = 6; i<8; i++){
        modosJuego[i] = Boton(textoBotonesJugar[i],{325,55},40,Color(255, 255, 255, 0),Color::White);
    }

    modosJuego[6].setPosition({100,560});
    modosJuego[6].setFont(font);

    modosJuego[7].setPosition({550,560});
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
    musica.setLoop(true);
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

                        if(botones[0].isMouseOver(MENU)){
                            MENU.close();
                            RenderWindow Jugar(VideoMode(1200,675),"Damas Chinas");
                            Jugar.setPosition(Vector2i(0,0));
                            while(Jugar.isOpen()){
                                abrirJugar(Jugar, font, modosJuego);
                                Jugar.display();
                            }
                        }

                        if(botones[1].isMouseOver(MENU)){
                            MENU.close();
                            RenderWindow Opcion(VideoMode(1200,675), "¿Como Jugar?");
                            Opcion.setPosition(Vector2i(0,0));
                            while(Opcion.isOpen()){
                                abrirTutorial(Opcion, font, siguiente, anterior);
                                Opcion.display();
                            }
                        }

                        if(botones[2].isMouseOver(MENU)){
                            MENU.close();
                            RenderWindow Creditos(VideoMode(1200,675),"Creditos");
                            Creditos.setPosition(Vector2i(0,0));
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
                                Creditos.clear();
                                Creditos.draw(fondoC);
                                Creditos.display();
                            }
                        }
                        MENU.create(VideoMode(1200,675), "Menu Principal", Style::Default);
                        MENU.setPosition(Vector2i(0,0));

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
