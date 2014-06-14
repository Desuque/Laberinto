#ifndef GPS_H_INCLUDED
#define GPS_H_INCLUDED

#include <string>
#include "Lista.h"

using namespace std;

class GPS{
private:
    int sentidoEjeActual;
    char direccionEnEje;
    int cantidadDeCaminos;
    Lista<pair<int, int> >* listaDeCoordenadas;
    Lista<pair<int, int> >* listaDeCoordenadasRelativas;
    string codigoDeColor;

    int colorActual[3];

    /* Guarda el defase del recorrido actual */
    int* nuevoOrigen;

    /* Variables usadas para el calculo del nuevo origen */

    int maxEste, maxOeste, maxNorte, maxSur, xActual, yActual;

public:
    GPS();
    ~GPS();
    void discriminarInformacion(string informacionLeida);
    void enviarCoordenadasAlMapa();
    Lista<pair<int, int> >* obtenerListaDeCoordenadasRelativas();
    void cargarColorActual(string rgb);
    int* obtenerCodigoDeColor();
    void generarListaDeCoordenadasRelativas();
    void vaciarListaDeCoordenadas();

private:
    void calcularNuevoOrigen(string informacionLeida);
    void obtenerDireccion(string informacionLeida);
    void cargarCoordenada(string informacionLeida);
};

#endif // GPS_H_INCLUDED
