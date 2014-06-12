#include <stdio.h>
#include "Objeto.h"
#include "Mochila.h"
#include "Lista.h"

using namespace std;

Mochila::Mochila(){
    this->objetosGuardados = new Lista<Objeto>;
}

bool Mochila::objetoEstaEnMochila(string nombreObjeto){
    bool encontrado=false;
    this->objetosGuardados->iniciarCursor();
    while ( (this->objetosGuardados->avanzarCursor()) && (!encontrado) ){
        if ( ((this->objetosGuardados->obtenerCursor()).obtenerNombre() ) == (nombreObjeto) ){
            encontrado=true;
        }
    }
    return encontrado;
}

int Mochila::obtenerCantidadDeObjeto(string nombreObjeto){
    unsigned int cantidadActual = 0;
    this->objetosGuardados->iniciarCursor();
    while ( (this->objetosGuardados->avanzarCursor()) && (cantidadActual==0) ){
        if ( ((this->objetosGuardados->obtenerCursor()).obtenerNombre() ) == (nombreObjeto) ){
            cantidadActual=(this->objetosGuardados->obtenerCursor()).obtenerCantidad();
        }
    }
    return cantidadActual;
}

void Mochila::eliminarObjeto(string nombreObjeto){
    unsigned int posicionActual=0;
    this->objetosGuardados->iniciarCursor();
    while ( (this->objetosGuardados->avanzarCursor()) ){
        posicionActual++;
        if ( ((this->objetosGuardados->obtenerCursor()).obtenerNombre() ) == (nombreObjeto) ){
            objetosGuardados->remover(posicionActual);
        }
    }
}

void Mochila::agregarObjeto(string nombreObjeto){
    /* Si la lista de objetosGuardados esta vacia, lo guarda */
    if (objetosGuardados->contarElementos()==0){
        Objeto unObjeto(nombreObjeto);
        this->objetosGuardados->agregar(unObjeto);
    }

    /* Si no, compara para ver que el elemento no exista en la mochila */
    /* Si no existe, lo agrega. Si no, incrementa la cantidad del elemento */
    else{
        if (!objetoEstaEnMochila(nombreObjeto)){
            Objeto unObjeto(nombreObjeto);
            this->objetosGuardados->agregar(unObjeto);
        }
        else{
            unsigned int cantidadActual = obtenerCantidadDeObjeto(nombreObjeto);
            eliminarObjeto(nombreObjeto);
            /* Creo un nuevo objeto con la cantidad total */
            Objeto unObjeto(nombreObjeto, cantidadActual+1);
            this->objetosGuardados->agregar(unObjeto);
        }
    }
}

void Mochila::enviar(string informacionLeida){
    string nombreObjeto = obtenerNombreObjeto(informacionLeida);
    if (informacionLeida[0]=='L'){
        agregarObjeto(nombreObjeto);
    }
    else if (informacionLeida[0]=='T'){

        if (obtenerCantidadDeObjeto(nombreObjeto)==1){
            eliminarObjeto(nombreObjeto);
        }
        else{
            unsigned int cantidadActual=obtenerCantidadDeObjeto(nombreObjeto);
            eliminarObjeto(nombreObjeto);
            /* Creo un nuevo objeto con la cantidad total */
            Objeto unObjeto(nombreObjeto, cantidadActual-1);
            this->objetosGuardados->agregar(unObjeto);
        }
    }
}

string Mochila::obtenerNombreObjeto(string informacionLeida){
    string nombreObjeto;
    for(unsigned int i=2; i<informacionLeida.length(); i++){
        nombreObjeto+=informacionLeida[i];
    }
    return nombreObjeto;
}

Lista<Objeto>* Mochila::obtenerObjetos(){
    return this->objetosGuardados;
}

Mochila::~Mochila(){
}
