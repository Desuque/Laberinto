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
const int x=0;
const int y=1;

Mapa::Mapa(){
    this->pasosVerticales=0;
    this->pasosHorizontales=0;
    this->coordenadaVertical=0;
    this->coordenadaHorizontal=0;
    this->colorActual=0;
    this->Laberinto.SetBitDepth(32);
    this->Laberinto.SetSize(250,80);
}

Mapa::~Mapa(){
}

void Mapa::marcarEjes(){
    RGBApixel colorTexto;
    colorTexto.Red = 0 ;
    colorTexto.Green = 0;
    colorTexto.Blue = 0;

    char Norte[6] = "Norte";
    char Sur[4] = "Sur";
    char Oeste[6] = "Oeste";
    char Este[5] = "Este";

    int lugarHorizontal=1024/2;
    int horizontal_NS = 450;
    int vertical_N = 3;
    int vertical_S= 900;
    int CursorVertical = 450;
    int CursorJ = 3;
    int tamanioFuente = 25;

    PrintString(Laberinto, Norte, horizontal_NS, vertical_N, tamanioFuente, colorTexto);
    PrintString(Laberinto, Sur, horizontal_NS, vertical_S, tamanioFuente, colorTexto);
    //PrintString(Laberinto, Oeste, CursorVertical, CursorHorizontal, tamanioFuente, colorTexto);
    //PrintString(Laberinto, Este, CursorVertical, CursorHorizontal, tamanioFuente, colorTexto);
}

void Mapa::cargarColor(int* rgb){
    this->colorActual=rgb;
}

void Mapa::cargarRecorrido(Lista<pair<int, int> >* listaDeCoordenadas){
    coordenadaHorizontal=nuevoOrigen.first;
    coordenadaVertical=nuevoOrigen.second;

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
}

void Mapa::cargarNuevoOrigen(pair<int, int> nuevoOrigen){
    this->nuevoOrigen=nuevoOrigen;
}

void Mapa::marcarObjetos(Lista<pair<int, int> >* coordenadasPorMarcar){
    RGBApixel nuevoColor;
    nuevoColor.Red = 0;
    nuevoColor.Green = 0;
    nuevoColor.Blue = 0;

    coordenadasPorMarcar->iniciarCursor();
    while (coordenadasPorMarcar->avanzarCursor()){
        int coordenadaX=(coordenadasPorMarcar->obtenerCursor()).first+nuevoOrigen.first;
        int coordenadaY=(coordenadasPorMarcar->obtenerCursor()).second+nuevoOrigen.second;
        Laberinto.SetPixel(coordenadaX,coordenadaY,nuevoColor);
    }
}

void Mapa::dibujarRecorridos(){
    marcarEjes();
    Laberinto.WriteToFile("Salida.bmp");
}
