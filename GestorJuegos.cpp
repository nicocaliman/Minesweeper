#include "GestorJuegos.h"
#include <iostream>
#include <iomanip>

GestorJuegos::GestorJuegos()
{
	//no hace nada
}

bool GestorJuegos::cargar_juegos()
{
	//pedir fichero con las partidas
	string nombreFichero = pedir_fichero();

	ifstream archivo;
	bool ok = false;

	archivo.open(nombreFichero);	//abrir archivo

	if (archivo.is_open())	//si el archivo se ha abierto correctamente
	{
		int numJuegos;
		archivo >> numJuegos;	//leer el numero del tableros que hay en el fichero
		
		for (int i = 0; i < numJuegos; i++)
		{
			Juego juego;
			cargar_juego(archivo, juego);	//cargar tablero

			insertar(juego);	//insertar juego en la lista de juegos
		}

		archivo.close();	//cerrar fichero
		ok = true;
	}

	return ok;
}

void GestorJuegos::mostrar_lista_juegos() const
{
	cout << "Mostrando lista de juegos por orden de dificultad...\n";
	for (int i = 0; i < numero_juegos(); i++)
	{
		cout << "Juego " << i << "\n";
		cout << setw(14) << "Dimension: " << dame_juego(i).dame_num_filas() << " x " << dame_juego(i).dame_num_columnas() << "\n";
		cout << setw(10) << "Minas: " << dame_juego(i).dame_num_minas() << "\n";
	}
}

int GestorJuegos::numero_juegos() const
{
	return juegos.dame_longitud();
}

const Juego& GestorJuegos::dame_juego(int pos) const
{
	return juegos.dame_juego(pos);
}

int GestorJuegos::insertar(const Juego& juego)
{
	return juegos.insertar(juego);
}

void GestorJuegos::eliminar(int pos)
{
	juegos.eliminar(pos);
}

bool GestorJuegos::hay_juegos() const
{
	return !juegos.es_vacia();
}

bool GestorJuegos::guardar_lista_juegos() const
{
    string nombreFichero;
    bool ok = false;
    bool nombreValido = false;

    while (!nombreValido)
    {
        cout << "Nombre del fichero para guardar los juegos: ";
        cin >> nombreFichero;

        // Verificar si el fichero ya existe
        ifstream test(nombreFichero);
        if (!test.is_open())
        {
            cout << RED << "El fichero no existe. Por favor, elige otro nombre.\n" << RESET;
        }
        else
        {
            nombreValido = true;
            test.close();
        }
    }

    // Ahora abrimos para escritura
    ofstream archivo(nombreFichero);
    if (archivo.is_open())
    {
        archivo << numero_juegos() << endl;

        for (int i = 0; i < numero_juegos(); ++i)
        {
            const Juego& j = dame_juego(i);

            archivo << j.dame_num_filas() << " " << j.dame_num_columnas() << endl;
            archivo << j.dame_num_minas() << endl;

            for (int f = 0; f < j.dame_num_filas(); ++f)
            {
                for (int c = 0; c < j.dame_num_columnas(); ++c)
                {
                    if (j.contiene_mina(f, c))
                        archivo << f << " " << c << endl;
                }
            }
        }

        archivo.close();
        cout << GREEN << "Lista de juegos guardada correctamente en " << nombreFichero << "\n" << RESET;
        ok = true;
    }
    else
    {
        cout << RED << "Error al abrir el fichero para guardar.\n" << RESET;
    }

    return ok;
}
