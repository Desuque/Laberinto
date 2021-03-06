#include "Caminante.h"
#include "CargadorDeAtajos.h"
#include "Dijkstra.h"

using namespace std;

/* Distancia entre caminos a la hora de dibujarlos */
const int distanciaAncho=30;
const int distanciaAlto=40;

Caminante::Caminante(){
    this->unaMochila = new Mochila;
    this->unMapa = new GraficadorDeMapa;
    this->caminos = new Lista<Camino*>;
    this->unGPS = new GPS;
}

void Caminante::logisticaDelRecorrido(Lista<Lista<string>*>* recorridos){
    Lista<string>* recorridoActual;
    recorridos->iniciarCursor();
    while (recorridos->avanzarCursor()){
        unCamino = new Camino;
        recorridoActual = recorridos->obtenerCursor();
        obtenerInformacionDel(recorridoActual, unCamino);
        caminos->agregar(unCamino);
    }

    /* Se encarga de asociar que puntoDeInteres se une con el anterior puntoDeInteres (TP2) */
    unirPuntosDeInteres();
}

Lista<Objeto* >* Caminante::obtenerObjetosDeLaMochila(){
    return unaMochila->obtenerObjetos();
}

void Caminante::enviarInformacionAlMapa(){
    acomodarOrigen();
    caminos->iniciarCursor();
    while (caminos->avanzarCursor()){
        Camino* caminoActual = caminos->obtenerCursor();
        unMapa->cargarColor(caminoActual->obtenerColor());
        unMapa->cargarOrigen(caminoActual->obtenerOrigen());
        unMapa->cargarRecorrido(caminoActual->obtenerListaDePasos());
        unMapa->marcarObjetos(caminoActual->obtenerCoordenadasPorMarcar());
    }
}

void Caminante::buscarAtajo(){
    /* Calcula el minimo camino utilizando el algoritmo de Dijkstra */
    Lista<int>* recorridoMinimo = new Lista<int>;
    Dijkstra* buscarMinimo = new Dijkstra(caminos, recorridoMinimo);
    buscarMinimo->inicializarValores();

    /* Envia los IDs de los caminos minimos al CargadorDeAtajos */
    Camino* caminoMasCorto = new Camino;
    CargadorDeAtajos* unAtajo = new CargadorDeAtajos(caminoMasCorto);
    unAtajo->cargarAtajo(recorridoMinimo, caminos, caminoMasCorto);

    /* Envio el atajo al graficadorDeMapa */
    unMapa->cargarColor(caminoMasCorto->obtenerColor());
    unMapa->cargarOrigen(caminoMasCorto->obtenerOrigen());
    unMapa->cargarRecorrido(caminoMasCorto->obtenerListaDePasos());

    delete recorridoMinimo;
    delete buscarMinimo;

    delete caminoMasCorto;
    delete unAtajo;
}

void Caminante::dibujarBMP(){
    unMapa->dibujarRecorridos();
}

bool Caminante::mochilaVacia(){
    return unaMochila->estaVacia();
}

/** PRIVATE **/

void Caminante::obtenerInformacionDel(Lista<string>* recorridoActual, Camino* unCamino){
    string informacionLeida;;
    recorridoActual->iniciarCursor();
    while (recorridoActual->avanzarCursor()){
        informacionLeida = recorridoActual->obtenerCursor();
        /* Se envian los objetos se�alados en el recorrido a la Mochila */
        enviarObjetosDelCaminoALaMochila(informacionLeida);

        /* Se envia la informacion del caminante al GPS */
        enviarAccionesAlGPS(informacionLeida, unCamino);

    }
}

void Caminante::enviarObjetosDelCaminoALaMochila(string informacionLeida){
    if ((informacionLeida[0]=='L') || (informacionLeida[0]=='T')){
        unaMochila->enviar(informacionLeida);
    }
}

void Caminante::enviarAccionesAlGPS(string informacionLeida, Camino* unCamino){
    /*
    * La informacion no se filtra ya que el GPS necesita conocer, ademas de los pasos y bifurcaciones
    * los lugares donde se ha levantado o dejado un Objeto
    * Se pasa un puntero al camino para que se modifique la informacion desde el GPS.
    */
    unGPS->discriminarInformacion(informacionLeida, unCamino);
}

void Caminante::acomodarOrigen(){
    int anchoCaminos=0;
    int altoCaminos=0;

    for(unsigned int i=1; i<=caminos->contarElementos(); i++){
        Camino* unCamino = caminos->obtener(i);

        if (unCamino->obtenerUniones()->contarElementos()==0){
            anchoCaminos = (*(unCamino->obtenerMaximoX())+abs(*(unCamino->obtenerMinimoX())))+ distanciaAncho;
            altoCaminos = distanciaAlto;
            pair<int, int> nuevoOrigen=make_pair(anchoCaminos, altoCaminos);
            (caminos->obtener(i))->cargarOrigen(nuevoOrigen);
        }
        else{
            /*
            * Busca la coordenada de la bifurcacion previamente cargada, para mover el origen
            * del recorrido que tiene la union, con acomodar una sola union, el camino queda
            * perfectamente ubicado (ya que el resto de los caminos estaran validados)
            */
            PuntoDeInteres* unaUnion=unCamino->obtenerUniones()->obtener(1);

            pair<int, int> coordenadaDeUnion=obtenerCoordenadaDeUnion(unaUnion->obtenerNombre(), i);

            /*
            * Obtengo la posicion de la union respecto a su camino asociado. Esta posicion debe ser
            * igual a "coordenadaDeUnion" por lo que muevo el origen de este camino para que esto suceda.
            */
            pair<int, int> posicionDeUnion=unaUnion->obtenerPosicion();
            pair<int, int> nuevoOrigen = calcularNuevoOrigen(coordenadaDeUnion, posicionDeUnion);

            unCamino->cargarOrigen(nuevoOrigen);
        }
    }
    unMapa->cargarTamanioBMP(150, 150);
}

pair<int, int> Caminante::obtenerCoordenadaDeUnion(string nombreUnion, int numeroCamino){
    pair<int, int> coordenadaDeUnion;
    bool encontrado=false;
    int i=1;

    /* Busco en todos los caminos anteriores al camino actual donde se encontro una Union */

    /* Nota: La coordenada encontrada sirve unicamente si se le suma el origen de el camino al cual se
    asocia la bifurcacion, ya que esta puede haber sido modificada en un recorrido anterior */

    while ((i<=numeroCamino) && (!encontrado)){
        Camino* unCamino=caminos->obtener(i);
        unsigned int j=1;
        while (j<=unCamino->obtenerPuntosDeInteres()->contarElementos() && (!encontrado)){
            if ((unCamino->obtenerPuntosDeInteres()->obtener(j))->obtenerNombre()==nombreUnion){
                pair<int, int> coordenadaEncontrada=(unCamino->obtenerPuntosDeInteres()->obtener(j))->obtenerPosicion();
                pair<int, int> origenCamino=unCamino->obtenerOrigen();

                int nuevoX=coordenadaEncontrada.first+origenCamino.first;
                int nuevoY=coordenadaEncontrada.second+origenCamino.second;

                coordenadaDeUnion=make_pair(nuevoX, nuevoY);
                encontrado=true;
            }
            j++;
        }
        i++;
    }
    return coordenadaDeUnion;
}

pair<int, int> Caminante::calcularNuevoOrigen(pair<int, int> coordenadaDeUnion, pair<int, int> posicionDeUnion){
    int x=0;
    int y=0;

    if (posicionDeUnion.first<coordenadaDeUnion.first){
        x=coordenadaDeUnion.first-posicionDeUnion.first;
    }
    if (posicionDeUnion.first>coordenadaDeUnion.first){
        x=posicionDeUnion.first-coordenadaDeUnion.first;
    }

    if (posicionDeUnion.second<coordenadaDeUnion.second){
        y=coordenadaDeUnion.second-posicionDeUnion.second;
    }
    if (posicionDeUnion.second>coordenadaDeUnion.second){
        y=posicionDeUnion.second-coordenadaDeUnion.second;
    }

    return make_pair(x,y);
}

void Caminante::unirPuntosDeInteres(){
    int k=1;
    for(unsigned int i=1; i<=caminos->contarElementos();i++){
        unCamino=caminos->obtener(i);
        Lista<PuntoDeInteres*>* puntos = unCamino->obtenerPuntosDeInteres();
        for(unsigned int j=1; j<=puntos->contarElementos(); j++){
            if ((puntos->obtener(j)->obtenerID()!=INF) && (puntos->obtener(j)->obtenerID()!=0)){
                /*
                * Si el camino ya trae precargado que su ID es igual a j
                * quiere decir que es un punto de partida (PP), por ende
                * se une con el siguiente punto
                */
                (puntos->obtener(j))->cargarID(k);
                if(buscarUnion(puntos->obtener(j+1)->obtenerNombre(),i,j)!=-1){
                    /*Busco si hay uno igual antes en la lista. si hay el seUneCon es el id del j+1*/
                    puntos->obtener(j)->cargarSeUneCon(buscarUnion(puntos->obtener(j+1)->obtenerNombre(),i,j));
                }
                else{
                    puntos->obtener(j)->cargarSeUneCon(k+1);
                    k++;
                }

            }
            else if (puntos->obtener(j)->obtenerID()!=k){
                if (puntos->obtener(j)->obtenerID()!=INF){
                    if(buscarUnion(puntos->obtener(j-1)->obtenerNombre(),i,j-1)!=-1){
                        puntos->obtener(j)->cargarID(k);
                        puntos->obtener(j)->cargarSeUneCon(buscarUnion(puntos->obtener(j-1)->obtenerNombre(),i,j-1));
                        k++;
                    }
                    else
                    {
                        puntos->obtener(j)->cargarID(k);
                        puntos->obtener(j)->cargarSeUneCon(k-1);
                        k++;
                    }
                }
                else{
                    /*Si el ID es igual a INF quiere decir que el punto que se busco
                    *era una union, por ende, se unira con el ID correspondiente a ese nombre */
                    puntos->obtener(j)->cargarID(obtenerUnion(puntos->obtener(j)->obtenerNombre()));
                    if(buscarUnion(puntos->obtener(j-1)->obtenerNombre(),i,j-1)!=-1){
                        puntos->obtener(j)->cargarSeUneCon(buscarUnion(puntos->obtener(j-1)->obtenerNombre(),i,j-1));
                    }
                    else{
                        puntos->obtener(j)->cargarSeUneCon(k);
                        k++;
                    }
                }
            }
        }
    }
    calcularPeso();
}

void Caminante::calcularPeso(){
    for(unsigned int i=1; i<=caminos->contarElementos();i++){
        unCamino=caminos->obtener(i);
        for(unsigned int j=1; j<=unCamino->obtenerPuntosDeInteres()->contarElementos(); j++){
            PuntoDeInteres* unPuntoDeInteres=unCamino->obtenerPuntosDeInteres()->obtener(j);

            if (unPuntoDeInteres->obtenerID()==unPuntoDeInteres->obtenerUnion()){
                /* Si el camino no tiene uniones, entonces su peso es nulo */
                unPuntoDeInteres->cargarPeso(0);
            }
            else{
                /*
                * Si el camino tiene uniones, entonces se resta la posicion de cada punto
                * y se suman ambos ejes en modulo, dando como resultado la cantidad de pasos
                */
                pair<int, int> posicionFinal=unPuntoDeInteres->obtenerPosicion();
                pair<int, int> posicionInicial=unCamino->obtenerPuntosDeInteres()->obtener(j-1)->obtenerPosicion();

                int totalX=abs(posicionFinal.first-posicionInicial.first);
                int totalY=abs(posicionFinal.second-posicionInicial.second);

                unPuntoDeInteres->cargarPeso(totalX+totalY);
            }
        }
    }
}

int Caminante::obtenerUnion(string nombre){
    bool encontrado=false;
    int ID;
    for(unsigned int i=1; ((i<=caminos->contarElementos()) && (!encontrado)); i++){
        unCamino=caminos->obtener(i);
        Lista<PuntoDeInteres*>* puntos = unCamino->obtenerPuntosDeInteres();
        for(unsigned int j=1; ((j<=puntos->contarElementos()) && (!encontrado)); j++){
            if (puntos->obtener(j)->obtenerNombre()==nombre){
                ID=puntos->obtener(j)->obtenerID();
                encontrado=true;
            }
        }
        if (encontrado==false){
            ID=INF;
        }
    }
    return ID;
}

int Caminante::buscarUnion(string nombre, int caminoFin, int puntoFin)
{
    int idUnionEncontrada = -1;
    for(int i=1; i<=caminoFin;i++){
        unCamino=caminos->obtener(i);
        Lista<PuntoDeInteres*>* puntos = unCamino->obtenerPuntosDeInteres();
        if(i==caminoFin){
            for(int j=1; j<puntoFin; j++){
                if(puntos->obtener(j)->obtenerNombre() == nombre)
                    idUnionEncontrada = puntos->obtener(j)->obtenerID();
            }
        }else{
            for(unsigned int j=1; j<=puntos->contarElementos(); j++){
                    if(puntos->obtener(j)->obtenerNombre() == nombre)
                        idUnionEncontrada = puntos->obtener(j)->obtenerID();
                }
        }
    }
    return idUnionEncontrada;
}

Caminante::~Caminante(){
    caminos->iniciarCursor();
    while (caminos->avanzarCursor()){
        delete caminos->obtenerCursor();
    }

    delete caminos;
    delete unaMochila;
    delete unMapa;
    delete unGPS;
}
