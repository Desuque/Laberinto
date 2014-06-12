#include "GPS.h"
#include "Mapa.h"
#include <string>
#include <stdlib.h>
#include <iostream>

GPS::GPS(){
    this->sentidoEjeActual=0;
    this->cantidadDeCaminos=0;
    this->direccionEnEje=' ';
    this->codigoDeColor="";
    this->defase = new int[2];
}

string GPS::obtenerCodigoDeColor(){
    return this->codigoDeColor;
}

void GPS::discriminarInformacion(string informacionLeida){
    if (informacionLeida!="PLL"){
        if ( (informacionLeida[0]=='P') && (informacionLeida[1]=='P') ){
            this->codigoDeColor=informacionLeida;
        }
        else if (informacionLeida[0]=='G'){
            obtenerDireccion(informacionLeida);
        }
        else if (informacionLeida[0]=='A'){
            cargarCoordenada(informacionLeida);
        }
    }
    else{
        /* Cuando termina un camino, se asigna un margen en X arbitrario */

        //FALTA PROGRAMARLO

    }
}

void GPS::obtenerDireccion(string informacionLeida){
    this->direccionEnEje=informacionLeida[1];
    if ( (informacionLeida[1]=='N') || (informacionLeida[1]=='O') ){
        this->sentidoEjeActual=-1;
    }
    if ( (informacionLeida[1]=='S') || (informacionLeida[1]=='E') ){
        this->sentidoEjeActual=1;
    }
}

void GPS::calcularDefase(){
    /*
    * Si los pasos totales quedan en negativo, significa que se salio del origen
    * (0,0) impuesto por la libreria EasyBMP, por lo tanto, reacomodamos el origen
    * sumando a todos los pasos el modulo del corrimiento calculado.
    */

    int pasosTotalesX=0;
    int pasosTotalesY=0;

    listaDeCoordenadas.iniciarCursor();
    while (listaDeCoordenadas.avanzarCursor()){
        if (pasosTotalesX>(listaDeCoordenadas.obtenerCursor()).first ){
            pasosTotalesX += (listaDeCoordenadas.obtenerCursor()).first;
        }
        pasosTotalesY += (listaDeCoordenadas.obtenerCursor()).second;
    }

    if (pasosTotalesX<0){
        pasosTotalesX=abs(pasosTotalesX);
    }
    else{
        pasosTotalesX=0;
    }

    if (pasosTotalesY<0){
        pasosTotalesY=abs(pasosTotalesY);
    }
    else{
        pasosTotalesY=0;
    }

    defase[0]=pasosTotalesX;
    defase[1]=pasosTotalesY;

    cout<<pasosTotalesX<<endl;
    cout<<pasosTotalesY<<endl;
}

int* GPS::obtenerDefase(){
    return this->defase;
}


void GPS::cargarCoordenada(string informacionLeida){
    string coordenadaAuxiliar="";
    int coordenada=0;
    for (unsigned int i=2; i<informacionLeida.length(); i++){
        coordenadaAuxiliar+=informacionLeida[i];
    }
    istringstream convert(coordenadaAuxiliar);
    convert>>coordenada;

    /* Guardo las coordenadas segun su direccion y sentido */
    coordenada=coordenada*sentidoEjeActual;

    if ((direccionEnEje=='N') || (direccionEnEje=='S')){
        listaDeCoordenadas.agregar(make_pair(0,coordenada));
    }
    else if ((direccionEnEje=='O') || (direccionEnEje=='E')){
        listaDeCoordenadas.agregar(make_pair(coordenada,0));
    }
}

Lista<pair<int, int> > GPS::obtenerListaDeCoordenadas(){
    //calcularDefase();
    return this->listaDeCoordenadas;
}

GPS::~GPS(){
}
