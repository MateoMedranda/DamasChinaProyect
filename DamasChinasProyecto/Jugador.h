#ifndef Jugador_H
#define Jugador_H

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

    static void inicializarArchivo(const std::string& nombreArchivo);
    void guardarEnArchivo(const std::string& nombreArchivo) const;


    // Método estático para verificar si un usuario existe en el archivo
    static bool usuarioExisteEnArchivo(const string& usuario, const string& archivoNombre) {
        ifstream archivo(archivoNombre);
        if (!archivo.is_open()) {
            cout << "Error: No se pudo abrir el archivo " << archivoNombre << endl;
            return false;
        }
        string linea;
        while (getline(archivo, linea)) {
            size_t pos = linea.find(" || ");
            if (pos != string::npos) {
                string usuarioEnArchivo = linea.substr(pos + 4, linea.find(" || ", pos + 4) - (pos + 4));
                // Trim whitespace from usuarioEnArchivo
                usuarioEnArchivo.erase(0, usuarioEnArchivo.find_first_not_of(" \t\r\n"));
                usuarioEnArchivo.erase(usuarioEnArchivo.find_last_not_of(" \t\r\n") + 1);
                cout << "Comparando: '" << usuario << "' con '" << usuarioEnArchivo << "'" << endl;
                if (usuario == usuarioEnArchivo) {
                    cout << "Usuario encontrado!" << endl;
                    return true;
                }
            }
        }
        cout << "Usuario no encontrado." << endl;
        return false;
    }

    // Getters
    string getNombre() const { return nombre; }
    string getUsuario() const { return usuario; }

    // Métodos para incrementar puntaje y partidas
    void incrementarPuntaje(int puntos) { puntaje += puntos; }
    void incrementarPartidasJugadas() { partidasJugadas++; }
    void incrementarPartidasGanadas() { partidasGanadas++; }

};

// Inicializar archivo con encabezado
void Jugador::inicializarArchivo(const string& nombreArchivo) {
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
void Jugador::guardarEnArchivo(const std::string& nombreArchivo) const {
    ifstream archivoLectura(nombreArchivo);
    bool archivoVacio = archivoLectura.peek() == ifstream::traits_type::eof();
    archivoLectura.close();

    ofstream archivo(nombreArchivo, ios::app);
    if (archivo.is_open()) {
        if (archivoVacio) {
            // Escribir el encabezado si el archivo está vacío
            archivo << left << setw(20) << "Nombre" << " ||"
                    << setw(15) << " Usuario" << "  ||"
                    << setw(10) << " Puntaje" << "  ||"
                    << setw(20) << " Partidas Jugadas" << "  ||"
                    << setw(20) << " Partidas Ganadas" << endl;
            archivo << string(100, '-') << endl;
        }

        // Escribir la información del jugador
        archivo << left << setw(20) << nombre << " || "
                << setw(15) << usuario << " || "
                << setw(10) << puntaje << " || "
                << setw(20) << partidasJugadas << " || "
                << setw(20) << partidasGanadas << "\n";
        archivo.close();
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

#endif // Jugador_H
