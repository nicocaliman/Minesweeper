
#include "ListaUndo.h"
#include "checkML.h"

ListaUndo::ListaUndo()
{
    inicializar(); //iniciar el numero de elementos a 0
}

ListaUndo::~ListaUndo()
{
    destruye();
}

void ListaUndo::destruye()
{
    for (int i = 0; i < MAX_UNDO; i++)
    {
        delete lista[i];
        lista[i] = nullptr;
    }

    cont = 0;
}

void ListaUndo::insertar_final(const ListaPosiciones& lista_pos)
{
    //si no hay espacio en la lista
    if (cont == MAX_UNDO)
    {
        // Liberar el primer elemento
        delete lista[0];

        // Desplazar los elementos hacia la izquierda
        for (int i = 1; i < MAX_UNDO; i++)
        {
            lista[i - 1] = lista[i]; // Desplazar
        }

        // Insertar lista_pos en la última posición
        lista[MAX_UNDO - 1] = new ListaPosiciones(lista_pos); // Asignar nueva memoria
    }

    //si hay espacio 
    else
    {
        delete lista[cont]; //si no se libera el indice antes, se sobreescribira y habra leaks de memoria
        lista[cont] = new ListaPosiciones(lista_pos);    //insertamos lista_pos en la ultima posicion 
        cont++;   //actualizamos contador
    }
}

ListaPosiciones ListaUndo::ultimo_elemento() const
{
    return *lista[cont - 1];   //ultimo elemento de la lista
}

void ListaUndo::eliminar_ultimo_elemento()
{
    if (cont > 0)
    {
        delete lista[cont]; //llamar a la destructora de ListaPosiciones
        lista[cont] = nullptr;
        cont--; //actualizar contador
    }
}

void ListaUndo::inicializar()
{
    for (int i = 0; i < MAX_UNDO; i++)
    {
        lista[i] = new ListaPosiciones();   //inicializar cada indice
    }   

    cont = 0;   //0 elementos inicialmente
}
