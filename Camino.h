#ifndef CAMINO_H_INCLUDED
#define CAMINO_H_INCLUDED

#include "Lista.h"
#include "PuntoDeInteres.h"

class Camino{
private:
    int color[3];
    std::pair<int, int> origen;
    Lista<std::pair<int, int> >* listaDePasos;
    Lista<std::pair<int, int> >* coordenadasPorMarcar;
    Lista<PuntoDeInteres* >* puntosDeInteres;
    Lista<PuntoDeInteres* >* uniones;
    int* MaximoX;
    int* MinimoX;
    int* MaximoY;
    int* MinimoY;

public:
    /*
    * Pre:
    * Post: Se crea un nuevo camino sin informacion
    */
    Camino();

    /*
    * Pre: El color debe ser con formato "-- <R G B>"
    * Post: Carga el color del camino actual
    */
    void cargarColor(std::string rgb);

    /*
    * Pre: El origen debe ser una coordenada valida para la libreria EasyBMP (Positiva en X e Y)
    * Post: Setea el origen del camino actual
    */
    void cargarOrigen(std::pair<int, int> origen);

    /*
    * Pre:
    * Post: Setea la lista de pasos del camino actual
    */
    void cargarListaDePasos(Lista<std::pair<int, int> >* listaDePasos);

    /*
    * Pre:
    * Post: Setea las coordenadas en las cuales debe establecerse una marca (Objetos y bifurcaciones)
    */
    void cargarCoordenadasPorMarcar(Lista<std::pair<int, int> >* coordenadasPorMarcar);

    /*
    * Pre:
    * Post: Setea los puntos de interes del camino actual (PP PLL B U)
    */
    void cargarPuntosDeInteres(Lista<PuntoDeInteres* >* puntosDeInteres);

    /*
    * Pre:
    * Post: Setea las uniones del camino actual respecto a las bifurcaciones de los caminos anteriores
    */
    void cargarUniones(Lista<PuntoDeInteres* >* uniones);

    /*
    * Pre:
    * Post: Setea los Maximos y Minimos del camino actual
    */
    void cargarMaxMin(int* MaximoX, int* MinimoX, int* MaximoY, int* MinimoY);

    /*
    * Pre: El origen del camino actual debe estar seteado
    * Post: Devuelve el origen del camino actual, por defecto es el (0,0)
    */
    std::pair<int, int> obtenerOrigen();

    /*
    * Pre: Los puntos de interes deben estar seteados
    * Post: Devuelve los puntos de interes del camino actual
    */
    Lista<PuntoDeInteres* >* obtenerPuntosDeInteres();

    /*
    * Pre: Las coordenadas por marcar deben estar seteadas
    * Post: Devuelve las coordenadas por marcar del camino actual
    */
    Lista<std::pair<int, int> >* obtenerCoordenadasPorMarcar();

    /*
    * Pre: Las uniones del camino deben estar seteadas
    * Post: Devuelve las uniones correspondientes al camino actual
    */
    Lista<PuntoDeInteres* >* obtenerUniones();

    /*
    * Pre: El color debe estar cargado
    * Post: Devuelve el color asociado al camino actual
    */
    int* obtenerColor();

    /*
    * Pre: La lista de pasos debe estar seteada
    * Post: Devuelve la lista de pasos asociada al camino actual
    */
    Lista<std::pair<int, int> >* obtenerListaDePasos();

    /*
    * Pre:
    * Post: Devuelve el maximo valor de la coordenada X calculada para el recorrido actual
    */
    int* obtenerMaximoX();

    /*
    * Pre:
    * Post: Devuelve el minimo valor de la coordenada X calculada para el recorrido actual
    */
    int* obtenerMinimoX();

    /*
    * Pre:
    * Post: Devuelve el maximo valor de la coordenada Y calculada para el recorrido actual
    */
    int* obtenerMaximoY();

    /*
    * Pre:
    * Post: Devuelve el minimo valor de la coordenada Y calculada para el recorrido actual
    */
    int* obtenerMinimoY();

    /*
    * Pre:
    * Post: Libera los recursos asociados al Camino
    */
    ~Camino();
};

#endif // CAMINO_H_INCLUDED
