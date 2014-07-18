/****************************************************
 ***Algoritmo: Dijkstra (One Source Shortest Path)
 ***Tipo: Grafos
 ***Autor: Jhosimar George Arias Figueroa
 ****************************************************/

#include "Dijkstra.h"
using namespace std;

Dijkstra::Dijkstra(Lista<Camino* >* caminos, Lista<int>* recorridoMinimo){
    /* La cantidad de vertices del grafo es igual a la cantidad de puntos de interes */
    int vertices=0;
    for(unsigned int i=1; i<=caminos->contarElementos(); i++){
        Camino* unCamino = caminos->obtener(i);
        vertices+=unCamino->obtenerPuntosDeInteres()->contarElementos();
    }
    this->caminos=caminos;
    this->V=vertices;
    this->aristas=vertices-1;
    this->recorridoMinimo=recorridoMinimo;

    this->Q = new priority_queue< Node , std::vector<Node> , cmp >;
}

//función de inicialización
void Dijkstra::init(){
    for( int i = 0 ; i <= V ; ++i ){
        distancia[ i ] = INF;  //inicializamos todas las distancias con valor infinito
        visitado[ i ] = false; //inicializamos todos los vértices como no visitados
        previo[ i ] = -1;      //inicializamos el previo del vertice i con -1
    }
}

//Paso de relajacion
void Dijkstra::relajacion( int actual , int adyacente , int peso ){
    //Si la distancia del origen al vertice actual + peso de su arista es menor a la distancia del origen al vertice adyacente
    if( distancia[ actual ] + peso < distancia[ adyacente ] ){
        distancia[ adyacente ] = distancia[ actual ] + peso;  //relajamos el vertice actualizando la distancia
        previo[ adyacente ] = actual;                         //a su vez actualizamos el vertice previo
        Q->push( Node( adyacente , distancia[ adyacente ] ) ); //agregamos adyacente a la cola de prioridad
    }
}

//Impresion del camino mas corto desde el vertice inicial y final ingresados
void Dijkstra::print( int destino ){
    if( previo[ destino ] != -1 )    //si aun poseo un vertice previo
        print( previo[ destino ] );  //recursivamente sigo explorando

    /* Guardo los caminos mas cortos en la Lista */
    recorridoMinimo->agregar(destino);
}

void Dijkstra::dijkstra( int inicial ){
    init(); //inicializamos nuestros arreglos
    Q->push( Node( inicial , 0 ) ); //Insertamos el vértice inicial en la Cola de Prioridad
    distancia[ inicial ] = 0;      //Este paso es importante, inicializamos la distancia del inicial como 0
    int actual , adyacente , peso;
    while( !Q->empty() ){                   //Mientras cola no este vacia
        actual = Q->top().first;            //Obtengo de la cola el nodo con menor peso, en un comienzo será el inicial
        Q->pop();                           //Sacamos el elemento de la cola
        if( visitado[ actual ] ) continue; //Si el vértice actual ya fue visitado entonces sigo sacando elementos de la cola
        visitado[ actual ] = true;         //Marco como visitado el vértice actual

        for( unsigned int i = 0 ; i < ady[ actual ].size() ; ++i ){ //reviso sus adyacentes del vertice actual
            adyacente = ady[ actual ][ i ].first;   //id del vertice adyacente
            peso = ady[ actual ][ i ].second;        //peso de la arista que une actual con adyacente ( actual , adyacente )
            if( !visitado[ adyacente ] ){        //si el vertice adyacente no fue visitado
                relajacion( actual , adyacente , peso ); //realizamos el paso de relajacion
            }
        }
    }

    string puntoLlegada;
    cout<<"Ingrese el punto de llegada: ";
    cin>>puntoLlegada;

    int ID=buscarIDSegunNombre(puntoLlegada);

    /* Compruebo que el nombre ingresado exista */
    if (ID==INF){
        cout<<"El nombre del punto ingresado no existe, mas suerte la proxima."<<endl;
    }
    else{
        destino=buscarIDSegunNombre(puntoLlegada);
        print( destino );
    }
}

int Dijkstra::buscarIDSegunNombre(string nombre){
    unsigned int i=1;
    unsigned int ID;
    bool encontrado=false;
    string aux;
    while ((i<=caminos->contarElementos()) && (!encontrado)){
        Camino* unCamino = caminos->obtener(i);
        unCamino->obtenerPuntosDeInteres()->iniciarCursor();
        while (unCamino->obtenerPuntosDeInteres()->avanzarCursor()){
            if (unCamino->obtenerPuntosDeInteres()->obtenerCursor()->obtenerNombre()==nombre){
                ID=unCamino->obtenerPuntosDeInteres()->obtenerCursor()->obtenerID();
                encontrado=true;
            }
        }
        i++;
    }
    if (encontrado==false){
        ID=INF;
    }
    return ID;
}

void Dijkstra::inicializarValores(){

    int origen, destino , peso , inicial;
    while( aristas-- ){
        for(unsigned int i=1; i<=caminos->contarElementos(); i++){
            Camino* unCamino = caminos->obtener(i);
            for (unsigned int j=1; j<=unCamino->obtenerPuntosDeInteres()->contarElementos(); j++){
                PuntoDeInteres* unPuntoDeInteres = unCamino->obtenerPuntosDeInteres()->obtener(j);
                peso=unPuntoDeInteres->obtenerPeso();
                origen=unPuntoDeInteres->obtenerID();
                destino=unPuntoDeInteres->obtenerUnion();

                ady[ origen ].push_back( Node( destino , peso ) ); //consideremos grafo dirigido
                ady[ destino ].push_back( Node( origen , peso ) ); //grafo no dirigido
            }
        }
    }

    string puntoPartida;

    cout<<"Ingrese el punto de partida: ";
    cin>>puntoPartida;

    /* Compruebo que el nombre ingresado exista */
    int ID=buscarIDSegunNombre(puntoPartida);
    if (ID==INF){
        cout<<"El nombre del punto ingresado no existe, mas suerte la proxima."<<endl;
    }
    else{
        inicial=ID;
        dijkstra( inicial );
    }
}

Dijkstra::~Dijkstra(){
    delete Q;
}
