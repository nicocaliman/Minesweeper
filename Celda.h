#pragma once

class Celda
{
private:
    //tipo de celda
    typedef enum { NUMERO, VACIA, MINA } Estado;
    //celda desubierta u oculta
    bool descubierta;
    Estado estado;
    //numero de minas que rodean la celda
    int numero;
    //celda marcada o no marcada
    bool marcada;
    //!funcion privada: valores por defecto de las variables de la clase
    void setDefaults();
public:
    //constructor por defecto
    Celda();
    //mismo codigo que la constructora por defecto
    void destruye();
    //valor del campo numero 
    int dame_numero() const;
    //true si la celda esta descubierta
    bool esta_descubierta() const;
    //true si la celda contiene una mina
    bool contiene_mina() const;
    //true si la celda contiene un numero
    bool contiene_numero() const;
    //true si la celda esta vacia
    bool esta_vacia() const;
    //true si la celda esta marcada
    bool esta_marcada() const;
    //descubre celda
    void descubrir_celda();
    //oculta la celda
    void ocultar_celda();
    //cambia el estado de la celda a MINA
    void poner_mina();
    //pone el estado de la mina a NUMERO y el numero de la celda al valor n
    void poner_numero(int n);
    //marca la celda
    void marcar_celda();
    //desmarca la celda
    void desmarcar_celda();
};
