#ifndef Jugadores_H
#define Jugadores_H

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <iomanip>

using namespace std;

class Jugador {
private:
    string nombre;
    string usuario;
    int puntaje;
    int partidasJugadas;
    int partidasGanadas;

public:
    // Constructor
    Jugador(string nombre, string usuario)
        : nombre(std::move(nombre)), usuario(std::move(usuario)), puntaje(0), partidasJugadas(0), partidasGanadas(0) {}

    // Validaciones
    bool validarNombre() const {
        return !nombre.empty() && all_of(nombre.begin(), nombre.end(), [](char c) { return isalpha(c) || isspace(c); });
    }

    bool validarUsuario() const {
        return !usuario.empty();
    }

    static bool usuarioExisteEnArchivo(const string& usuario, const string& nombreArchivo) {
        ifstream archivo(nombreArchivo);
        string line;
        if (archivo.is_open()) {
            while (getline(archivo, line)) {
                if (line.find(usuario) != string::npos) {
                    archivo.close();
                    return true;
                }
            }
            archivo.close();
        }
        return false;
    }

    // Getters
    string getNombre() const { return nombre; }
    string getUsuario() const { return usuario; }

    // Métodos para incrementar puntaje y partidas
    void incrementarPuntaje(int puntos) { puntaje += puntos; }
    void incrementarPartidasJugadas() { partidasJugadas++; }
    void incrementarPartidasGanadas() { partidasGanadas++; }

    // Almacenamiento en archivo
    void guardarEnArchivo(ofstream& archivo) const {
        archivo << left << setw(20) << nombre << " || "
                << setw(15) << usuario << " || "
                << setw(10) << puntaje << " || "
                << setw(20) << partidasJugadas << " || "
                << setw(20) << partidasGanadas << "\n";
    }
};

// Inicializar archivo con encabezado
void inicializarArchivo(const string& nombreArchivo) {
    ifstream archivoExistente(nombreArchivo);
    bool archivoVacio = !archivoExistente.good() || archivoExistente.peek() == ifstream::traits_type::eof();
    archivoExistente.close();

    if (archivoVacio) {
        ofstream archivo(nombreArchivo, ios::out | ios::app);
        if (archivo.is_open()) {
            archivo << left << setw(20) << "Nombre" << " ||"
                    << setw(15) << " Usuario" << "  ||"
                    << setw(10) << " Puntaje" << "  ||"
                    << setw(20) << " Partidas Jugadas" << "  ||"
                    << setw(20) << " Partidas Ganadas" << endl;
            archivo << string(100, '-') << endl;
            archivo.close();
        } else {
            cout << "Error al crear el archivo.\n";
        }
    }
}

// Guardar jugadores en el archivo
void guardarJugadoresEnArchivo(const list<Jugador>& jugadores, const string& nombreArchivo) {
    ofstream archivo(nombreArchivo, ios::app);
    if (archivo.is_open()) {
        for (const auto& jugador : jugadores) {
            jugador.guardarEnArchivo(archivo);
        }
        archivo.close();
        cout << "Datos guardados en " << nombreArchivo << " con éxito.\n";
    } else {
        cout << "Error al abrir el archivo.\n";
    }
}

// Ingresar jugadores
void ingresarJugadores(list<Jugador>& listaJugadores, const string& nombreArchivo) {
    string nombre, usuario;
    int cantJugadores = 0;

    while (true) {
        while (true) {
            cout << "Ingrese el nombre del jugador (presione Enter para finalizar): ";
            getline(cin, nombre);
            if (nombre.empty()) {
                if (cantJugadores < 2) {
                    cerr << "Debe haber al menos 2 jugadores para comenzar el juego. Ingrese un jugador.\n";
                    continue;
                }
                return;
            }

            Jugador jugadorTemp(nombre, "");
            if (jugadorTemp.validarNombre()) {
                break;
            } else {
                cerr << "El nombre solo debe contener letras. Intentelo de nuevo.\n";
            }
        }

        while (true) {
            cout << "Ingrese el usuario: ";
            getline(cin, usuario);

            // Validación de existencia del usuario en la lista de jugadores actual
            bool usuarioExistenteEnLista = any_of(listaJugadores.begin(), listaJugadores.end(),
                [&usuario](const Jugador& j) { return j.getUsuario() == usuario; });

            // Validación de existencia del usuario en el archivo
            if (usuarioExistenteEnLista || Jugador::usuarioExisteEnArchivo(usuario, nombreArchivo)) {
                cerr << "El usuario ya esta registrado. Intentelo de nuevo.\n";
                continue;
            }

            Jugador jugadorTemp("", usuario);
            if (jugadorTemp.validarUsuario()) {
                break;
            } else {
                cerr << "El usuario no puede estar vacio. Intentelo de nuevo.\n";
            }
        }

        Jugador jugador(nombre, usuario);
        listaJugadores.push_back(jugador);
        cantJugadores++;

        if (cantJugadores >= 2) {
            string continuar;
            cout << "Desea ingresar otro jugador? (s/n): ";
            getline(cin, continuar);
            if (continuar != "s") break;
        }
    }
}

// Controlar turnos
void controlarTurnos(list<Jugador>& listaJugadores) {
    auto it = listaJugadores.begin();
    while (true) {
        cout << "Turno de: " << it->getUsuario() <<"\n";
        it++;
        if (it == listaJugadores.end()) {
            it = listaJugadores.begin();
        }

        string continuar;
        cout << "Desea continuar? (s/n): ";
        cin >> continuar;
        cin.ignore();
        if (continuar != "s") break;
    }
}

#endif // Jugadores_H


/* METODO MAIN PARA SU EJECUCION

int main() {
    list<Jugador> listaJugadores;
    string nombreArchivo = "jugadores.txt";

    inicializarArchivo(nombreArchivo);
    ingresarJugadores(listaJugadores, nombreArchivo);
    guardarJugadoresEnArchivo(listaJugadores, nombreArchivo);
    controlarTurnos(listaJugadores);

    return 0;
}
*/
