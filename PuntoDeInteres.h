#ifndef PUNTODEINTERES_H_INCLUDED
#define PUNTODEINTERES_H_INCLUDED

#include <string>

class PuntoDeInteres{
private:
    std::string nombre;
    std::pair<int, int> posicion;
    int ID;
    int numeroCamino;
    int peso;
public:
    /*
    * Pre: Crea un nuevo Punto de Interes vacio
    * Post:
    */
    PuntoDeInteres();

    /*
    * Pre: Debe existir un Punto de Interes
    * Post: Asigna nombre, sentido y posicion (coordenadas) del punto de interes respecto a un camino
    */
    void cargarPuntoDeInteres(std::string nombre, std::pair<int, int> posicion);

    /*
    * Pre: Debe existir un Punto de Interes
    * Post: Devuelve el nombre asociado al punto de interes
    */
    std::string obtenerNombre();

    /*
    * Pre: Debe existir un Punto de Interes
    * Post: Obtiene las coordenadas asociadas al punto de interes respecto a un camino
    */
    std::pair<int, int> obtenerPosicion();

    /*
    * Pre: Debe existir un Punto de Interes
    * Post: Carga el numero de ID asociado al puntoDeInteres
    */

    void cargarID(int IDActual);

    /*
    * Pre: Debe existir un Punto de Interes
    * Post: Obtiene el ID asociado al puntoDeInteres actual
    */
    int obtenerID();

    /*
    * Pre: Debe existir un Punto de Interes
    * Post: Carga el numero de ID con el cual se une el puntoDeInteres actual
    */
    void cargarSeUneCon(int numeroCamino);

    /*
    * Pre: Debe existir un Punto de Interes
    * Post: Carga el peso entre el puntoDeInteres actual y el vertcie al cual se une
    */
    void cargarPeso(int peso);

    /*
    * Pre: Debe existir un Punto de Interes
    * Post: Obtiene el peso asociado al puntoDeInteres actual y el vertice al cual se une
    */
    int obtenerPeso();

    /*
    * Pre: Debe existir un Punto de Interes
    * Post: Obtiene el ID al cual se une el puntoDeInteres actual
    */
    int obtenerUnion();

    /*
    * Pre:
    * Post: Libera los recursos asociados al Punto de Interes
    */
    ~PuntoDeInteres();
};

#endif // PUNTODEINTERES_H_INCLUDED
