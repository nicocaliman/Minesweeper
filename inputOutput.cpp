
#include "inputOutput.h"
#include <iomanip>
#include <cctype>
#include <iostream>

using namespace std;


const char CHAR_MINA = '*';  // Mina


void mostrar_separador(const Juego& juego);
void mostrar_celda(const Juego& juego, int f, int c);
void color_numero(int numero);

void color_numero(int numero) {
    switch (numero) {
    case 1: cout << BLUE; break;
    case 2: cout << GREEN; break;
    case 3: cout << RED; break;
    case 4: cout << DBLUE; break;
    case 5: cout << DGREEN; break;
    case 6: cout << DRED; break;
    default:
        break;
    }
}

string pedir_fichero()
{
    string fichero;

    //le pedimos al usuario el nombre del fichero a cargar
    cout << "Nombre del fichero de juegos: ";
    cin >> fichero;

    return fichero;
}

void pedirDimensiones(int& filas, int& columnas)
{
    do
    {
        cout << "Numero de filas (>=3) y columnas (>=3) del tablero: ";
        cin >> filas >> columnas;
    } while (filas < 3 || columnas < 3);
}

void mostrar_separador(const Juego& juego) {
    cout << "\t -+";
    for (int col = 0; col < juego.dame_num_columnas(); ++col) {
        cout << setw(N_HUECOS + 1) << setfill('-') << '+' << setfill(' ');
    }
    cout << endl;
}

void mostrar_celda(const Juego& juego, int fila, int columna) {
    if (!juego.esta_descubierta(fila, columna) && !juego.esta_marcada(fila, columna)) {
        cout << BG_GRAY << GRAY << N_HUECOS << setfill(' ') << ' ' << RESET;
    }
    else {
        cout << BG_BLACK << BLACK;
        if (!juego.esta_marcada(fila, columna)) {
            if (juego.contiene_mina(fila, columna)) {
                cout << RED << setw(N_HUECOS) << setfill(' ') << CHAR_MINA << RESET;
            }
            else {
                if (juego.esta_vacia(fila, columna)) {
                    cout << setw(N_HUECOS) << setfill(' ') << ' ' << RESET;
                }
                else {
                    if (juego.contiene_numero(fila, columna)) {
                        int numero = juego.dame_numero(fila, columna);
                        color_numero(numero);
                        cout << setw(N_HUECOS) << setfill(' ') << numero << RESET;
                    }
                    else {
                        cout << BG_RED << RED << setw(N_HUECOS) << setfill(' ') << ' ' << RESET;
                    }
                }
            }
        }
        else {
            cout << BG_ORANGE << ORANGE << setw(N_HUECOS) << setfill(' ') << ' ' << RESET;
        }
    }
}

void mostrar_cabecera()
{
    cout << "Buscaminas\n"; //cabecera
    cout << "----------\n";
}


void pedir_pos(int& fila, int& columna)
{
    bool valido = false;

    while (!valido)
    {
        cout << "Introduce la fila y la columna: ";
        if (cin >> fila >> columna)
        {
            valido = true; // Si se leyeron correctamente, marcar como válido
        }
        else
        {
            /*
            La implementación del control de entrada de datos se basa en las técnicas explicadas en 
            'The C++ Programming Language' de Bjarne Stroustrup (4ª edición, 2013)
            y 'C++ Primer' de Lippman, Lajoie y Moo (5ª edición, 2012).
            */
            cout << "Error: introduce numeros enteros.\n";
            /*
            Cuando cin encuentra un error (por ejemplo, si se intenta leer un tipo de dato incorrecto),
            se establece un estado de error que impide que se realicen más lecturas hasta que se limpie.
            */
            cin.clear(); // Limpiar el estado de error
            /*
            Esta línea se utiliza para ignorar el resto de la línea en el flujo de entrada hasta que se encuentre un salto de línea ('\n').
            Esto es útil para limpiar el búfer de entrada después de un error, asegurando que cualquier entrada no válida no interfiera con las siguientes lecturas.
            */
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignorar el resto de la línea
        }
    }
}

void mostrar_resultado(const Juego& juego)
{
    if (juego.esta_completo())
    {
        cout << GREEN << "El usuario ha ganado!\n" << RESET;
    }

    else if (juego.mina_explotada())
    {
        cout << RED << "El usuario ha pisado una mina\n" << RESET;
    }
}

void mostrar_juego_consola(const Juego& juego)
{
    // mostrar el n�mero de jugadas del juego
    cout << "Jugadas: " << juego.dame_num_jugadas() << "\n";
    // mostrar cabecera
    cout << "\t  |";
    for (int col = 0; col < juego.dame_num_columnas(); col++) {
        cout << LBLUE << setw(N_HUECOS) << col << RESET << '|';
    }
    cout << endl;

    // mostrar separador
    mostrar_separador(juego);

    // mostrar tablero
    for (int f = 0; f < juego.dame_num_filas(); f++) {
        // mostrar numero de fila
        cout << "\t" << LBLUE << setw(2) << f << RESET << '|';
        // mostrar la fila
        for (int c = 0; c < juego.dame_num_columnas(); c++) {
            mostrar_celda(juego, f, c);
            cout << '|';
        }
        cout << endl;

        mostrar_separador(juego);
    }
    cout << endl;
}

void cargar_juego(istream& archivo, Juego& juego)
{
    archivo >> juego;
}

istream& operator>>(istream& in, Juego& juego)
{
    int filas, columnas, num_minas;

    //leer numero de filas, columnas y minas que tiene el tablero
    in >> filas >> columnas >> num_minas;

    //inicializar el juego
    juego.inicializa(filas, columnas, num_minas);

    for (int i = 0; i < num_minas; i++)
    {
       int fila, columna;
       in >> fila >> columna;

       juego.poner_mina(fila, columna);    //poner mina en la posicion [fila][columna]
    }

    return in;
}
