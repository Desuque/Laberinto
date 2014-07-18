#include "PuntoDeInteres.h"

using namespace std;

PuntoDeInteres::PuntoDeInteres(){
    this->nombre="";
    this->posicion=make_pair(0,0);
    this->ID=0;
    /* Esta variable guarda con que camino se une */
    this->numeroCamino=0;
    /* Cantidad de pasos entre camino actual y el que se une */
    this->peso=0;
}

void PuntoDeInteres::cargarPuntoDeInteres(string nombre, pair<int, int> posicion){
    this->nombre=nombre;
    this->posicion=posicion;
}

string PuntoDeInteres::obtenerNombre(){
    return this->nombre;
}

pair<int, int> PuntoDeInteres::obtenerPosicion(){
    return this->posicion;
}

void PuntoDeInteres::cargarID(int IDActual){
    this->ID=IDActual;
}

void PuntoDeInteres::cargarSeUneCon(int numeroCamino){
    this->numeroCamino=numeroCamino;
}

void PuntoDeInteres::cargarPeso(int peso){
    this->peso=peso;
}

int PuntoDeInteres::obtenerPeso(){
    return peso;
}

int PuntoDeInteres::obtenerUnion(){
    return numeroCamino;
}

int PuntoDeInteres::obtenerID(){
    return this->ID;
}

PuntoDeInteres::~PuntoDeInteres(){
}
