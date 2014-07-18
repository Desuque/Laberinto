#ifndef CARGADORDEATAJOS_H_INCLUDED
#define CARGADORDEATAJOS_H_INCLUDED

#include "Lista.h"
#include "Camino.h"

class CargadorDeAtajos{
private:
    Lista<std::pair<int, int> >* pasos;
    int cantidadDeCaminos;

public:
    /*
    * Pre: Espera un puntero al camino ya creado donde se guardara la informacion del atajo
    * Post: Crea un nuevo CargadorDeAtajos sin ninguna informacion sobre el atajo
    */
    CargadorDeAtajos(Camino* caminoMasCorto);

    /*
    * Pre: Se le debe pasar una lista de recorridos (calculada con Dijkstra) y una lista de caminos.
    *      Se le pasa tambien el puntero al atajo final.
    * Post: Crea un nuevo camino, el cual corresponde al minimo entre 2 puntos, carga este nuevo camino
            en caminoMasCorto
    */
    void cargarAtajo(Lista<int>* recorridoMinimo, Lista<Camino* >* caminos, Camino* caminoMasCorto);

    /*
    * Pre:
    * Post: Libera los recursos asociados al CargadorDeAtajos
    */
    ~CargadorDeAtajos();

private:
    /*
    * Pre: Se le debe pasar un IDPartida y un IDLlegada, una lista de caminos y el total de caminos
    * Post: Encuentra a que camino particular pertenecen los ID de Partida y de Llegada
    *       envia este camino encontrado a cargarPorcionDeCamino
    */
    void buscarCamino(int IDPartida, int IDLlegada, Lista<Camino* >* caminos, int totalCaminos, Camino* caminoMasCorto);

    /*
    * Pre: Debe existir un CargadorDeAtajos y los puntos de partida y llegada deben poder unirse
    * Post: Devuelve la posicion de la listaDePasos en la que se encuentra el punto de interes ingresado
    */
    int buscarPosicion(Camino* camino, std::pair<int, int> posicion);

        /*
    * Pre: Se le debe pasar un IDPartida y un IDLlegada, un camino valido que se corresponda con estos IDs
    *      y el total de caminos a analizar
    * Post: Sabiendo a que camino pertenece el ID de Partida y de Llegada, carga en un nuevo camino
    *       los pasos contenidos entre IDPartida e IDLlegada
    */
    void cargarPorcionDeCamino(int IDPartida, int IDLlegada, Camino* unCamino, int totalCaminos, Camino* caminoMasCorto);
};

#endif // CARGADORDEATAJOS_H_INCLUDED
