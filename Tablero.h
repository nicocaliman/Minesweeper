#pragma once
#include "Celda.h"

const int MAX_FILS = 50;
const int MAX_COLS = 50;

class Tablero
{
private:
    int filas, columnas;
    Celda celdas[MAX_FILS][MAX_COLS];
    //!funcion privada: inicializa las filas y las columnas a 0
    void setDefaults();
public:
    //filas y columnas a 0
    Tablero();
    //filas y columnas a los valores de los parametros, y acada una de las celdas del tablero a traves de su constructora Celda()
    Tablero(int fils, int cols);
    //destruye todas las celdas de la matriz, y pone el numero de filas y columnas
    void destruye();
    //numero de filas
    int num_filas() const;
    //numero de columnas
    int num_columnas() const;
    //true si la posicion [fila][columna] del tablero es valida
    bool es_valida(int fila, int columna) const;
    //celda contenida en la posicion [fila][columna]
    Celda dame_celda(int fila, int columna) const;
    //asignar el valor celda a la posicion [fila][columna]
    void poner_celda(int fila, int columna, const Celda& celda);
};
