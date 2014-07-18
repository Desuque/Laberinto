#ifndef OBJETO_H_INCLUDED
#define OBJETO_H_INCLUDED

#include <string>

class Objeto
{
private:
    int cantidad;
    std::string nombre;
public:
    /*
    * Pre:
    * Post: Crea un nuevo objeto vacio
    */
    Objeto();

    /*
    * Pre:
    * Post: Crea un nuevo objeto con su respectivo nombre y cantidad 1
    */
    Objeto(std::string nombreObjeto);

    /*
    * Pre:
    * Post: Crea un nuevo objeto con su respectivo nombre y cantidad arbitraria
    */
    Objeto(std::string nombreObjeto, unsigned int cantidad);

    /*
    * Pre: El objeto debe existir
    * Post: Devuelve el nombre asociado al objeto
    */
    std::string obtenerNombre();

    /*
    * Pre: El objeto debe existir
    * Post: Devuelve la cantidad asociada al objeto
    */
    int obtenerCantidad();

    /*
    * Pre:
    * Post: Libera los recursos asociados al Objeto
    */
    ~Objeto();

};

#endif // OBJETO_H_INCLUDED

