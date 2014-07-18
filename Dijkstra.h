#ifndef DIJKSTRA_H_INCLUDED
#define DIJKSTRA_H_INCLUDED
#define Node std::pair< int , int > //definimos el nodo como un par( first , second ) donde first es el vertice adyacente y second el peso de la arista

#include "Lista.h"
#include "Camino.h"
#include <queue>
#define MAX 10005 //maximo numero de vértices
#define INF 1<<30 //definimos un valor grande que represente la distancia infinita inicial, basta conque sea superior al maximo valor del peso en alguna de las aristas

class Dijkstra{
private:
    /*Guarda los caminos que generan el recorrido mas corto */
    Lista<int>* recorridoMinimo;

    //La cola de prioridad de C++ por default es un max-Heap (elemento de mayor valor en el tope)
    //por ello es necesario realizar nuestro comparador para que sea un min-Heap
    struct cmp {
        bool operator() ( const Node &a , const Node &b ) {
        return a.second > b.second;
    }
    };

    int V; // numero de vertices
    int aristas;
    Lista<PuntoDeInteres>* puntosDeInteres;
    std::vector< Node > ady[ MAX ]; //lista de adyacencia
    int distancia[ MAX ];      //distancia[ u ] distancia de vértice inicial a vértice con ID = u
    bool visitado[ MAX ];      //para vértices visitados
    std::priority_queue< Node , std::vector<Node> , cmp >* Q; //priority queue propia del c++, usamos el comparador definido para que el de menor valor este en el tope
    int previo[ MAX ];         //para la impresion de caminos
    int origen;
    int destino;
    Lista<Camino* >* caminos;

public:
    Dijkstra(Lista<Camino* >* caminos, Lista<int>* recorridoMinimo);
    void inicializarValores();
    ~Dijkstra();

private:
    void init();
    void relajacion( int actual , int adyacente , int peso );
    void print( int destino );
    void dijkstra( int inicial );
    int buscarIDSegunNombre(std::string nombre);
};

#endif // DIJKSTRA_H_INCLUDED
