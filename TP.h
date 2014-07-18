#ifndef TP_H_INCLUDED
#define TP_H_INCLUDED

#include "Caminante.h"

class TP{
private:
    Caminante* unCaminante;

public:
    /*
    * Pre:
    * Post: Crea un nuevo Caminante, listo para ser cargado
    */
    TP();

    /*
    * Pre: El TP debe estar creado
    * Post: Pide la ruta del archivo de caminos, se encarga de llamar a los metodos que resuelven el problema
    */
    void iniciar();

    /*
    * Pre:
    * Post: Libera los recursos asociados al TP
    */
    ~TP();

private:
    /*
    * Pre: El usuario debe ingresar una ruta de archivo valida
    * Post: Carga el recorrido en memoria y se lo envia al Caminante
    */
    void cargarRecorridos(std::string archivoDeCaminos, Lista<Lista<std::string>*>* recorridos);

    /*
    * Pre:
    * Post: Muestra por pantalla el estado actual de la Mochila
    */
    void obtenerMochila();

    /*
    * Pre:
    * Post: Envia la informacion al BMP
    */
    void enviarInformacionAlGraficador();

    /*
    * Pre:
    * Post: Busca atajos entre 2 puntos de interes y lo marca en el mapa final con color Amarillo
    */
    void buscarAtajo();

    /*
    * Pre:
    * Post: Imprime en el BMP final la informacion cargada hasta el momento
    */
    void dibujarBMP();
};

#endif // TP_H_INCLUDED
