#ifndef Jugador_H
#define Jugador_H

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iomanip>
#include <filesystem>

using namespace std;

static int gameNumber = 1;

class Jugador {
private:
    string usuario;
    int puntos;
    string estado;

public:
    // Constructor
    Jugador(string usuario)
        : usuario(std::move(usuario)), puntos(0), estado("") {}

    // Validaciones
    bool validarUsuario() const {
        return !usuario.empty();
    }

    static void inicializarArchivo(const std::string& nombreArchivo);
    void guardarEnArchivo(const std::string& nombreArchivo) const;
    static string generarNombreArchivo();

    string getUsuario() const {
        return usuario;
    }

    void setStatus(const string& newStatus) {
        estado = newStatus;
    }

    void agregarPuntos(int puntosGanados) {
        puntos += puntosGanados;
    }

    int obtenerPuntos() const {
        return puntos;
    }
};

// Metodo para generar el nombre del archivo de la partida
string Jugador::generarNombreArchivo() {
    string carpeta = "Partidas/";
    if (!filesystem::exists(carpeta)) {
        filesystem::create_directories(carpeta);
    }

    string nombreArchivo = carpeta + "Game" + to_string(gameNumber) + ".txt";
    cout << "Generando archivo: " << nombreArchivo << endl; // Depuraci�n
    gameNumber++;
    return nombreArchivo;
}

// Inicializar archivo con encabezado
void Jugador::inicializarArchivo(const string& nombreArchivo) {
    ifstream fileCheck(nombreArchivo);
    if (!fileCheck.good()) {  // El archivo no existe, por lo tanto, inicializamos
        ofstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            archivo << left << setw(15) << "Usuario" << " || "
                    << setw(10) << "Puntaje" << " || "
                    << setw(10) << "Estado" << endl;
            archivo << string(45, '-') << endl;
            archivo.close();
        } else {
            cout << "Error al crear el archivo.\n";
        }
    }
}

// Guardar jugadores en el archivo
void Jugador::guardarEnArchivo(const std::string& nombreArchivo) const {
    ofstream archivo(nombreArchivo, ios::app);
    if (archivo.is_open()) {
        archivo << left << setw(15) << usuario << " || "
                << setw(10) << puntos << " || "
                << setw(10) << estado << "\n";
        archivo.close();
        cout << "Jugador " << usuario << " guardado en el archivo " << nombreArchivo << endl; // Depuraci�n
    } else {
        cout << "Error al abrir el archivo " << nombreArchivo << ".\n";
    }
}

// Ingresar jugadores
void ingresarJugadores(list<Jugador>& listaJugadores) {
    string usuario;
    int cantJugadores = 0;

    while (true) {
        cout << "Ingrese el usuario (presione Enter para finalizar): ";
        getline(cin, usuario);
        if (usuario.empty()) {
            if (cantJugadores < 2) {
                cerr << "Debe haber al menos 2 jugadores para comenzar el juego. Ingrese un jugador.\n";
                continue;
            }
            return;
        }

        Jugador jugador(usuario);
        if (jugador.validarUsuario()) {
            listaJugadores.push_back(jugador);
            cantJugadores++;
        } else {
            cerr << "El usuario no puede estar vac�o. Intentelo de nuevo.\n";
        }

        if (cantJugadores >= 2) {
            string continuar;
            cout << "�Desea ingresar otro jugador? (s/n): ";
            getline(cin, continuar);
            if (continuar != "s") break;
        }
    }
}

// Controlar turnos y guardar resultados
void controlarTurnosYGuardar(list<Jugador>& listaJugadores) {
    string fileName = Jugador::generarNombreArchivo();
    Jugador::inicializarArchivo(fileName);

    for (auto& jugador : listaJugadores) {
        jugador.guardarEnArchivo(fileName);
    }
}

void procesarMovimiento(Jugador& jugador, bool esPrimeraComida, bool esReina, bool comioReina) {
    if (esPrimeraComida) {
        jugador.agregarPuntos(5);  // 5 puntos por la primera comida
    }

    if (comioReina) {
        jugador.agregarPuntos(10); // 10 puntos por comer una reina
    } else if (esReina) {
        jugador.agregarPuntos(7);  // 7 puntos por una reina que come
    } else {
        jugador.agregarPuntos(2);  // 2 puntos por una comida normal
    }
}

#endif // Jugador_H
