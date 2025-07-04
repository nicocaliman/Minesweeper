#pragma once
#include "Juego.h"
class ListaJuegos {
private:
	int cont;	//numero de juegos de la lista
	Juego** lista;	//array dinamico de punteros a juego
	int capacidad;	//tamanio actual del array

	void redimensionar();	//aumenta la capacidad del array dinamico
	void buscar(const Juego& juego, int& pos) const;	//metodo privado: calcula la posicion donde insertar el juego
public:
	ListaJuegos();	//constructor
	~ListaJuegos();	//destructor
	int insertar(const Juego& juego);	//insertar un nuevo juego 
	int dame_longitud() const;	//numero de juegos en la lista
	bool es_vacia() const;	//true si no hay juegos en la lista
	const Juego& dame_juego(int pos) const;	//devuelve una referencia al juego
	void eliminar(int pos);	//elimina juego en la posicion pos
};