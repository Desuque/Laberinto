#ifndef MOCHILAV0_H_INCLUDED
#define MOCHILAV0_H_INCLUDED

#include <string>
#include "Objeto.h"
#include "Lista.h"

using namespace std;

class Mochila
{
private:
	Lista<Objeto>* objetosGuardados;

public:
	Mochila();
	~Mochila();
	void enviar(string informacionLeida);
	void agregarObjeto(string nombreObjeto);
    int obtenerCantidadDeObjeto(string nombreObjeto);
    Lista<Objeto>* obtenerObjetos();

private:
	string obtenerNombreObjeto(string informacionLeida);
    bool objetoEstaEnMochila(string nombreObjeto);
    void eliminarObjeto(string nombreObjeto);
};

#endif // MOCHILAV0_H_INCLUDED
