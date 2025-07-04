
#include "tablero.h"

void Tablero::setDefaults()
{
    filas = columnas = 0;
}

Tablero::Tablero()
{
    setDefaults();   //filas y columnas del tablero a 0
}

Tablero::Tablero(int fils, int cols)
{
    //filas y columnas del tablero a los valores de los parametros
    filas = fils;
    columnas = cols;

    //recorrer filas de tablero
    for (int i = 0; i < num_filas(); i++)
    {
        //recorrer columnas del tablero
        for (int j = 0; j < num_columnas(); j++)
        {
            celdas[i][j] = Celda();   //inicializar celda en posicion [i][j]
        }
    }
}

void Tablero::destruye()
{
    //recorrer filas de tablero
    for (int i = 0; i < num_filas(); i++)
    {
        //recorrer columnas del tablero
        for (int j = 0; j < num_columnas(); j++)
        {
            celdas[i][j].destruye();   //destruye la celda en la posicion [i][j]
        }
    }

    //poner el numero de filas y columnas a 0
    setDefaults();
}

int Tablero::num_filas() const
{
    return filas; //filas del tablero
}

int Tablero::num_columnas() const
{
    return columnas;  //columnas del tablero
}

bool Tablero::es_valida(int fila, int columna) const
{
    return (fila >= 0 && fila < num_filas()) &&
        (columna >= 0 && columna < num_columnas());   //true si fila ∈ [0,numFilas) && columnma ∈ [0,numColumnas)
}

Celda Tablero::dame_celda(int fila, int columna) const
{
    return celdas[fila][columna]; //celda en la posicion [fila][columna]
}

void Tablero::poner_celda(int fila, int columna, const Celda& celda)
{
    celdas[fila][columna] = celda; //poner celda en posicion [fila][columna]
}
