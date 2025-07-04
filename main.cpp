
// Versi�n jugable en internet: https://minesweeper.online/es/
// Alberto de la Encina 
// Puri Arenas

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include "colors.h"

using namespace std;

#include "ListaUndo.h"
#include "GestorJuegos.h"

bool juega(Juego& juego, int fila, int columna, ListaUndo& lista_undo);
int obtenerOpcion(int fila, int columna);
Juego crear_juego_aleatorio(int& pos, GestorJuegos& GP);
Juego crear_o_seleccionar_juego(GestorJuegos& GP, int& pos);

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    srand(time(NULL));  // (recomendado para aleatoriedad)

    //cabecera
    mostrar_cabecera();

    GestorJuegos GP;
    Juego juego;
    ListaUndo listaUndo;
    int fila, columna, pos;
    bool continuarJuego = true;

    //si el archivo existe
    if (GP.cargar_juegos())
    {
        juego = crear_o_seleccionar_juego(GP, pos);
    }
    //si no existe
    else
    {
        cout << RED << "Error en la apertura del fichero de juegos\n" << RESET;
        cout << GREEN << "Se genera un juego aleatorio...\n" << RESET;
        juego = crear_juego_aleatorio(pos, GP);
    }

    while (continuarJuego)
    {
        mostrar_juego_consola(juego);
        pedir_pos(fila, columna);
        continuarJuego = juega(juego, fila, columna, listaUndo);
    }

    if (fila != -1 && columna != -1) 
    {
        mostrar_juego_consola(juego);
        GP.eliminar(pos);
    }

    mostrar_resultado(juego);

    juego.destruye();

    if(GP.numero_juegos() > 0)
        GP.guardar_lista_juegos();
    return 0;
}


bool juega(Juego& juego, int fila, int columna, ListaUndo& lista_undo)
{
    bool seguirJugando = true;

    //parsear opcion
    switch (obtenerOpcion(fila, columna))
    {
    case 1: /*-1 -1*/
        cout << YELLOW << "El usuario ha decidido terminar el juego\n" << RESET;
        seguirJugando = false;
        break;
    case 2: /*-2 -2*/
        cout << "MARCAR/DESMARCAR mina:\n";
        pedir_pos(fila, columna);
        juego.marcar_desmarcar(fila, columna);
        break;
    case 3: /*-3 -3*/
        cout << "UNDO: realizar undo.\n";
        for (int i = 0; i < lista_undo.ultimo_elemento().longitud(); i++)
        {
            juego.ocultar_celda(lista_undo.ultimo_elemento().dame_posX(i), lista_undo.ultimo_elemento().dame_posY(i));
        }
        lista_undo.eliminar_ultimo_elemento();
        break;
    default:
        ListaPosiciones lista_pos;  //crear lista de posiciones
        juego.juega(fila, columna, lista_pos);  //realizar movimiento
        if (juego.es_valida(fila,columna))
        {
            lista_undo.insertar_final(lista_pos);   //insertar posiciones modificadas en la lista undo
        }
        if (juego.esta_completo() || juego.mina_explotada()) seguirJugando = false;
        break;
    }

    return seguirJugando;
}

int obtenerOpcion(int fila, int columna)
{
    int opcion = 0; //default

    if (fila == -1 && columna == -1) opcion = 1; // Salir
    else if (fila == -2 && columna == -2) opcion = 2; // Marcar/Desmarcar
    else if (fila == -3 && columna == -3) opcion = 3; // Undo

    return opcion;
}

Juego crear_juego_aleatorio(int& pos, GestorJuegos& GP)
{
    int filas, columnas;
    Juego juego;
    pedirDimensiones(filas, columnas);

    int numMinas = (filas * columnas) / 3;

    juego = Juego(filas, columnas, numMinas);
    pos = GP.insertar(juego);

    return juego;
}

Juego crear_o_seleccionar_juego(GestorJuegos& GP, int& pos)
{
    Juego juego;

    //si el fichero no tiene partidas
    if (!GP.hay_juegos())
    {
        cout << RED << "El fichero cargado no tiene juegos... Se crea uno aleatorio\n" << RESET;
        juego = crear_juego_aleatorio(pos, GP);
    }
    //si el fichero tiene partidas
    else
    {
        int opt = 0;
        do
        {
            cout << BLUE << "Juego nuevo (opcion 1) o juego existente (opcion 2): " << RESET;    //pedirle al uusario si quiere generar un juego aleatorio o elegir alguno que haya en el gestor de partidos
            cin >> opt;
        } while (opt != 1 && opt != 2);

        if (opt == 1)
        {           
            juego = crear_juego_aleatorio(pos, GP); //crear tablero aleatorio
        }
        else
        {
            GP.mostrar_lista_juegos();  //mostrar lista de partidas
            int partida = -1;
            do
            {
                cout << "Selecciona la partida: ";
                cin >> partida;
            } while (partida < 0 || partida > GP.numero_juegos()-1);

            juego = GP.dame_juego(partida);  //jugar la partida seleccionada por el usuario
            pos = partida;
        }
    }

    return juego;
}
