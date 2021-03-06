#include "Camino.h"

using namespace std;

const int R=0;
const int G=1;
const int B=2;

Camino::Camino(){
    this->color[R]=0;
    this->color[G]=0;
    this->color[B]=0;
    this->origen=make_pair(0,0);
    this->MaximoX=0;
    this->MaximoY=0;
    this->MinimoX=0;
    this->MinimoY=0;

    this->listaDePasos = new Lista<pair<int, int> >;
    this->coordenadasPorMarcar = new Lista<pair<int, int> >;
    this->puntosDeInteres = new Lista<PuntoDeInteres* >;
    this->uniones = new Lista<PuntoDeInteres* >;
}

void Camino::cargarColor(string rgb){
    int codigoDeColor=0;
    int j=0;
    string rgbAuxiliar;

    unsigned int k=3;
    while (rgb[k]!=' '){
        k++;
    }
    for(unsigned int i=k+1; i<rgb.length(); i++){
        if((rgb[i])!=' '){
            rgbAuxiliar=rgbAuxiliar+rgb[i];
        }
        else{
            istringstream convert(rgbAuxiliar);
            convert>>codigoDeColor;
            color[j]=codigoDeColor;
            rgbAuxiliar="";
            j++;
        }
    }
    istringstream convert(rgbAuxiliar);
    convert>>codigoDeColor;
    color[j]=codigoDeColor;
}

void Camino::cargarOrigen(pair<int, int> origen){
    this->origen=origen;
}

void Camino::cargarListaDePasos(Lista<pair<int, int > >* listaDePasos){
    this->listaDePasos=listaDePasos;
}

void Camino::cargarCoordenadasPorMarcar(Lista<pair<int, int> >* coordenadasPorMarcar){
    this->coordenadasPorMarcar=coordenadasPorMarcar;
}

void Camino::cargarPuntosDeInteres(Lista<PuntoDeInteres* >* puntosDeInteres){
    this->puntosDeInteres=puntosDeInteres;
}

void Camino::cargarUniones(Lista<PuntoDeInteres* >* uniones){
    this->uniones=uniones;
}

void Camino::cargarMaxMin(int* MaximoX, int* MinimoX, int* MaximoY, int* MinimoY){
    this->MaximoX=MaximoX;
    this->MinimoX=MinimoX;
    this->MaximoY=MaximoY;
    this->MinimoY=MinimoY;
}

pair<int, int> Camino::obtenerOrigen(){
    return this->origen;
}

Lista<PuntoDeInteres* >* Camino::obtenerPuntosDeInteres(){
    return this->puntosDeInteres;
}

Lista<pair<int, int> >* Camino::obtenerCoordenadasPorMarcar(){
    return this->coordenadasPorMarcar;
}

Lista<PuntoDeInteres* >* Camino::obtenerUniones(){
    return this->uniones;
}

int* Camino::obtenerColor(){
    return this->color;
}

Lista<pair<int, int> >* Camino::obtenerListaDePasos(){
    return this->listaDePasos;
}

int* Camino::obtenerMaximoX(){
    return this->MaximoX;
}

int* Camino::obtenerMinimoX(){
    return this->MinimoX;
}

int* Camino::obtenerMaximoY(){
    return this->MaximoY;
}

int* Camino::obtenerMinimoY(){
    return this->MinimoY;
}

Camino::~Camino(){
    delete MaximoX;
    delete MaximoY;
    delete MinimoX;
    delete MinimoY;

    while (listaDePasos->contarElementos()!=0){
        int i=1;
        listaDePasos->iniciarCursor();
        while (listaDePasos->avanzarCursor()){
            listaDePasos->remover(i);
            i++;
        }
    }
    delete listaDePasos;

    puntosDeInteres->iniciarCursor();
    while (puntosDeInteres->avanzarCursor()){
        delete puntosDeInteres->obtenerCursor();
    }
    delete puntosDeInteres;

    /* La lista de uniones contiene puntosDeInteres que se cargaron al mismo momento
    * (y apuntando al mismo puntero) que la lista de puntosDeInteres. Por lo tanto,
    * solo se debe borrar "uniones" caso contrario se intentara borrar memoria liberada. */
    delete uniones;
    delete coordenadasPorMarcar;
}
