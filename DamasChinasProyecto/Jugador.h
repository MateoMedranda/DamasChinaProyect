#ifndef Jugador_H
#define Jugador_H

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iomanip>
#include <vector>
#include <filesystem>

using namespace std;

class Jugador {
private:
    string usuario;
    int puntos;
    int movimientos;
    string estado;
    static int gameNumber;

public:
    // Constructor
    Jugador(string usuario)
        : usuario(std::move(usuario)), puntos(0), movimientos(0), estado("") {}

    // Validaciones
    bool validarUsuario() const {
        return !usuario.empty();
    }

    static void inicializarArchivo(const std::string& nombreArchivo);
    static string generarNombreArchivo();
    void actualizarEstado(const std::string& estado);
    static void guardarJugadoresEnArchivo(const vector<Jugador>& jugadores);
    static void determinarEstado(const vector<int>& puntajes, vector<Jugador>& jugadores);

    void setStatus(const string& newStatus) {
        estado = newStatus;
    }

    string getUsuario() const {
        return usuario;
    }

    int obtenerPuntos() const {
        return puntos;
    }

    string getStatus() const {
        return estado;
    }

    int getMovimientos() const {
        return movimientos;
    }

    void actualizarPuntos(int nuevoPuntaje) {
        puntos = nuevoPuntaje;
    }

    void actualizarMovimientos(int nuevoMovimiento) {
        movimientos = nuevoMovimiento;
    }
};

int Jugador::gameNumber = 1;

// Inicializar archivo con encabezado
void Jugador::inicializarArchivo(const string& nombreArchivo) {
    ofstream archivo(nombreArchivo);
    if (archivo.is_open()) {
        archivo << left << setw(15) << "Usuario" << " || "
                << setw(10) << "Puntaje" << " || "
                << setw(15) << "Movimientos" << " || "
                << setw(10) << "Estado" << endl;
        archivo << string(60, '-') << endl;
        archivo.close();
    } else {
        cerr << "Error al crear el archivo.\n";
    }
}

string Jugador::generarNombreArchivo() {
    string carpeta = "Partidas/";
    if (!filesystem::exists(carpeta)) {
        filesystem::create_directories(carpeta);
    }

    string nombreArchivo = carpeta + "Game" + to_string(gameNumber) + ".txt";
    gameNumber++;
    return nombreArchivo;
}

void Jugador::determinarEstado(const vector<int>& puntajes, vector<Jugador>& jugadores) {
    int maxPuntaje = *max_element(puntajes.begin(), puntajes.end());
    int minPuntaje = *min_element(puntajes.begin(), puntajes.end());

    for (auto& jugador : jugadores) {
        if (jugador.obtenerPuntos() == maxPuntaje && count(puntajes.begin(), puntajes.end(), maxPuntaje) == 1) {
            jugador.setStatus("Ganador");
        } else if (jugador.obtenerPuntos() == minPuntaje && count(puntajes.begin(), puntajes.end(), minPuntaje) == 1) {
            jugador.setStatus("Perdedor");
        } else {
            jugador.setStatus("Empate");
        }
    }
}

void Jugador::actualizarEstado(const std::string& estado) {
    this->estado = estado;
}

void Jugador::guardarJugadoresEnArchivo(const vector<Jugador>& jugadores) {
    string nombreArchivo = generarNombreArchivo();
    inicializarArchivo(nombreArchivo);

    ofstream archivo(nombreArchivo, ios::app);
    if (archivo.is_open()) {
        for (const auto& jugador : jugadores) {
            archivo << left << setw(15) << jugador.getUsuario() << " || "
                    << setw(10) << jugador.obtenerPuntos() << " || "
                    << setw(15) << jugador.getMovimientos() << " || "
                    << setw(10) << jugador.getStatus() << "\n";
        }
        archivo.close();
        cout << "Datos de la partida guardados en " << nombreArchivo << endl;
    } else {
        cerr << "Error al abrir el archivo " << nombreArchivo << ".\n";
    }
}

#endif // Jugador_H
