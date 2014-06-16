#ifndef GPS_H_INCLUDED
#define GPS_H_INCLUDED

#include <string>
#include "Lista.h"
#include "Bifurcacion.h"

using namespace std;

class GPS{
private:
    int sentidoEjeActual;
    char direccionEnEje;
    Lista<pair<int, int> >* listaDeCoordenadas;
    Lista<pair<int, int> >* listaDePasos;
    Lista<pair<int, int> >* coordenadasPorMarcar;
    Lista<Bifurcacion>* bifurcaciones;
    string codigoDeColor;
    int colorActual[3];
    pair<int, int> nuevoOrigen;
    int MaximoX;
    int MinimoX;
    int MaximoY;
    int MinimoY;


public:
    GPS();
    ~GPS();
    void discriminarInformacion(string informacionLeida);
    void enviarCoordenadasAlMapa();
    Lista<pair<int, int> >* obtenerListaDeCoordenadas();
    Lista<pair<int, int> >* obtenerListaDePasos();
    void cargarColorActual(string rgb);
    int* obtenerCodigoDeColor();
    void vaciarListaDePasos();
    void vaciarListaDeCoordenadas();
    void obtenerCoordenadaActual();
    void cargarCoordenadasPorMarcar();
    Lista<pair<int, int> >* obtenerCoordenadasPorMarcar();
    pair<int, int> obtenerNuevoOrigen();
    void cargarBifurcacion(string bifurcacion);
    void calcularNuevoOrigen();

private:
    void obtenerDireccion(string informacionLeida);
    void cargarCoordenada(string informacionLeida);
    void buscarMinimoMaximo(Lista<pair<int, int> >* recorridoActual);
    pair<int, int> obtenerPosicionActual();
};

#endif // GPS_H_INCLUDED
