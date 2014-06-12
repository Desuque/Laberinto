#include<iostream>
#include "CargadorDeRecorridos.h"

CargadorDeRecorridos::CargadorDeRecorridos()
{

}

CargadorDeRecorridos::CargadorDeRecorridos(string archivo)
{
    this->_nombreArchivo = archivo;
}

Lista<Lista<string>*>* CargadorDeRecorridos::obtenerRecorridos()
{
    return (this->obtenerRecorridos(this->_nombreArchivo));
}


Lista<Lista<string>*>* CargadorDeRecorridos::obtenerRecorridos(string archivoNombre)
{
    Lista<Lista<string>*>* listaRecorridos;
    listaRecorridos = new Lista<Lista<string>*>();

    ifstream archivo;
    archivo.open(archivoNombre.c_str());
    if (archivo != NULL)
    {
        string line,lineSubs;
        while(!archivo.eof())
        {
            Lista<string>* recorridoActual;
            getline(archivo,line);

            //si el principio de un recorrido creo uno
            if (((line != "")) and (line.substr(0,2)=="PP"))
            {
                recorridoActual = new Lista<string>();
                recorridoActual->agregar(line);
            }

            //si no es un comentario ni el final de un recorrido
            else if (((line.substr(0,2)!= "PL"))and (line.substr(0,2)!= "--"))
                recorridoActual->agregar(line);

            //si ese recorrido termino
            if(line.substr(0,2) == "PL")
            {
                recorridoActual->agregar(line);
                listaRecorridos->agregar(recorridoActual);
            }
        }
    }
    archivo.close();
    return listaRecorridos;
}
