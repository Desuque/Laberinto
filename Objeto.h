#ifndef OBJETO_H_INCLUDED
#define OBJETO_H_INCLUDED

#include <string>

using namespace std;

class Objeto
{
private:
        int cantidad;
        string nombre;
public:
        Objeto();
        ~Objeto();
        Objeto(string nombreObjeto);
        Objeto(string nombreObjeto, unsigned int cantidad);
        string obtenerNombre();
        int obtenerCantidad();

        void aumentarCantidad();
        void reducirCantidad();

};

#endif // OBJETO_H_INCLUDED

