#include "CargadorDeAtajos.h"

using namespace std;

/* Declaro constante el color del atajo (Amarillo) */
const string color="-- ATAJO 255 255 0";

CargadorDeAtajos::CargadorDeAtajos(Camino* caminoMasCorto){
    this->pasos= caminoMasCorto->obtenerListaDePasos();
    this->cantidadDeCaminos=1;
}

void CargadorDeAtajos::cargarAtajo(Lista<int>* recorridoMinimo, Lista<Camino* >* caminos, Camino* caminoMasCorto){
    /*
    * Siempre que se elija un punto, se debera pasar por otro punto perteneciente al mismo camino,
    * por ende, busco a que camino pertenece un par de PuntosDeInteres y de esta manera obtengo
    * la "porcion" de pasos del atajo referidas a ese camino.
    */
    unsigned int i=1;

    while (i<recorridoMinimo->contarElementos()){
        int IDPartida=recorridoMinimo->obtener(i);
        int IDLlegada=recorridoMinimo->obtener(i+1);

        /*
        * Siempre va a entrar al menos la cantidad de elementos que contenga la lista
        * de recorridos minimos -1.
        * Esto me sirve para saber cuando agregar el ultimo paso del caminante al atajo.
         */
        int totalCaminos=recorridoMinimo->contarElementos()-1;
        buscarCamino(IDPartida, IDLlegada, caminos, totalCaminos, caminoMasCorto);
        i++;
    }
    caminoMasCorto->cargarListaDePasos(pasos);
    caminoMasCorto->cargarColor(color);
}

/** PRIVATE **/

void CargadorDeAtajos::buscarCamino(int IDPartida, int IDLlegada, Lista<Camino* >* caminos, int totalCaminos, Camino* caminoMasCorto){
    bool encontrePartida=false;
    bool encontreLlegada=false;
    bool encontrado=false;
    Camino* camino;
    for (unsigned int i=1; (i<=caminos->contarElementos()) && (!encontrado); i++){
        Camino* unCamino = caminos->obtener(i);
        unCamino->obtenerPuntosDeInteres()->iniciarCursor();
        while (unCamino->obtenerPuntosDeInteres()->avanzarCursor() && (!encontrado)){
            PuntoDeInteres* unPuntoDeInteres = unCamino->obtenerPuntosDeInteres()->obtenerCursor();
            if (unPuntoDeInteres->obtenerID()==IDPartida){
                encontrePartida=true;
            }
            if (unPuntoDeInteres->obtenerID()==IDLlegada){
                encontreLlegada=true;
            }
            if ((encontrePartida) && (encontreLlegada)){
                encontrado=true;
                camino=caminos->obtener(i);
            }
        }
    }
    cargarPorcionDeCamino(IDPartida, IDLlegada, camino, totalCaminos, caminoMasCorto);
}

int CargadorDeAtajos::buscarPosicion(Camino* camino, pair<int, int> posicion){
    pair<int, int> pasoActual = make_pair(0,0);
    int posicionActual=1;
    int posicionEncontrada=1;
    bool encontrado=false;
    if ((posicion.first==0) && (posicion.second==0)){
        posicionEncontrada=0;
    }
    else{
        Lista<pair<int, int> >* listaDePasos = camino->obtenerListaDePasos();
        listaDePasos->iniciarCursor();
        while ( (listaDePasos->avanzarCursor()) && (!encontrado) ){
            pasoActual.first += listaDePasos->obtenerCursor().first;
            pasoActual.second += listaDePasos->obtenerCursor().second;
            if (pasoActual==posicion){
                encontrado=true;
                posicionEncontrada=posicionActual;
            }
            posicionActual++;
        }
    }
    return posicionEncontrada;
}

void CargadorDeAtajos::cargarPorcionDeCamino(int IDPartida, int IDLlegada, Camino* unCamino, int totalCaminos, Camino* caminoMasCorto){
    /*
    * Obtiene la porcion de camino que nos interesa, cargandolo en una nueva lista
    * de caminos, la cual se enviara al GraficadorDeMapa
    */
    int lugarPartida;
    int lugarLlegada;
    pair<int, int> posicionPartida=make_pair(0,0);
    pair<int, int> posicionLlegada=make_pair(0,0);
    Lista<PuntoDeInteres*>* puntosDeInteres = unCamino->obtenerPuntosDeInteres();
    for(unsigned int i=1; i<=puntosDeInteres->contarElementos();i++){
        if (puntosDeInteres->obtener(i)->obtenerID()==IDPartida){
            posicionPartida=puntosDeInteres->obtener(i)->obtenerPosicion();
        }
        if (puntosDeInteres->obtener(i)->obtenerID()==IDLlegada){
            posicionLlegada=puntosDeInteres->obtener(i)->obtenerPosicion();
        }
    }
    lugarPartida=buscarPosicion(unCamino, posicionPartida);
    lugarLlegada=buscarPosicion(unCamino, posicionLlegada);

    /*
    * Los caminos sufren modificaciones en sus origenes antes de enviar la informacion al Mapa,
    * por ende, debo corregir este error en el origen del atajo.
    */
    if (cantidadDeCaminos==1){
        pair<int, int> origenCoordenado = make_pair(0,0);
        if (caminoMasCorto->obtenerOrigen()==origenCoordenado){
            int nuevoOrigenX= posicionPartida.first+(unCamino->obtenerOrigen().first);
            int nuevoOrigenY= posicionPartida.second+(unCamino->obtenerOrigen().second);

            caminoMasCorto->cargarOrigen(make_pair(nuevoOrigenX, nuevoOrigenY));
        }
    }

        if (lugarPartida>lugarLlegada){
            /* Si en la lista el lugar de partida es mas avanzado que el lugar de llegada
            se deben invertir los pasos del caminante para que formen el camino al reves */

            for(int i=lugarPartida; i>lugarLlegada; i--){
                pair<int, int> pasoPorGuardar=unCamino->obtenerListaDePasos()->obtener(i);
                int first_invertido = pasoPorGuardar.first*(-1);
                int second_invertido = pasoPorGuardar.second*(-1);
                pasos->agregar(make_pair(first_invertido, second_invertido));
            }
            cantidadDeCaminos++;
        }
        else{
            /* El "-1" hace que entre caminos no pise la ultima instruccion */
            for(int i=lugarPartida+1; i<=lugarLlegada; i++){
                pair<int, int> pasoPorGuardar=unCamino->obtenerListaDePasos()->obtener(i);
                pasos->agregar(pasoPorGuardar);
            }
            cantidadDeCaminos++;
        }

}

CargadorDeAtajos::~CargadorDeAtajos(){
}
