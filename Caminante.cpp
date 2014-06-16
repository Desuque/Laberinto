#include "Caminante.h"
#include "Mochila.h"
#include "GPS.h"
#include "Mapa.h"
#include <string>

using namespace std;

Caminante::Caminante(Lista<Lista<string>*>* recorridos){
    this->recorridos = recorridos;
    this->unaMochila = new Mochila();
}

void Caminante::logisticaDelRecorrido(Lista<Lista<string>*>* recorridos){
    Lista<string>* recorridoActual;

    recorridos->iniciarCursor();
    while (recorridos->avanzarCursor()){
        recorridoActual = recorridos->obtenerCursor();
        obtenerInformacionDel(recorridoActual);
        enviarInformacionAlMapa();
    }
}

void Caminante::obtenerInformacionDel(Lista<string>* recorridoActual){
    string informacionLeida;;
    recorridoActual->iniciarCursor();
    while (recorridoActual->avanzarCursor()){
        informacionLeida = recorridoActual->obtenerCursor();
        /* Se envian los objetos señalados en el recorrido a la Mochila */
        enviarObjetosDelCaminoALaMochila(informacionLeida);

        /* Se envia la informacion del caminante al GPS */
        enviarAccionesAlGPS(informacionLeida);
    }
}

void Caminante::enviarObjetosDelCaminoALaMochila(string informacionLeida){
    if ((informacionLeida[0]=='L') or (informacionLeida[0]=='T')){
        unaMochila->enviar(informacionLeida);
    }
}

void Caminante::enviarAccionesAlGPS(string informacionLeida){
    /*
    * La informacion no se filtra ya que el GPS necesita conocer, ademas de los pasos y bifurcaciones
    * los lugares donde se ha levantado o dejado un Objeto
    */
    unGPS.discriminarInformacion(informacionLeida);
}



void Caminante::enviarInformacionAlMapa(){
    unMapa.cargarColor(unGPS.obtenerCodigoDeColor());
    unMapa.cargarNuevoOrigen(unGPS.obtenerNuevoOrigen());
    unMapa.cargarRecorrido(unGPS.obtenerListaDePasos());
    //unMapa.marcarObjetos(unGPS.obtenerCoordenadasPorMarcar());

    unGPS.vaciarListaDePasos();
    //unGPS.vaciarListaDeCoordenadas();



}

void Caminante::dibujarBMP(){
    unMapa.dibujarRecorridos();
}

Lista<Objeto>* Caminante::obtenerObjetosDeLaMochila(){
    return unaMochila->obtenerObjetos();
}

Caminante::~Caminante(){
    delete unaMochila;
}
