#include "GPS.h"
#include <string>
#include <stdlib.h>
#include <iostream>

const int x=0;
const int y=1;

GPS::GPS(){
    this->sentidoEjeActual=0;
    this->direccionEnEje=' ';
    this->codigoDeColor="";
    this->listaDeCoordenadas = new Lista<pair<int, int> >;
    this->listaDePasos = new Lista<pair<int, int> >;
    this->coordenadasPorMarcar = new Lista<pair<int, int> >;
    this->bifurcaciones = new Lista<Bifurcacion>;
    this->MaximoX=0;
    this->MaximoY=0;
    this->MinimoX=0;
    this->MinimoY=0;
}

void GPS::discriminarInformacion(string informacionLeida){
    if ( (informacionLeida[0]=='P') && (informacionLeida[1]=='P') ){
        cargarColorActual(informacionLeida);
    }
    else if (informacionLeida[0]=='G'){
        obtenerDireccion(informacionLeida);
    }
    else if ( (informacionLeida[0]=='A')){
        cargarCoordenada(informacionLeida);
    }
    else if ( (informacionLeida[0]=='L') || (informacionLeida[0]=='T') ){
        cargarCoordenadasPorMarcar();
    }
    /*
    else if (informacionLeida[0]=='B'){
        cargarBifurcacion(informacionLeida);*/
    /* Las bifurcaciones tambien deben marcarse en el Mapa, por lo que agrego la coordenada*/
    /*    cargarCoordenadasPorMarcar();
    }
    else if (informacionLeida[0]=='U'){
    }
    */
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

void GPS::calcularNuevoOrigen(){
    listaDeCoordenadas->iniciarCursor();
    while (listaDeCoordenadas->avanzarCursor()){
        if (listaDeCoordenadas->obtenerCursor().first>MaximoX){
            MaximoX=listaDeCoordenadas->obtenerCursor().first;
        }
        else if (listaDeCoordenadas->obtenerCursor().first<MinimoX){
            MinimoX=listaDeCoordenadas->obtenerCursor().first;
        }
        else if (listaDeCoordenadas->obtenerCursor().second>MaximoY){
            MaximoY=listaDeCoordenadas->obtenerCursor().first;
        }
        else if (listaDeCoordenadas->obtenerCursor().first<MinimoY){
            MinimoX=listaDeCoordenadas->obtenerCursor().first;
        }
    }

    nuevoOrigen=make_pair(abs(MinimoX),abs(MinimoY));
}

pair<int, int> GPS::obtenerNuevoOrigen(){
    calcularNuevoOrigen();
    return this->nuevoOrigen;
}

void GPS::cargarCoordenada(string informacionLeida){
    string pasosAuxiliar="";
    int pasos=0;
    for (unsigned int i=2; i<informacionLeida.length(); i++){
        pasosAuxiliar+=informacionLeida[i];
    }
    istringstream convert(pasosAuxiliar);
    convert>>pasos;

    /* Guardo los pasos segun su direccion y sentido */
    pasos=pasos*sentidoEjeActual;

    pair<int, int> posicionActual=obtenerPosicionActual();

    if ((direccionEnEje=='N') || (direccionEnEje=='S')){
        listaDeCoordenadas->agregar(make_pair(posicionActual.first,posicionActual.second+pasos));
        listaDePasos->agregar(make_pair(0,pasos));
    }
    else if ((direccionEnEje=='O') || (direccionEnEje=='E')){
        listaDeCoordenadas->agregar(make_pair(posicionActual.first+pasos,posicionActual.second));
        listaDePasos->agregar(make_pair(pasos,0));
    }
}

void GPS::vaciarListaDePasos(){
    delete listaDePasos;
    this->listaDePasos = new Lista<pair<int, int> >;
}

void GPS::vaciarListaDeCoordenadas(){
    delete listaDeCoordenadas;
    this->listaDeCoordenadas = new Lista<pair<int, int> >;
}

Lista<pair<int, int> >* GPS::obtenerListaDeCoordenadas(){
    return this->listaDeCoordenadas;
}

Lista<pair<int, int> >* GPS::obtenerListaDePasos(){
    return this->listaDePasos;
}

void GPS::cargarCoordenadasPorMarcar(){
    coordenadasPorMarcar->agregar(obtenerPosicionActual());
}

Lista<pair<int, int> >* GPS::obtenerCoordenadasPorMarcar(){
    return this->coordenadasPorMarcar;
}

pair<int, int> GPS::obtenerPosicionActual(){
    int coordenadaX;
    int coordenadaY;

    if (listaDeCoordenadas->contarElementos()!=0){
        coordenadaX=listaDeCoordenadas->obtener(listaDeCoordenadas->contarElementos()).first;
        coordenadaY=listaDeCoordenadas->obtener(listaDeCoordenadas->contarElementos()).second;
    }
    else{
        coordenadaX=0;
        coordenadaY=0;
    }

    pair<int, int> posicionActual=make_pair(coordenadaX, coordenadaY);
    return posicionActual;
}

void GPS::cargarBifurcacion(string bifurcacion){
    Bifurcacion unaBifurcacion;
    string nombre;
    for(unsigned int i=2; i<bifurcacion.length(); i++){
        nombre+=bifurcacion[i];
    }
    /* Obtiene si la bifurcacion es en sentido N S O E */
    char sentido=bifurcacion[1];

    unaBifurcacion.cargarBifurcacion(nombre, sentido, obtenerPosicionActual());
    bifurcaciones->agregar(unaBifurcacion);
}


GPS::~GPS(){
}
