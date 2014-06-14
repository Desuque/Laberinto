#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED

#include "Lista.h"
#include "Nodo.h"
#include "EasyBMP.h"

using namespace std;

class Mapa{
private:
    BMP Laberinto;

    string pasos;
    int pasosHorizontales;
    int pasosVerticales;
    int coordenadaVertical;
    int coordenadaHorizontal;
    int tamanioDelRecorrido[2];
    int* colorActual;
    string rgb;

    int anchoBMP;
    int altoBMP;

public:
    Mapa();
    ~Mapa();
    void cargarColor(int* rgb);
    void cargarRecorrido(Lista<pair<int, int> >* listaDeCoordenadas);
    void dibujarRecorridos();
};

#endif // MAPA_H_INCLUDED
