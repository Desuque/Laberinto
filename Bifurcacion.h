#ifndef BIFURCACION_H_INCLUDED
#define BIFURCACION_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class Bifurcacion{
private:
    string nombre;
    char sentido;
    pair<int, int> posicion;
public:
    Bifurcacion();
    void cargarBifurcacion(string nombre, char sentido, pair<int, int> posicion);
    string obtenerNombre();
    ~Bifurcacion();
};

#endif // BIFURCACION_H_INCLUDED
