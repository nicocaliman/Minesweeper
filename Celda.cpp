#include "Celda.h"

void Celda::setDefaults()
{
    descubierta = false;  //*oculta
    marcada = false;  //*no marcada
    estado = VACIA;   //*vacia
    numero = 0;       //*a 0 
}

Celda::Celda()
{
    setDefaults();
}

void Celda::destruye()
{
    setDefaults();  //mismo codigo que la constructora por defecto
}

int Celda::dame_numero() const
{
    return numero;    //numero de la celda
}

bool Celda::esta_descubierta() const
{
    return descubierta;   //true si descubierta == true, false en caso contrario
}

bool Celda::contiene_mina() const 
{
    return (estado == MINA);  //true si estado == MINA, false en caso contrario
}

bool Celda::contiene_numero() const
{
    return (estado == NUMERO);    //true si estado == NUMERO, false en caso contrario
}

bool Celda::esta_vacia() const 
{
    return (estado == VACIA); //true si estado == VACIA, false en caso contrario
}

bool Celda::esta_marcada() const
{
    return marcada;   //true si marcada == true, false en caso contrario
}

void Celda::descubrir_celda()
{
    descubierta = true;   //celda descubierta
}

void Celda::ocultar_celda()
{
    descubierta = false;  //celda ocultada
}

void Celda::poner_mina()
{
    estado = MINA;    //mina puesta
}

void Celda::poner_numero(int n)
{
    estado = NUMERO;  //la celda tiene un numero
    numero = n;       //poner n como nuevo valor de la celda
}

void Celda::marcar_celda()
{
    marcada = true;   //celda marcada
}

void Celda::desmarcar_celda()
{
    marcada = false;  //celda desmarcada
}