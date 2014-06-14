#ifndef CAMINANTE_H_INCLUDED
#define CAMINANTE_H_INCLUDED

#include "Lista.h"
#include "Mochila.h"
#include "GPS.h"
#include "Mapa.h"

class Caminante{
private:
    Lista<Lista<string>*>* recorridos;
    Lista<pair<int, int> > listaDeCoordenadasRelativas;
    Mochila* unaMochila;
    GPS unGPS;
    Mapa unMapa;

public:
    //Pre: Se debe haber llamado al cargadorDeRecorridos
    //Post: Carga una serie de recorridos en memoria
    Caminante(Lista<Lista<string>*>* recorridos);

    ~Caminante();

    //Pre:
    //Post:
    void logisticaDelRecorrido(Lista<Lista<string>*>* recorridos);

    //Pre:
    //Post:
    void obtenerInformacionDel(Lista<string>* recorridoActual);

    void enviarObjetosDelCaminoALaMochila(string informacionLeida);

    void enviarAccionesAlGPS(string informacionLeida);

    void enviarInformacionAlMapa();

    Lista<Objeto>* obtenerObjetosDeLaMochila();

    void dibujarBMP();
};

#endif // CAMINANTE_H_INCLUDED
