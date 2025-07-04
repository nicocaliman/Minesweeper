#pragma once
#include "ListaJuegos.h"
#include "inputOutput.h"

class GestorJuegos
{
private:
	ListaJuegos juegos;
public:
	GestorJuegos();	//constructora: no hace nada
	bool cargar_juegos();
	void mostrar_lista_juegos() const;
	int numero_juegos() const;
	const Juego& dame_juego(int pos) const;
	int insertar(const Juego& juego);
	void eliminar(int pos);
	bool hay_juegos() const;
	bool guardar_lista_juegos() const;
};