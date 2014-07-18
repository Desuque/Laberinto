#ifndef GRAFICADORDEMAPA_H_INCLUDED
#define GRAFICADORDEMAPA_H_INCLUDED

#include "Lista.h"
#include "EasyBMP.h"

class GraficadorDeMapa{
private:
    BMP Laberinto;
    std::string pasos;
    int pasosHorizontales;
    int pasosVerticales;
    int coordenadaVertical;
    int coordenadaHorizontal;
    int tamanioDelRecorrido[2];
    int* colorActual;
    std::pair<int, int> origen;
    std::string rgb;
    int anchoBMP;
    int altoBMP;

public:
    /*
    * Pre: -
    * Post: Crea un nuevo Mapa sin tamanio ni informacion asociada
    */
    GraficadorDeMapa();

    /*
    * Pre: El Mapa debe estar creado
    * Post: Setea el nuevo tamanio del BMP final, este valor no puede modificarse una vez que se
    *       cargo informacion en el Mapa, caso contrario se borrara lo cargado hasta el momento
    */
    void cargarTamanioBMP(int anchoBMP, int altoBMP);

    /*
    * Pre: El Mapa debe estar creado
    * Post: Setea el origen del recorrido que se quiere dibujar, a partir de este punto
    *       se comenzara a dibujar el camino
    */
    void cargarOrigen(std::pair<int, int> origen);

    /*
    * Pre: El Mapa debe estar creado
    * Post: Setea el color del recorrido que se quiere dibujar, hasta que vuelva a cargarse
    *       un nuevo color, todos los caminos que se dibujen seran con este codigo RGB
    */
    void cargarColor(int* rgb);

    /*
    * Pre: El Mapa debe estar creado y el recorrido ingresado no debe superar al ancho y
    *      alto asignados al BMP
    * Post: Carga el recorrido en el Mapa
    */
    void cargarRecorrido(Lista<std::pair<int, int> >* listaDeCoordenadas);

    /*
    * Pre: El Mapa debe estar creado. El camino sobre el cual se espera marcar (bifuraciones y elementos)
    *      debe estar previamente cargado
    * Post: Carga los objetos sobre el recorrido
    */
    void marcarObjetos(Lista<std::pair<int, int> >* coordenadasPorMarcar);

    /*
    * Pre: El Mapa debe existir
    * Post: Se dibuja en un archivo BMP la informacion cargada hasta el momento en el Mapa
    */
    void dibujarRecorridos();

    /*
    * Pre:
    * Post: Libera los recursos asociados al Mapa
    */
    ~GraficadorDeMapa();

private:
    /*
    * Pre: El ancho y alto del BMP deben estar cargados
    * Post: Plasma las coordenadas N S O E sobre el BMP final
    */
    void marcarEjes();
};

#endif // GRAFICADORDEMAPA_H_INCLUDED
