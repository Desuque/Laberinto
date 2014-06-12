#include <iostream>
#include "cargadorDeRecorridos.h"
#include "Caminante.h"
#include "Mochila.h"
#include "Objeto.h"
#include "Lista.h"

using namespace std;

int main()
{
    cout<<"El laberinto maldito:"<<endl;
    cout<<"====================="<<endl;
    cout<<endl;
    string archivoDeCaminos="Caminos.txt";
    Lista<Lista<string>*>* recorridos;
    Mochila unaMochila;
    Lista<Objeto>* listaDeObjetos;

    CargadorDeRecorridos registroDeRecorridos(archivoDeCaminos);
    recorridos = registroDeRecorridos.obtenerRecorridos();

    Caminante unCaminante(recorridos);
    unCaminante.logisticaDelRecorrido(recorridos);

    /* Dibuja el recorrido en el BMP */
    unCaminante.enviarInformacionAlMapa();

    //Muestro por pantalla los objetos de la mochila
    cout<<"Objetos guardados en la mochila:"<<endl;
    cout<<"--------------------------------"<<endl<<endl;

    listaDeObjetos = unCaminante.obtenerObjetosDeLaMochila();
    if (listaDeObjetos->contarElementos()==0){
        cout<<"La mochila esta vacia."<<endl;
    }
    else{
        (listaDeObjetos)->iniciarCursor();
        while (listaDeObjetos->avanzarCursor()){
            Objeto unObjeto = listaDeObjetos->obtenerCursor();
            cout<<"Nombre: "<<unObjeto.obtenerNombre()<<endl;
            cout<<"Cantidad: "<<unObjeto.obtenerCantidad()<<endl<<endl;
        }
    }
}
