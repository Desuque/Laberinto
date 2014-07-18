#ifndef CAMINANTE_H_INCLUDED
#define CAMINANTE_H_INCLUDED

#include "Mochila.h"
#include "GraficadorDeMapa.h"
#include "Lista.h"
#include "Camino.h"
#include "GPS.h"

class Caminante{
private:
    Mochila* unaMochila;
    GraficadorDeMapa* unMapa;
    Lista<Camino* >* caminos;
    Camino* unCamino;
    GPS* unGPS;

public:
    /*
    * Pre: Se debe haber haber llamado previamente al CargadorDeRecorridos
    * Post: Carga los recorridos, crea la Mochila, crea lista de caminos
    */
    Caminante();

    /*
    * Pre: Recibe los caminos leidos por el CargadorDeRecorridos
    * Post: Arma la estructura de cada Camino
    */
    void logisticaDelRecorrido(Lista<Lista<std::string>*>* recorridos);

    /*
    * Pre: La Mochila debe estar creada
    * Post: Devuelve los objetos guardados en la Mochila
    */
    Lista<Objeto* >* obtenerObjetosDeLaMochila();

    /*
    * Pre: Debe existir un Camino
    * Post: Carga la informacion del camino en el Mapa
    */
    void enviarInformacionAlMapa();

    /*
    * Pre: Los caminos deben estar cargados y deben existir puntos de interes
    * Post: Llama al algoritmo de Dijkstra para poder buscar el minimo camino
    */
    void buscarAtajo();

    /*
    * Pre: El Mapa debe estar cargado
    * Post: Da la accion de dibujar la informacion cargada hasta el momento
    */
    void dibujarBMP();

    /*
    * Pre: La mochila debe estar creada
    * Post: Devuelve TRUE en caso de que la mochila contenga elementos, caso contrario devuelve FALSE
    */
    bool mochilaVacia();

    /*
    * Pre: -
    * Post: Destruye los recursor asociados al Caminante
    */
    ~Caminante();

private:
    /*
    * Pre: Debe existir un camino actual
    * Post: Separa la informacion leida del camino actual entre la Mochila y el GPS
    */
    void obtenerInformacionDel(Lista<std::string>* recorridoActual, Camino* unCamino);

    /*
    * Pre: Debe existir un camino actual
    * Post: Envia la informacion leida del camino actual a la Mochila
    */
    void enviarObjetosDelCaminoALaMochila(std::string informacionLeida);

    /*
    * Pre: Debe existir un camino actual
    * Post: Envia la informacion leida del camino actual al GPS, carga la informacion obtenida
    *       en el objeto Camino.
    */
    void enviarAccionesAlGPS(std::string informacionLeida, Camino* unCamino);

    /*
    * Pre: Todos los caminos deben estar cargados
    * Post: Separa los caminos que no tengan uniones con otros caminos, une los caminos que
    *       presentan uniones entre si. Setea el tamaño del BMP final a 150x150
    *       (Esto puede mejorarse calculando el ancho y alto total de los caminos)
    */
    void acomodarOrigen();

    /*
    * Pre: Debe haberse encontrado una union y debe saberse a que numero de camino pertenece
    * Post: Devuelve la coordenada donde debe unirse la union con la bifurcacion encontrada anteriormente
    */
    std::pair<int, int> obtenerCoordenadaDeUnion(std::string nombreUnion, int numeroCamino);

    /*
    * Pre: Debe conocerse la coordenada asociada a la union y la posicion final donde debe quedar
    *      ubicada esta union
    * Post: Devuelve el nuevo origen donde debe ubicarse el camino actual
    */
    std::pair<int, int> calcularNuevoOrigen(std::pair<int, int> coordenadaDeUnion, std::pair<int, int> posicionDeUnion);


    /*
    * Pre: los caminos deben tener pre cargados sus puntos de interes
    * Post: Carga para cada punto de interes, su ID y con que ID se une, envia la informacion a calcularPeso()
    */
    void unirPuntosDeInteres();

    /*
    * Pre: Los caminos deben estar cargados
    * Post: A cada puntoDeInteres (propios de cada Camino) le calcula su "peso" entre si mismo y el vertice
    *       con el cual se une. Esto es necesario para utilizar el algoritmo de Dijkstra
    */
    void calcularPeso();

    /*
    * Pre: La lista de caminos debe estar cargada, se le debe ingresar el nombre del puntoDeInteres a buscar
    *      este puede existir o no.
    * Post: Busca en los caminos el nombre del puntoDeInteres ingresado, al encontrarlo devuelve el ID al cual
    *       pertenece, caso contrario devuelve INF.
    */
    int obtenerUnion(std::string nombre);

    /*
    * Pre: Los caminos deben estar cargados, se le debe pasar el nombre de una UNION valida, el numero de
    *      camino hasta el cual se de debe buscar y hasta que puntoDeInteres se debe incluir en la busqueda.
    * Post: Busca en los caminos y puntosDeInteres ya recorridos que BIFURCACION lleva el mismo nombre que la
    *       union ingresada, retorna el ID asociado a la BIFURCACION, por ende, la UNION tendra este mismo ID
    *       ya que se trata del mismo punto.
    */
    int buscarUnion(std::string nombre, int caminoFin, int puntoFin);
};

#endif // CAMINANTE_H_INCLUDED
