#include <iostream>
#include <string>
#include "Mapa.h"
#include "EasyBMP.h"
#include "EasyBMP_Font.h"
#include "Lista.h"
#include "Nodo.h"

using namespace std;

const int grosorDelCamino=5;
const int R=0;
const int G=1;
const int B=2;

Mapa::Mapa(){
    this->pasosVerticales=0;
    this->pasosHorizontales=0;
    this->coordenadaVertical=0;
    this->coordenadaHorizontal=25;
    this->nuevoOrigenX=0;
    this->nuevoOrigenY=0;

    this->anchoBMP=0;
    this->altoBMP=0;

}

Mapa::~Mapa(){
}

//
//void Mapa::defase(int* defase){
//    this->coordenadaHorizontal=defase[0];
//    this->coordenadaVertical=defase[1];
//}

void Mapa::firmaDelMapa(BMP Laberinto){
    /*
    RGBApixel colorDeFuente;
    colorDeFuente.Red = 0;
    colorDeFuente.Green = 0;
    colorDeFuente.Blue = 0;
    int FontHeight = 20;
    int CursorI = 103;
    int CursorJ = 3;
    char firma[40] = "Grupo 9 | Algoritmos II (Catedra Calvo)";
    PrintString( Laberinto, firma, CursorI, CursorJ, FontHeight, colorDeFuente );
*/
}

void Mapa::colorActual(string rgb){
    int codigoDeColor=0;
    int j=0;
    string rgbAuxiliar;
    for(unsigned int i=3; i<rgb.length(); i++){
        if((rgb[i])!=' '){
            rgbAuxiliar=rgbAuxiliar+rgb[i];
        }
        else{
            istringstream convert(rgbAuxiliar);
            convert>>codigoDeColor;
            ColorActual[j]=codigoDeColor;
            rgbAuxiliar="";
            j++;
        }
    }
    istringstream convert(rgbAuxiliar);
    convert>>codigoDeColor;
    ColorActual[j]=codigoDeColor;
}

void Mapa::calcularTamanioBMP(Lista<pair<int, int> > listaDeCoordenadas){

    int pasosTotalesX=0;
    int pasosTotalesY=0;

    listaDeCoordenadas.iniciarCursor();
    while (listaDeCoordenadas.avanzarCursor()){
        pasosTotalesX += (listaDeCoordenadas.obtenerCursor()).first;
        pasosTotalesY += (listaDeCoordenadas.obtenerCursor()).second;
    }

    this->anchoBMP=abs(pasosTotalesX)+1024;
    this->altoBMP=abs(pasosTotalesY)+1024;
}

void Mapa::dibujarRecorrido(Lista<pair<int, int> > listaDeCoordenadas){
    BMP Laberinto;
    Laberinto.SetBitDepth(32);
    Laberinto.SetSize(this->anchoBMP,this->altoBMP);
    listaDeCoordenadas.iniciarCursor();
    while (listaDeCoordenadas.avanzarCursor()){
        pasosHorizontales = (listaDeCoordenadas.obtenerCursor()).first;
        pasosVerticales = (listaDeCoordenadas.obtenerCursor()).second;

        /*Si los pasos son negativos*/

        if ( (pasosHorizontales<0) or (pasosVerticales<0)){

            // El "-1" es para evitar el defasaje
            for (int i=nuevoOrigenX+coordenadaHorizontal+grosorDelCamino-1;i>(coordenadaHorizontal+pasosHorizontales); i--){
                for (int j=nuevoOrigenY+coordenadaVertical; j<=(coordenadaVertical+grosorDelCamino); j++){
                    Laberinto(i,j)->Red = ColorActual[R];
                    Laberinto(i,j)->Green = ColorActual[G];
                    Laberinto(i,j)->Blue = ColorActual[B];
                }
            }
            for (int i=nuevoOrigenX+coordenadaHorizontal;i<(coordenadaHorizontal+grosorDelCamino); i++){
                for (int j=nuevoOrigenY+coordenadaVertical+grosorDelCamino; j>=(coordenadaVertical+pasosVerticales); j--){
                    Laberinto(i,j)->Red = ColorActual[R];
                    Laberinto(i,j)->Green = ColorActual[G];
                    Laberinto(i,j)->Blue = ColorActual[B];
                }
            }

        }

        /*Si los pasos son positivos*/
        else{
            for (int i=coordenadaHorizontal;i<(coordenadaHorizontal+pasosHorizontales);i++){
                for (int j=coordenadaVertical; j<(coordenadaVertical+grosorDelCamino); j++){
                    Laberinto(i,j)->Red = ColorActual[R];
                    Laberinto(i,j)->Green = ColorActual[G];
                    Laberinto(i,j)->Blue = ColorActual[B];
                }
            }
            for (int i=coordenadaHorizontal;i<(coordenadaHorizontal+grosorDelCamino);i++){
                for (int j=coordenadaVertical; j<(coordenadaVertical+pasosVerticales); j++){
                    Laberinto(i,j)->Red = ColorActual[R];
                    Laberinto(i,j)->Green = ColorActual[G];
                    Laberinto(i,j)->Blue = ColorActual[B];
                }
            }
        }

        coordenadaVertical+=pasosVerticales;
        coordenadaHorizontal+=pasosHorizontales;
    }

    firmaDelMapa(Laberinto);
    Laberinto.WriteToFile("Salida.bmp");
}
