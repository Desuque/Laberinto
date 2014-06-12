#ifndef CARGADORDERECORRIDOS_H
#define CARGADORDERECORRIDOS_H

#include <fstream>
#include "Lista.h"
#include <string>

using namespace std;

class CargadorDeRecorridos
{
    private:
        string _nombreArchivo;


    public:
        /*
        * Post: Crea un CargadorDeRecorridos sin basarse algun archivo
        */
        CargadorDeRecorridos();

        /*
        * Post: Crea un CargadorDeRecorridos basandose en el archivo indicado
        */
        CargadorDeRecorridos(string archivo);

        /*
        * Post: Devuelve tosdos los recorridos con sus instrucciones
        *       obtenidos del archivo seteado como base
        */
        Lista<Lista<string>*>* obtenerRecorridos();

        /*
        * Post: Devuelve tosdos los recorridos con sus instrucciones
        *       obtenidos del archivo indicado.
        */
        Lista<Lista<string>*>* obtenerRecorridos(string archivo);

};



#endif // CARGADORDERECORRIDOS_H
