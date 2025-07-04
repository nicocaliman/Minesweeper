#pragma once
#include "Tablero.h"
#include "ListaPosiciones.h"

const int NUM_DIRS = 8;
const int NUM_COORD = 2;

const int DIRECCIONES[NUM_DIRS][NUM_COORD] = { 0,1, 1,1, 1,0, 1,-1, 0,-1, -1,-1, -1,0, -1,1 };

class Juego
{
private:
    Tablero tablero;
    int num_jugadas;
    bool mina_pisada;
    int num_minas;
    int num_descubiertas;
    //!funcion privada: actualizada la celda de la direccion [direccion]
    void actualizar_direccion(int fila, int columna, int direccion);
    //!funcion privada: actualiza las celdas vecinas a la posicion [fila][columna]
    void actualizar_vecinas(int fila, int columna);
    //!funcion privada: descubre las celdas vecinas a la posicion [fila][columna]
    void descubrir_vecinas(int fila, int columna, ListaPosiciones& lista_pos);
    //!funcion privada: descubre la celda vecina en la direccion [direccion]
    void descubrir_direccion(int fila, int columna, int direccion, ListaPosiciones& lista_pos);
    //!funcion privada: inicia los valores del juego
    void setDefaults();
public:
    //crear un juego, con el numero de jugadas, minas y celdas descubiertas a 0. mina_pisada = false + el tablero se inicializa mediante su constructora
    Juego();
    //lo mismo que la constructora anterior, pero el tablero se inicializa con los parametros
    Juego(int fils, int cols);
    //constructora para la v2, que crea un tablero de dimension fils*cols con numMinas colocadas de forma aleatoria
    Juego(int fils, int cols, int numMinas);
    //destruye el tablero, y el resto de atributos los pone al mismo valor que la constructora por defecto
    void destruye();
    //numero de jugadas
    int dame_num_jugadas() const;
    //numero de filas del tablero
    int dame_num_filas() const;
    //numero de columnas del tablero
    int dame_num_columnas() const;
    //numero de minas del tablero
    int dame_num_minas() const;
    //true si la la celda en la posicion [fila][columna] es una mina
    bool contiene_mina(int fila, int columna) const;
    //true si la celda en la posicion [fila][columna] esta descubierta
    bool esta_descubierta(int fila, int columna) const;
    //true si la celda en la posicion [fila][columna] esta marcada
    bool esta_marcada(int fila, int columna) const;
    //true si la celda en la posicion [fila][columna] esta vacia
    bool esta_vacia(int fila, int columna) const;
    //true si la celda en la posicion [fila][columna] contiene un numero
    bool contiene_numero(int fila, int columna) const;
    //true si todas las celdas del tablero, que no son minas estan estan descubiertas
    bool esta_completo() const;
    //true si alguna mina ha sido descubierta
    bool mina_explotada() const;
    //numero asociado a la celda en la posicion [fila][columna]
    int dame_numero(int fila, int columna) const;
    //si la posicion [i][j] es valida, no esta descubierta y no contiene una mina, coloca una mina en esa posicion y actualiza las poisiciones vecinas
    bool poner_mina(int fila, int columna);
    //si la posicion [fila][columna] es valida, si la celda esta oculta, marcar celda. Si la celda esta marcada, la desmarca
    void marcar_desmarcar(int fila, int columna);
    //si la posicion [fila][columna] es valida, 
    void ocultar_celda(int fila, int columna);
    //intenta descubrir la celda colocada en la posicion [fila][columna] 
    void juega(int fila, int columna, ListaPosiciones& lista_pos);
    //!funcion publica: inicializa los valores del juego
    void inicializa(int f, int c, int numMinas);
    //!funcion publica: descubre la celda en la posicion fila columna
    void descubrir_celda(int fila, int columna);
    bool es_valida(int fila, int columna);
};

