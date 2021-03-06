#include "TP.h"
#include "CargadorDeRecorridos.h"

using namespace std;

TP::TP(){
    this->unCaminante = new Caminante;
}

void TP::iniciar(){
    Lista<Lista<string>*>* recorridos = new Lista<Lista<string>*>;
    string archivoDeCaminos;

    cout<<"El laberinto maldito:"<<endl;
    cout<<"====================="<<endl;
    cout<<endl;

    cout<<"Ingrese el nombre del archivo de caminos (Ej: Caminos.txt): ";
    cin>>archivoDeCaminos;
    cout<<endl;

    cargarRecorridos(archivoDeCaminos, recorridos);

    /* Libero la memoria asociada a la lista de recorridos */
    recorridos->iniciarCursor();
    while (recorridos->avanzarCursor()){
        Lista<string>* unRecorrido = recorridos->obtenerCursor();
        int i=1;
        unRecorrido->iniciarCursor();
        while (unRecorrido->avanzarCursor()){
            unRecorrido->remover(i);
            i++;
        }
        delete unRecorrido;
    }
    delete recorridos;

    obtenerMochila();
    enviarInformacionAlGraficador();
    buscarAtajo();
    dibujarBMP();
}

void TP::cargarRecorridos(string archivoDeCaminos, Lista<Lista<string>*>* recorridos){
    /* Cargo los recorridos en memoria */
    CargadorDeRecorridos* registroDeRecorridos = new CargadorDeRecorridos();
    registroDeRecorridos->cargarRecorridos(archivoDeCaminos, recorridos);

    /* Envio los recorridos al Caminante */
    unCaminante->logisticaDelRecorrido(recorridos);

    delete registroDeRecorridos;
}

void TP::obtenerMochila(){
    cout<<"Objetos guardados en la mochila:"<<endl;
    cout<<"--------------------------------"<<endl<<endl;

    if (unCaminante->mochilaVacia()){
        cout<<"La mochila esta vacia."<<endl<<endl;
    }
    else{
        (unCaminante->obtenerObjetosDeLaMochila())->iniciarCursor();
        while (unCaminante->obtenerObjetosDeLaMochila()->avanzarCursor()){
            Objeto* unObjeto = unCaminante->obtenerObjetosDeLaMochila()->obtenerCursor();
            cout<<"Nombre: "<<unObjeto->obtenerNombre()<<endl;
            cout<<"Cantidad: "<<unObjeto->obtenerCantidad()<<endl<<endl;
        }
    }
}

void TP::enviarInformacionAlGraficador(){
    /* Luego de realizar todas las tareas, se envia la informacion al Mapa y se dibuja el BMP */
    unCaminante->enviarInformacionAlMapa();
}

void TP::buscarAtajo(){
    /* Buscar atajo */
    cout<<"Buscador de atajos:"<<endl;
    cout<<"-------------------"<<endl<<endl;

    unCaminante->buscarAtajo();
}

void TP::dibujarBMP(){
    unCaminante->dibujarBMP();
}

TP::~TP(){
    delete unCaminante;
}
