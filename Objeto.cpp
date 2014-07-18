#include "Objeto.h"

using namespace std;

Objeto::Objeto()
{
    this->cantidad=0;
    this->nombre="";
}

Objeto::Objeto(string nombreObjeto)
{
    this->cantidad=1;
    this->nombre=nombreObjeto;
}

Objeto::Objeto(string nombreObjeto, unsigned int cantidad)
{
    this->cantidad=cantidad;
    this->nombre=nombreObjeto;
}

string Objeto::obtenerNombre(){
    return this->nombre;
}

int Objeto::obtenerCantidad(){
    return this->cantidad;
}

Objeto::~Objeto()
{
}
