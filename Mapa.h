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
    pair<int, int> nuevoOrigen;
    string rgb;

    int anchoBMP;
    int altoBMP;

public:
    Mapa();
    ~Mapa();
    void cargarColor(int* rgb);
    void cargarRecorrido(Lista<pair<int, int> >* listaDeCoordenadas);
    void dibujarRecorridos();
    void cargarNuevoOrigen(pair<int, int> nuevoOrigen);
    void marcarObjetos(Lista<pair<int, int> >* coordenadasPorMarcar);
    void marcarEjes();
};

#endif // MAPA_H_INCLUDED
