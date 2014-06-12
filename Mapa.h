#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#include "Lista.h"
#include "Nodo.h"
#include "EasyBMP.h"

using namespace std;

class Mapa{
private:
    string pasos;
    int pasosHorizontales;
    int pasosVerticales;
    int coordenadaVertical;
    int coordenadaHorizontal;
    int tamanioDelRecorrido[2];
    int ColorActual[3];
    int* vecCoordenadas;
    string rgb;
    int nuevoOrigenX;
    int nuevoOrigenY;

    int anchoBMP;
    int altoBMP;

public:
    /*
    * Pre: -
    * Post: Crea un nuevo mapa vacio
    */
    Mapa();

    /*
    * Pre: -
    * Post: Libera todos los recursos asociados al Mapa
    */
    ~Mapa();

    /*
    * Pre: Codigos de colores RGB separados por un espacio
    * Post: Se crea un vector de tres posiciones con los codigos recibidos
    */
    void colorActual(string rgb);

    /*
    * Pre: El mapa debe estar creado y previamente debe haber
    * sido cargada una lista con los pasos del caminante
    * Post: Devuelve un mapa en formato BMP
    */
    void dibujarRecorrido(Lista<pair<int, int> > listaDeCoordenadas);

    void defase(int* defase);

    void calcularTamanioBMP(Lista<pair<int, int> > listaDeCoordenadas);

    void firmaDelMapa(BMP Laberinto);

private:
    /*
    * Pre:
    * Post:
    */
    void convertirPasosACoordenadas(string pasos);
};

#endif // MAPA_H_INCLUDED
