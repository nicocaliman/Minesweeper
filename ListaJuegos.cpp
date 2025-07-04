#include "ListaJuegos.h"

const int CAPACIDAD_INICIAL = 1;

void ListaJuegos::redimensionar()
{
	int nuevaCapacidad = capacidad * 2;	//duplicamos la capacidad original
	Juego** nuevaLista = new Juego * [nuevaCapacidad];	//creamos la nueva lista

	for (int i = 0; i < cont; i++)
	{
		nuevaLista[i] = lista[i];	//copiamos los punteros existentes
	}

	delete[] lista;	//borramos array viejo
	lista = nuevaLista;
	capacidad = nuevaCapacidad;
}

void ListaJuegos::buscar(const Juego& juego, int& pos) const
{
	double dificultad_nueva = static_cast<double>(
		juego.dame_num_filas() * juego.dame_num_columnas()
		) / juego.dame_num_minas();

	pos = 0;

	while (pos < cont &&
		dificultad_nueva < static_cast<double>(
			lista[pos]->dame_num_filas() * lista[pos]->dame_num_columnas()
			) / lista[pos]->dame_num_minas())
	{
		pos++;
	}

}

ListaJuegos::ListaJuegos()
{
	capacidad = CAPACIDAD_INICIAL;
	cont = 0;
	lista = new Juego * [capacidad];
}

ListaJuegos::~ListaJuegos()
{
	//liberamos los juegos individuales
	for (int i = 0; i < cont; i++)	//el contador habra ido aumentando segun se hayan ido aniadiendo juegos
	{
		delete lista[i];	//borramos cada elemento de la lista
	}

	delete[] lista;	//liberamos el array
	lista = nullptr;
}

int ListaJuegos::insertar(const Juego& juego)
{
	if (cont == capacidad)
	{
		redimensionar();
	}

	int pos;
	buscar(juego, pos);

	for (int i = cont; i > pos; i--)	//comienza en la ultima posicion hasta y va reduciendo hasta llegar a la posicion indicada
	{
		lista[i] = lista[i - 1];
	}

	//creamos una copia del juego en la memoria dinamica
	lista[pos] = new Juego(juego);
	cont++;

	return pos;
}

int ListaJuegos::dame_longitud() const
{
	return cont;	//numero de juegos en la lista
}

bool ListaJuegos::es_vacia() const
{
	return cont == 0;	//true si esta vacia
}

const Juego& ListaJuegos::dame_juego(int pos) const
{
	return *lista[pos];	//juego en la posicion dada(como referencia constante)
}

void ListaJuegos::eliminar(int pos)
{
	delete lista[pos];	//eliminar el objeto de la lista de juegos

	//desplazamos juego hacia la izquierda
	for (int i = pos; i < cont-1; i++)
	{
		lista[i] = lista[i + 1];
	}

	cont--;
}
