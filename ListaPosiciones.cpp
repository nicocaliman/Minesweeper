
#include "ListaPosiciones.h"
#include "checkML.h"

void ListaPosiciones::inicializa()
{
    size = MAX_LISTA;   //dimension inicial
    lista = new Posicion[size];    //crear array dinamico de dimension inicial MAX_LISTA
    cont = 0;   //0 elementos inicialmente
}

void ListaPosiciones::resize()
{
    int newSize = size*INCREMENTO;  //nueva dimension
    Posicion* listaAux = new Posicion[newSize]; //crear nueva lista dinamica auxiliar

    //copiar flechas
    for (int i = 0; i < cont; i++)
    {
        listaAux[i] = lista[i];
    }

    size = newSize; //actuaizar dimension
    delete[] lista; //liberar memoria
    lista = listaAux;
}

void ListaPosiciones::destruye()
{
    //destruir atributos
    cont = 0;
    size = 0;

    delete[] lista; //liberar memoria   
    lista = nullptr;    //direccion valida
}

ListaPosiciones::ListaPosiciones()
{
    inicializa();
}

ListaPosiciones::ListaPosiciones(const ListaPosiciones& lp)
{
    size = lp.size; //copiar dimension actual
    cont = lp.cont; //copiar numero de elementos 
    lista = new Posicion[size]; // Reservar memoria exacta para los elementos

    for (int i = 0; i < cont; i++)
    {
        lista[i] = lp.lista[i]; // Copiar posición directamente
    }
}

ListaPosiciones::~ListaPosiciones()
{
    destruye(); //destruir 
}

void ListaPosiciones::insertar_final(int x, int y)
{
    //si no quedan huecos en la lista
    if (longitud() == size)
    {
        resize();   //redimensionar array dinamico
    }

    lista[cont].posx = x;
    lista[cont].posy = y;

    cont++; //actualizar contador
}

int ListaPosiciones::longitud() const
{
    return cont;  //numero de indices ocupados en la lista
}

int ListaPosiciones::dame_posX(int i) const
{
    return lista[i].posx;
}

int ListaPosiciones::dame_posY(int i) const
{
    return lista[i].posy;
}
