#ifndef GPS_H_INCLUDED
#define GPS_H_INCLUDED

#include "Lista.h"
#include "Camino.h"
#include "PuntoDeInteres.h"

class GPS{
private:
    int sentidoEjeActual;
    char direccionEnEje;
    Lista<std::pair<int, int> >* listaDeCoordenadas;
    Lista<std::pair<int, int> >* listaDePasos;
    Lista<std::pair<int, int> >* coordenadasPorMarcar;
    Lista<PuntoDeInteres* >* puntosDeInteres;
    Lista<PuntoDeInteres* >* uniones;
    std::pair<int, int> nuevoOrigen;
    int* MaximoX;
    int* MinimoX;
    int* MaximoY;
    int* MinimoY;
    int numeroID;

public:
    /*
    * Pre:
    * Post: Crea un nuevo GPS sin informacion asociada
    */
    GPS();

    /*
    * Pre: El GPS debe estar previamente creado
    * Post: Se divide la informacion de llegada segun las acciones esperadas, envia toda
    *       la informacion recopilada a un nuevo camino
    */
    void discriminarInformacion(std::string informacionLeida, Camino* unCamino);

    /*
    * Pre: El codigo de color debe ser ingresado luego de "PP " separando los codigos por espacios
    *      Debe existir un camino asociado
    * Post: Se envia el color ingresado al camino asociado
    */
    void cargarColor(std::string rgb, Camino* unCamino);

    /*
    * Pre: Deben existir una serie de coordenadas por marcar
    * Post: Se guardan las coordenadas en las cuales debe considerarse una marca (Bifurcaciones y Objetos)
    */
    void cargarCoordenadasPorMarcar();

    /*
    * Pre:
    * Post: Libera los recursos asociados al GPS
    */
    ~GPS();

private:
    /*
    * Pre:
    * Post: Se guarda el nombre, sentido y coordenada del punto de interes (PP PLL Bifurcaciones Uniones)
    */
    void cargarPuntoDeInteres(std::string punto);

    /*
    * Pre: La informacion leida debe contar con la direccion del eje (N S O E)
    * Post: Carga la direccion actual sobre el eje (si es negativo o positivo)
    */
    void obtenerDireccion(std::string informacionLeida);

    /*
    * Pre: Debe existir una lista de coordenadas
    * Post: Se crea una nueva lista de coordenadas vacia, eliminando los recursos asociados a la anterior
    */
    void vaciarListaDeCoordenadas();

    /*
    * Pre: La lista de coordenadas debe estar cargada
    * Post: Calcula el maximo y minimo del camino actual sobre los ejes
    */
    void calcularMaximosyMinimos();

    /*
    * Pre: Debe existir una lista de pasos, una lista de coordenadas y un camino
    * Post: Se asocia la lista de pasos al camino y se crea una lista de coordenadas del camino actual
    */
    void cargarCoordenada(std::string informacionLeida, Camino* unCamino);

    /*
    * Pre: La lista de coordenadas debe estar cargada
    * Post: Obtiene la posicion actual del camino, al momento de llamar el metodo
    */
    std::pair<int, int> obtenerPosicionActual();
};

#endif // GPS_H_INCLUDED
