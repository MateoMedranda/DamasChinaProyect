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

static int gameNumber = 1;

class Jugador {
private:
    string usuario;
    int puntos;
    int movimientos;
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
    void actualizarEstado(const std::string& estado);
    static void guardarJugadoresEnArchivo(const vector<Jugador>& jugadores);
    static void determinarEstado(const vector<int>& puntajes, vector<Jugador>& jugadores);

    void setStatus(const string& newStatus) {
        estado = newStatus;
    }

    string getUsuario() const;
    int obtenerPuntos() const;
    string getStatus() const;

    void actualizarPuntos(int nuevoPuntaje) {
        puntos = nuevoPuntaje;
    }

    void actualizarMovimientos(int nuevoMovimiento){
        movimientos = nuevoMovimiento;
    }

    int getMovimientos(){
        return movimientos;
    }
};

string Jugador::getUsuario() const {
    return usuario;
}

int Jugador::obtenerPuntos() const {
    return puntos;
}

string Jugador::getStatus() const {
    return estado;
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

// Inicializar archivo con encabezado
void Jugador::inicializarArchivo(const string& nombreArchivo) {
    ifstream archivoExistente(nombreArchivo);
    if (!archivoExistente.good() || archivoExistente.peek() == ifstream::traits_type::eof()) {
        ofstream archivo(nombreArchivo);
        if (archivo.is_open()) {
            archivo << left << setw(15) << "Usuario" << " || "
                    << setw(10) << "Puntaje" << " || "
                    << setw(10) << "Estado" << endl;
            archivo << string(45, '-') << endl;
            archivo.close();
        } else {
            cerr << "Error al crear el archivo.\n";
        }
    }
}

// Guardar jugador en el archivo
void Jugador::guardarEnArchivo(const std::string& nombreArchivo) const {
    ofstream archivo(nombreArchivo, ios::app);
    if (archivo.is_open()) {
        archivo << left << setw(15) << usuario << " || "
                << setw(10) << puntos << " || "
                << setw(10) << estado << "\n";
        archivo.close();
    } else {
        cerr << "Error al abrir el archivo " << nombreArchivo << ".\n";
    }
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
    string nombreArchivoFinal = generarNombreArchivo();

    ifstream archivoExistente(nombreArchivoFinal);
    if (!archivoExistente.good()) {
        inicializarArchivo(nombreArchivoFinal);
    }

    for (const auto& jugador : jugadores) {
        jugador.guardarEnArchivo(nombreArchivoFinal);
    }
}

#endif // Jugador_H
