#include "CargadorDeRecorridos.h"
#include <fstream>

using namespace std;

CargadorDeRecorridos::CargadorDeRecorridos()
{

}

void CargadorDeRecorridos::cargarRecorridos(string archivoNombre, Lista<Lista<string>*>* listaRecorridos)
{
    ifstream archivo;
    archivo.open(archivoNombre.c_str());
    if (archivo != NULL)
    {
        string line;

        while(!archivo.eof()){
            Lista<string>* recorridoActual;
            getline(archivo,line);

            //si el principio de un recorrido creo uno
            if (((line != "")) && (line.substr(0,2)=="PP"))
            {
                recorridoActual = new Lista<string>();
            }

            if ((line.substr(0,1)=="U") || (line.substr(0,1)=="B")){
                line=line.substr(0,line.length()-1);
                recorridoActual->agregar(line);
            }

            //si no es un comentario ni el final de un recorrido
            if (((line.substr(0,2)!= "PL")||(line.substr(0,2)=="PP")) && (line.substr(0,2)!= "--")){
                recorridoActual->agregar(line);
            }

            //si ese recorrido termino
            if(line.substr(0,2) == "PL"){
                line=line.substr(0,line.length()-1);
                recorridoActual->agregar(line);
                listaRecorridos->agregar(recorridoActual);
            }
    }
    archivo.close();
    }
}

CargadorDeRecorridos::~CargadorDeRecorridos(){
}
