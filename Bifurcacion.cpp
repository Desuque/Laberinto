#include <iostream>
#include <string>
#include "Bifurcacion.h"

Bifurcacion::Bifurcacion(){
    this->nombre="";
    this->sentido=' ';
    this->posicion=make_pair(0,0);
}

void Bifurcacion::cargarBifurcacion(string nombre, char sentido, pair<int, int> posicion){
    this->nombre=nombre;
    this->sentido=sentido;
    this->posicion=posicion;
}

string Bifurcacion::obtenerNombre(){
    return this->nombre;
}

Bifurcacion::~Bifurcacion(){
}
