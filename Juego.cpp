#include "Juego.h"
#include <ctime>
#include <cstdlib>

void Juego::actualizar_vecinas(int fila, int columna)
{
    for (int i = 0; i < NUM_DIRS; i++)
    {
        actualizar_direccion(fila, columna, i);
    }
}

void Juego::actualizar_direccion(int fila, int columna, int direccion)
{
    int incrX = DIRECCIONES[direccion][0];
    int incrY = DIRECCIONES[direccion][1];

    int posX = fila + incrX;
    int posY = columna + incrY;

    if (tablero.es_valida(posX, posY))
    {
        Celda c = tablero.dame_celda(posX, posY);

        if (esta_vacia(posX, posY) || contiene_numero(posX, posY))
        {
            int numero = c.dame_numero();
            numero++;

            c.poner_numero(numero); //cambiar estado de la celda

            tablero.poner_celda(posX, posY, c);
        }
    }
}

void Juego::descubrir_vecinas(int fila, int columna, ListaPosiciones& lista_pos)
{
    for (int i = 0; i < NUM_DIRS; i++)
    {
        descubrir_direccion(fila, columna, i, lista_pos);
    }
}

void Juego::descubrir_direccion(int fila, int columna, int direccion, ListaPosiciones& lista_pos)
{
    int incrX = DIRECCIONES[direccion][0];
    int incrY = DIRECCIONES[direccion][1];

    int posX = fila + incrX;
    int posY = columna + incrY;

    if (tablero.es_valida(posX, posY))
    {
        Celda c = tablero.dame_celda(posX, posY);

        if (!esta_marcada(posX, posY) && !esta_descubierta(posX, posY))
        {
            c.descubrir_celda();
            tablero.poner_celda(posX, posY, c);

            lista_pos.insertar_final(posX, posY);
            num_descubiertas++;

            // Si la celda también está vacía, seguimos descubriendo (!RECURSION)
            if (c.esta_vacia())
                descubrir_vecinas(posX, posY, lista_pos);  //llamada recursiva
        }
    }
}

void Juego::setDefaults()
{
    num_jugadas = num_minas = num_descubiertas = 0;
    mina_pisada = false;
}

void Juego::descubrir_celda(int fila, int columna)
{
    //si la posicion [fila][columna] es valida
    if (tablero.es_valida(fila, columna))
    {
        //celda en la posicion [fila][columna]
        Celda c = tablero.dame_celda(fila, columna);

        //si la celda en la posicion [fila][columna] esta descubierta
        if (!esta_descubierta(fila, columna))
        {
            c.descubrir_celda();  //ocultar celda 
            tablero.poner_celda(fila, columna, c);

            num_descubiertas++;
        }
    }
}

bool Juego::es_valida(int fila, int columna)
{
    return tablero.es_valida(fila, columna);
}

Juego::Juego()
{
    setDefaults();

    tablero = Tablero();  //inicializar tablero
}

Juego::Juego(int fils, int cols)
{
    setDefaults();

    tablero = Tablero(fils, cols);    //inicializar tablero con los parametros 
}

Juego::Juego(int fils, int cols, int numMinas)
{
    setDefaults();
    num_minas = numMinas;

    tablero = Tablero(fils, cols);

    //insertar minas aleatoriamente

    int minas_colocadas = 0;
    while (minas_colocadas < numMinas)
    {
        int x = rand() % fils;  //desde 0 hasta fils-1 inclusive
        int y = rand() % cols;  //desde 0 hasta cols-1 inclusive

        if (poner_mina(x,y))    //sintentar poner la mina
        {
            ++minas_colocadas;    //actualizar contador de minas
        }
    }
}

void Juego::destruye()
{
    tablero.destruye();   //destruye el tablero

    setDefaults();
}

int Juego::dame_num_jugadas() const
{
    return num_jugadas;   //numero de jugadas
}

int Juego::dame_num_filas() const
{
    return tablero.num_filas();   //numero de filas del tablero
}

int Juego::dame_num_columnas() const
{
    return tablero.num_columnas();    //numero de columnas del tablero
}

int Juego::dame_num_minas() const
{
    return num_minas; //numero de minas que hay en el tablero
}

bool Juego::contiene_mina(int fila, int columna) const
{
    return tablero.dame_celda(fila, columna).contiene_mina(); //true si estado = MINA, false en caso contrario
}

bool Juego::esta_descubierta(int fila, int columna) const
{
    return tablero.dame_celda(fila, columna).esta_descubierta();  //true si descubierta = true, false en caso contrario
}

bool Juego::esta_marcada(int fila, int columna) const
{
    return tablero.dame_celda(fila, columna).esta_marcada();  //true si marcada = true, false en caso contrario
}

bool Juego::esta_vacia(int fila, int columna) const
{
    return tablero.dame_celda(fila, columna).esta_vacia();    //true si estado = VACIA, false en caso contrario
}

bool Juego::contiene_numero(int fila, int columna) const
{
    return tablero.dame_celda(fila, columna).contiene_numero();   //true si estado = NUMERO, false en caso contrario
}

bool Juego::esta_completo() const
{
    // Calcular el número total de celdas que deben ser descubiertas
    int total_celdas = dame_num_filas() * dame_num_columnas();
    int total_a_descubrir = total_celdas - num_minas; // Total de celdas menos las minas

    // Verificar si el número de celdas descubiertas es igual al total a descubrir
    return num_descubiertas == total_a_descubrir;
}

bool Juego::mina_explotada() const
{
    return mina_pisada;
}

int Juego::dame_numero(int fila, int columna) const
{
    return tablero.dame_celda(fila, columna).dame_numero();   //numero de la celda
}

bool Juego::poner_mina(int fila, int columna)
{
    bool ok = false;
    //si la posicion [fila][columna] del tablero es valida  + 
    //la celda en la posicion [fila][columna] no esta descubierta +
    // la celda en la posicion [fila][columna] no contiene una mina
    if (tablero.es_valida(fila, columna) && !esta_descubierta(fila, columna) && !contiene_mina(fila, columna))
    {
        Celda c = tablero.dame_celda(fila,columna);

        //poner mina en la posicion [fila][columna]
        c.poner_mina();
        tablero.poner_celda(fila, columna, c);

        //actualizar celdas vecinas
        actualizar_vecinas(fila, columna);

        ok = true;
    }

    return ok;
}

void Juego::marcar_desmarcar(int fila, int columna)
{
    //si la posicion [fila][columna] es valida
    if (tablero.es_valida(fila, columna))
    {
        //si la celda en la posicion [fila][columna] esta oculta (descubierta = false)
        if (!esta_descubierta(fila, columna))
        {
            Celda c = tablero.dame_celda(fila, columna);

            //si la celda no esta marcada 
            if (!esta_marcada(fila, columna))
            {
                c.marcar_celda();   //marcar celda
                tablero.poner_celda(fila, columna, c);
            }

            //si la celda esta marcada
            else
            {
                c.desmarcar_celda();      //desmarcar celda  
                tablero.poner_celda(fila, columna, c);
            }
        }
    }
}

void Juego::ocultar_celda(int fila, int columna)
{
    //si la posicion [fila][columna] es valida
    if (tablero.es_valida(fila, columna))
    {
        //si la celda en la posicion [fila][columna] esta descubierta
        if (esta_descubierta(fila, columna))
        {
            Celda c = tablero.dame_celda(fila, columna);

            c.ocultar_celda();         
            tablero.poner_celda(fila, columna, c);
            num_descubiertas--;
        }
    }
}

void Juego::juega(int fila, int columna, ListaPosiciones& lista_pos)
{
    //si las coordenadas son validas y la celda esta oculta + no marcada
    if (tablero.es_valida(fila, columna) && !esta_descubierta(fila, columna) && !esta_marcada(fila, columna))
    {
        Celda c = tablero.dame_celda(fila, columna);

        //descubrir celda
        c.descubrir_celda();
        tablero.poner_celda(fila, columna, c);

        num_descubiertas++;

        //agregar la posicion [fila][columna] a la lista de posiciones
        lista_pos.insertar_final(fila, columna);

        // Si la celda contiene una mina
        if (contiene_mina(fila, columna))
            mina_pisada = true; // Cambiar mina_pisada a true

        // Si la celda no es una mina y no contiene un número mayor que 0
        else if (dame_numero(fila, columna) == 0) 
            descubrir_vecinas(fila, columna, lista_pos);    // Actualizar celdas vecinas

        //actualizar numero de jugadas
        num_jugadas++;
    }
}

void Juego::inicializa(int f, int c, int numMinas)
{
    num_jugadas = num_descubiertas = 0;
    num_minas = numMinas;
    mina_pisada = false;

    tablero = Tablero(f, c);
}