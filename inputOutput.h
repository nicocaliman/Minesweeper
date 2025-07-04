
#pragma once

#include "colors.h"
#include <fstream>
#include "Juego.h"

const int N_HUECOS = 2; // huecos a dejar en el formato de las celdas.

using namespace std;

//muestra la cabecera del juego
void mostrar_cabecera();
//solicita al usuario que introduzca una fila y una columna
void pedir_pos(int& fila, int& columna);
void mostrar_resultado(const Juego& juego);
void mostrar_juego_consola(const Juego& juego);
void cargar_juego(istream& archivo, Juego& juego);
string pedir_fichero();
void pedirDimensiones(int& filas, int& columnas);
istream& operator>>(istream& in, Juego& juego);
