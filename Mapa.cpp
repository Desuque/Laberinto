#include <iostream>
#include <string>
#include "Mapa.h"
#include "EasyBMP.h"
#include "EasyBMP_Font.h"
#include "Lista.h"
#include "Nodo.h"

using namespace std;

const int grosorDelCamino=1;
const int R=0;
const int G=1;
const int B=2;

Mapa::Mapa(){
    this->pasosVerticales=0;
    this->pasosHorizontales=0;
    this->coordenadaVertical=300;
    this->coordenadaHorizontal=300;

    this->colorActual=0;

    this->Laberinto.SetBitDepth(32);
    this->Laberinto.SetSize(1024,1024);
}

Mapa::~Mapa(){
}

void Mapa::cargarColor(int* rgb){
    this->colorActual=rgb;
}

void Mapa::cargarRecorrido(Lista<pair<int, int> >* listaDeCoordenadas){
    listaDeCoordenadas->iniciarCursor();
    while (listaDeCoordenadas->avanzarCursor()){
        pasosHorizontales = (listaDeCoordenadas->obtenerCursor()).first;
        pasosVerticales = (listaDeCoordenadas->obtenerCursor()).second;

        /*Si los pasos son negativos*/

        if ( (pasosHorizontales<0) or (pasosVerticales<0)){

            // El "-1" es para evitar el defasaje
            for (int i=coordenadaHorizontal-1;i>(coordenadaHorizontal+pasosHorizontales); i--){
                for (int j=coordenadaVertical; j<(coordenadaVertical+grosorDelCamino); j++){
                    Laberinto(i,j)->Red = colorActual[R];
                    Laberinto(i,j)->Green = colorActual[G];
                    Laberinto(i,j)->Blue = colorActual[B];
                }
            }

            for (int i=coordenadaHorizontal;i<(coordenadaHorizontal+grosorDelCamino); i++){
                for (int j=coordenadaVertical; j>=(coordenadaVertical+pasosVerticales); j--){
                    Laberinto(i,j)->Red = colorActual[R];
                    Laberinto(i,j)->Green = colorActual[G];
                    Laberinto(i,j)->Blue = colorActual[B];
                }
            }


        }

        /*Si los pasos son positivos*/
        else{
            for (int i=coordenadaHorizontal;i<(coordenadaHorizontal+pasosHorizontales);i++){
                for (int j=coordenadaVertical; j<(coordenadaVertical+grosorDelCamino); j++){
                    Laberinto(i,j)->Red = colorActual[R];
                    Laberinto(i,j)->Green = colorActual[G];
                    Laberinto(i,j)->Blue = colorActual[B];
                }
            }

            for (int i=coordenadaHorizontal;i<(coordenadaHorizontal+grosorDelCamino);i++){
                for (int j=coordenadaVertical; j<(coordenadaVertical+pasosVerticales); j++){
                    Laberinto(i,j)->Red = colorActual[R];
                    Laberinto(i,j)->Green = colorActual[G];
                    Laberinto(i,j)->Blue = colorActual[B];
                }
            }

        }
        coordenadaVertical+=pasosVerticales;
        coordenadaHorizontal+=pasosHorizontales;
    }
    //Esto separa los mapas hasta que tengamos las bifurcaciones
    this->coordenadaHorizontal=100;
    this->coordenadaVertical=100;
    this->pasosHorizontales=0;
    this->pasosVerticales=0;
}

void Mapa::dibujarRecorridos(){
    Laberinto.WriteToFile("Salida.bmp");
}
