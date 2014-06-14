#include "GPS.h"
#include <string>
#include <stdlib.h>
#include <iostream>

const int x=0;
const int y=1;

GPS::GPS(){
    this->sentidoEjeActual=0;
    this->cantidadDeCaminos=0;
    this->direccionEnEje=' ';
    this->codigoDeColor="";
    this->nuevoOrigen = new int[2];
    this->listaDeCoordenadasRelativas = new Lista<pair<int, int> >;
    this->listaDeCoordenadas = new Lista<pair<int, int> >;
    maxEste=0, maxOeste=0, maxNorte=0, maxSur=0, xActual=0, yActual=0;
}

void GPS::discriminarInformacion(string informacionLeida){
    if ( (informacionLeida[0]=='P') && (informacionLeida[1]=='P') ){
        cargarColorActual(informacionLeida);
    }
    else if (informacionLeida[0]=='G'){
        obtenerDireccion(informacionLeida);
    }
    else if ( (informacionLeida[0]=='A') || (informacionLeida=="PLL") ){
        calcularNuevoOrigen(informacionLeida);
        if (informacionLeida!="PLL"){
            cargarCoordenada(informacionLeida);
        }
    }
}

void GPS::cargarColorActual(string rgb){
    int codigoDeColor=0;
    int j=0;
    string rgbAuxiliar;
    for(unsigned int i=3; i<rgb.length(); i++){
        if((rgb[i])!=' '){
            rgbAuxiliar=rgbAuxiliar+rgb[i];
        }
        else{
            istringstream convert(rgbAuxiliar);
            convert>>codigoDeColor;
            colorActual[j]=codigoDeColor;
            rgbAuxiliar="";
            j++;
        }
    }
    istringstream convert(rgbAuxiliar);
    convert>>codigoDeColor;
    colorActual[j]=codigoDeColor;
}

int* GPS::obtenerCodigoDeColor(){
    return this->colorActual;
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

void GPS::calcularNuevoOrigen(string informacionLeida){
    if (informacionLeida!="PLL"){

        //Metodo a parte
        string coordenadaAuxiliar="";
        int coordenada=0;
        for (unsigned int i=2; i<informacionLeida.length(); i++){
            coordenadaAuxiliar+=informacionLeida[i];
        }
        istringstream convert(coordenadaAuxiliar);
        convert>>coordenada;
        //Metodo a parte

        if (direccionEnEje == 'E'){
            xActual = xActual + coordenada;
            if (xActual > maxEste){
                maxEste = xActual;
            }
        }

        if(direccionEnEje == 'O'){
            xActual = xActual - coordenada;
            if (xActual < maxOeste){
                maxOeste = xActual;
            }
        }

        if(direccionEnEje == 'N'){
            yActual = yActual + coordenada;
            if (yActual < maxNorte){
                maxNorte = yActual;
            }
        }

        if(direccionEnEje == 'S'){
            yActual = yActual + coordenada;
            if (yActual > maxSur){
                maxSur = yActual;
            }
        }
    }
    else{
        this->nuevoOrigen[x]=abs(maxOeste);
        this->nuevoOrigen[y]=abs(maxNorte);
    }
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
        listaDeCoordenadas->agregar(make_pair(0,coordenada));
    }
    else if ((direccionEnEje=='O') || (direccionEnEje=='E')){
        listaDeCoordenadas->agregar(make_pair(coordenada,0));
    }
    cout<<coordenada<<endl;
}

void GPS::generarListaDeCoordenadasRelativas(){
    /*No sirve, asi que esto no hace nada por ahora */
    listaDeCoordenadasRelativas=listaDeCoordenadas;
}

void GPS::vaciarListaDeCoordenadas(){
    delete listaDeCoordenadas;
    this->listaDeCoordenadas = new Lista<pair<int, int> >;
}

Lista<pair<int, int> >* GPS::obtenerListaDeCoordenadasRelativas(){
    return this->listaDeCoordenadasRelativas;
}

GPS::~GPS(){
}
