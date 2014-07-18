#ifndef CARGADORDERECORRIDOS_H
#define CARGADORDERECORRIDOS_H

#include "Lista.h"

class CargadorDeRecorridos
{
    public:
        /*
        * Post: Crea un CargadorDeRecorridos sin basarse algun archivo
        */
        CargadorDeRecorridos();

        /*
        * Post: Carga todos los recorridos con sus instrucciones
        *       obtenidos del archivo indicado.
        */
        void cargarRecorridos(std::string archivo, Lista<Lista<std::string>*>* listaRecorridos);

        /*
        * Post: Libera los recursos asociados al cargadorDeRecorridos
        */
        ~CargadorDeRecorridos();
};

#endif // CARGADORDERECORRIDOS_H
