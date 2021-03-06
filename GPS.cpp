#include "GPS.h"

#define INF 1<<30

using namespace std;

const int x=0;
const int y=1;

GPS::GPS(){
    this->sentidoEjeActual=0;
    this->direccionEnEje=' ';
    this->listaDeCoordenadas = new Lista<pair<int, int> >;
    this->numeroID=0;
}

void GPS::discriminarInformacion(string informacionLeida, Camino* unCamino){
    if ( (informacionLeida[0]=='P') && (informacionLeida[1]=='P') ){
        /*
        * Al iniciar un nuevo recorrido creo una lista de pasos,
        * una lista de coordendas por marcar, una lista de puntos de interes
        * (necesarios para el TP2) y una lista de uniones.
        */
        this->listaDePasos = unCamino->obtenerListaDePasos();
        this->coordenadasPorMarcar = unCamino->obtenerCoordenadasPorMarcar();
        this->puntosDeInteres = unCamino->obtenerPuntosDeInteres();
        this->uniones = unCamino->obtenerUniones();

        cargarColor(informacionLeida, unCamino);
        cargarPuntoDeInteres(informacionLeida);
    }
    else if (informacionLeida[0]=='G'){
        obtenerDireccion(informacionLeida);
    }
    else if (informacionLeida[0]=='A'){
        cargarCoordenada(informacionLeida, unCamino);
    }
    else if (informacionLeida[0]=='R'){
        cargarCoordenada(informacionLeida, unCamino);
    }
    else if ( (informacionLeida[0]=='L') || (informacionLeida[0]=='T') ){
        cargarCoordenadasPorMarcar();
    }
    else if (informacionLeida[0]=='B'){
        cargarPuntoDeInteres(informacionLeida);
    /* Las bifurcaciones tambien deben marcarse en el Mapa, por lo que agrego la coordenada */
        cargarCoordenadasPorMarcar();
    }
    else if (informacionLeida[0]=='U'){
        cargarPuntoDeInteres(informacionLeida);
    }
    else if ((informacionLeida[0]=='P') && (informacionLeida[1]=='L')){
        cargarPuntoDeInteres(informacionLeida);
        /* Calculo Maximos y Minimos y del camino actual */
        calcularMaximosyMinimos();
        unCamino->cargarListaDePasos(listaDePasos);
        unCamino->cargarCoordenadasPorMarcar(coordenadasPorMarcar);
        unCamino->cargarPuntosDeInteres(puntosDeInteres);
        unCamino->cargarUniones(uniones);
        unCamino->cargarMaxMin(MaximoX, MinimoX, MaximoY, MinimoY);
    }
}

void GPS::cargarColor(string rgb, Camino* unCamino){
    unCamino->cargarColor(rgb);
}

void GPS::cargarCoordenadasPorMarcar(){
    coordenadasPorMarcar->agregar(obtenerPosicionActual());
}

void GPS::cargarPuntoDeInteres(string punto){
    numeroID++;
    string nombre;

    if (punto[0]=='B'){
        for(unsigned int i=3; i<punto.length(); i++){
            nombre+=punto[i];
        }
        PuntoDeInteres* unPuntoDeInteres = new PuntoDeInteres;
        unPuntoDeInteres->cargarPuntoDeInteres(nombre, obtenerPosicionActual());
        puntosDeInteres->agregar(unPuntoDeInteres);
    }
    else if (punto[0]=='U'){
        for(unsigned int i=2; i<punto.length(); i++){
            nombre+=punto[i];
        }
        PuntoDeInteres* unPuntoDeInteres = new PuntoDeInteres;
        unPuntoDeInteres->cargarID(INF);
        unPuntoDeInteres->cargarPuntoDeInteres(nombre, obtenerPosicionActual());

        /*
        * Las uniones tambien las guardo como punto de interes, las necesito para
        * poder comparar el numero de ID de los caminos y asi utilizar esta info para
        * encontrar caminos minimos
        */
        puntosDeInteres->agregar(unPuntoDeInteres);
        uniones->agregar(unPuntoDeInteres);
    }
    else if ((punto[0]=='P') && (punto[1]=='P')){
        unsigned int i=3;
        while (punto[i]!=' '){
            nombre+=punto[i];
            i++;
        }
        PuntoDeInteres* unPuntoDeInteres = new PuntoDeInteres;
        unPuntoDeInteres->cargarPuntoDeInteres(nombre, obtenerPosicionActual());
        unPuntoDeInteres->cargarID(numeroID);
        puntosDeInteres->agregar(unPuntoDeInteres);
    }
    else if ((punto[0]=='P') && (punto[1]=='L')){
        for(unsigned int i=4; i<punto.length(); i++){
            nombre+=punto[i];
        }
        PuntoDeInteres* unPuntoDeInteres = new PuntoDeInteres;
        unPuntoDeInteres->cargarPuntoDeInteres(nombre, obtenerPosicionActual());
        puntosDeInteres->agregar(unPuntoDeInteres);
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

void GPS::vaciarListaDeCoordenadas(){
    while (listaDeCoordenadas->contarElementos()!=0){
        int i=1;
        listaDeCoordenadas->iniciarCursor();
        while (listaDeCoordenadas->avanzarCursor()){
            listaDeCoordenadas->remover(i);
            i++;
        }
    }
    delete listaDeCoordenadas;

    listaDeCoordenadas = new Lista<pair<int, int> >;
}

void GPS::calcularMaximosyMinimos(){
    MaximoX=new int;
    MinimoX=new int;
    MaximoY=new int;
    MinimoY=new int;

    *MaximoX=0;
    *MaximoY=0;
    *MinimoX=0;
    *MinimoY=0;

    listaDeCoordenadas->iniciarCursor();
    while (listaDeCoordenadas->avanzarCursor()){
        if (listaDeCoordenadas->obtenerCursor().first>*(MaximoX)){
            *MaximoX=listaDeCoordenadas->obtenerCursor().first;
        }
        else if (listaDeCoordenadas->obtenerCursor().first<*(MinimoX)){
            *MinimoX=listaDeCoordenadas->obtenerCursor().first;
        }
        else if (listaDeCoordenadas->obtenerCursor().second>*(MaximoY)){
            *MaximoY=listaDeCoordenadas->obtenerCursor().second;
        }
        else if (listaDeCoordenadas->obtenerCursor().first<*(MinimoY)){
            *MinimoX=listaDeCoordenadas->obtenerCursor().second;
        }
    }
    vaciarListaDeCoordenadas();
}

void GPS::cargarCoordenada(string informacionLeida, Camino* unCamino){
    pair<int, int> posicionActual;
    string pasosAuxiliar="";
    int pasos=0;
    for (unsigned int i=2; i<informacionLeida.length(); i++){
        pasosAuxiliar+=informacionLeida[i];
    }
    istringstream convert(pasosAuxiliar);
    convert>>pasos;

    /* Guardo los pasos segun su direccion y sentido */
    if (informacionLeida[0]=='A'){
        pasos=pasos*sentidoEjeActual;
    }
    else if (informacionLeida[0]=='R'){
        pasos=pasos*sentidoEjeActual*(-1);
    }

    posicionActual=obtenerPosicionActual();


    if ((direccionEnEje=='N') || (direccionEnEje=='S')){
        listaDeCoordenadas->agregar(make_pair(posicionActual.first,posicionActual.second+pasos));
        listaDePasos->agregar(make_pair(0,pasos));
    }
    else if ((direccionEnEje=='O') || (direccionEnEje=='E')){
        listaDeCoordenadas->agregar(make_pair(posicionActual.first+pasos,posicionActual.second));
        listaDePasos->agregar(make_pair(pasos,0));
    }
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

GPS::~GPS(){
    while (listaDeCoordenadas->contarElementos()!=0){
        int i=1;
        listaDeCoordenadas->iniciarCursor();
        while (listaDeCoordenadas->avanzarCursor()){
            listaDeCoordenadas->remover(i);
            i++;
        }
    }
    delete listaDeCoordenadas;
}
