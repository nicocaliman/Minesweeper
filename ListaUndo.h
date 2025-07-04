
#pragma once
#include "ListaPosiciones.h"

const int MAX_UNDO = 3;

class ListaUndo
{
private:
    int cont;
    ListaPosiciones* lista[MAX_UNDO];

    //!funcion privada: inicializar el contador
    void inicializar();
    //destruye todos los elementos de la lista y pone el contador
    void destruye();
public:
    //constructora por defecto
    ListaUndo();
    //destructora
    ~ListaUndo();
    //inserta lista_pos al final de la lista. Si no hay espacio desplaza todos los elementos hacia la izquierda, descartando el colocado en la posicion 0
    void insertar_final(const ListaPosiciones& lista_pos);
    //devuelve el ultimo elemento de la lista
    ListaPosiciones ultimo_elemento() const;
    void eliminar_ultimo_elemento();
};
