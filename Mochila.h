#ifndef MOCHILAV0_H_INCLUDED
#define MOCHILAV0_H_INCLUDED

#include "Objeto.h"
#include "Lista.h"

class Mochila
{
private:
	Lista<Objeto* >* objetosGuardados;

public:
    /*
    * Pre:
    * Post: Crea una nueva Mochila sin objetos en su interior
    */
	Mochila();

    /*
    * Pre: La mochila debe existir
    * Post: Se procesa si el nuevo objeto se alzo o se tiro. En el primer caso se crea un objeto nuevo,
    *       o en caso de existir, se le suma una unidad. En caso de tirarlo, se resta una unidad al objeto.
    */
	void enviar(std::string informacionLeida);

    /*
    * Pre: Debe existir una Mochila
    * Post: Devuelve los objetos guardados en la Mochila
    */
    Lista<Objeto* >* obtenerObjetos();

    /*
    * Pre: La mochila debe existir
    * Post: Informa si la mochila esta o no vacia
    */
    bool estaVacia();

    /*
    * Pre:
    * Post: Libera los recursos asociados a la Mochila
    */
    ~Mochila();

private:
    /*
    * Pre: La mochila debe existir
    * Post: Se busca en los objetos guarados si existe el nuevo objeto o no
    */
    bool objetoEstaEnMochila(std::string nombreObjeto);

    /*
    * Pre: La mochila debe existir
    * Post: Devuelve la cantidad actual del objeto ingresado
    */
    int obtenerCantidadDeObjeto(std::string nombreObjeto);

    /*
    * Pre: La informacion leida debe ser ingresada como L<nombre> o T<nombre>
    * Post: Devuelve el nombre asociado al objeto
    */
	std::string obtenerNombreObjeto(std::string informacionLeida);

    /*
    * Pre: El objeto no debe existir en la Mochila
    * Post: Se agrega el nuevo objeto a la Mochila con 1 unidad
    */
	void agregarObjeto(std::string nombreObjeto);

    /*
    * Pre: El objeto debe existir
    * Post: Elimina el objeto
    */
    void eliminarObjeto(std::string nombreObjeto);
};

#endif // MOCHILAV0_H_INCLUDED
