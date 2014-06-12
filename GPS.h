#ifndef GPS_H_INCLUDED
#define GPS_H_INCLUDED

#include "Mapa.h"
#include <string>

using namespace std;

class GPS{
private:
    string codigoDeColor;
    int sentidoEjeActual;
    char direccionEnEje;
    int cantidadDeCaminos;
    Lista<pair<int, int> > listaDeCoordenadas;
    /* Guarda el defase del recorrido actual */
    int* defase;
public:
    GPS();
    ~GPS();
    void discriminarInformacion(string informacionLeida);
    void enviarCoordenadasAlMapa();
    Lista<pair<int, int> > obtenerListaDeCoordenadas();
    string obtenerCodigoDeColor();
    int* obtenerDefase();

private:
    void calcularDefase();
    void obtenerDireccion(string informacionLeida);
    void cargarCoordenada(string informacionLeida);
};

#endif // GPS_H_INCLUDED
