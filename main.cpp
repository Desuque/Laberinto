#include <iostream>
#include "CargadorDeRecorridos.h"
#include "Caminante.h"
#include "Mochila.h"
#include "Objeto.h"
#include "Lista.h"

using namespace std;

int main()
{
    string archivoDeCaminos="Caminos.txt";
    Lista<Lista<string>*>* recorridos;
    Mochila unaMochila;
    Lista<Objeto>* listaDeObjetos;

    cout<<"El laberinto maldito:"<<endl;
    cout<<"====================="<<endl;
    cout<<endl;

    /* Cargo los recorridos en memoria */
    CargadorDeRecorridos registroDeRecorridos(archivoDeCaminos);
    recorridos = registroDeRecorridos.obtenerRecorridos();

    /* Envio los recorridos al Caminante */
    Caminante unCaminante(recorridos);
    unCaminante.logisticaDelRecorrido(recorridos);
    unCaminante.dibujarBMP();

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
