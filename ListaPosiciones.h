
    #pragma once

    const int MAX_LISTA = 1;
    const int INCREMENTO = 2;

    class ListaPosiciones
    {
    private:
        typedef struct
        {
            int posx;
            int posy;
        }Posicion;

        int cont;
        int size;   // dimensión actual del array dinámico
        Posicion* lista;
        //!funcion privada: inicializa el contador de la lista
        void inicializa();
        //redimensionar
        void resize();
        //igual que la constructora
        void destruye();
    public:
        //constructora por defecto
        ListaPosiciones();
        //constructora por copia
        ListaPosiciones(const ListaPosiciones& lp);
        //destructora
        ~ListaPosiciones();
        //almacena si es posible, la posicion (x,y) al final de la lista
        void insertar_final(int x, int y);
        //numero de posiciones ocupadas en la lista
        int longitud() const;
        //valor de posX en la posicion i
        int dame_posX(int i) const;
        //valor de posY en la posicion y
        int dame_posY(int i) const;
    };
