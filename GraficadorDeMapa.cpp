#include "GraficadorDeMapa.h"
#include "EasyBMP_Font.h"

using namespace std;

const int grosorDelCamino=1;
const int R=0;
const int G=1;
const int B=2;
const int x=0;
const int y=1;

GraficadorDeMapa::GraficadorDeMapa(){
    this->Laberinto.SetBitDepth(32);
    this->pasosVerticales=0;
    this->pasosHorizontales=0;
    this->coordenadaVertical=0;
    this->coordenadaHorizontal=0;
    this->colorActual=0;
}

void GraficadorDeMapa::cargarTamanioBMP(int anchoBMP, int altoBMP){
    this->anchoBMP=anchoBMP;
    this->altoBMP=altoBMP;
    this->Laberinto.SetSize(anchoBMP, altoBMP);
}

void GraficadorDeMapa::cargarOrigen(pair<int, int> origen){
    this->origen=origen;
}

void GraficadorDeMapa::cargarColor(int* rgb){
    this->colorActual=rgb;
}

void GraficadorDeMapa::cargarRecorrido(Lista<pair<int, int> >* listaDeCoordenadas){
    SetEasyBMPwarningsOff();
    coordenadaHorizontal=origen.first;
    coordenadaVertical=origen.second;

    listaDeCoordenadas->iniciarCursor();
    while (listaDeCoordenadas->avanzarCursor()){
        pasosHorizontales = (listaDeCoordenadas->obtenerCursor()).first;
        pasosVerticales = (listaDeCoordenadas->obtenerCursor()).second;

        /*Si los pasos son negativos*/

        if ( (pasosHorizontales<0) || (pasosVerticales<0)){

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

void GraficadorDeMapa::marcarObjetos(Lista<pair<int, int> >* coordenadasPorMarcar){
    RGBApixel nuevoColor;
    nuevoColor.Red = 0;
    nuevoColor.Green = 0;
    nuevoColor.Blue = 0;

    coordenadasPorMarcar->iniciarCursor();
    while (coordenadasPorMarcar->avanzarCursor()){
        int coordenadaX=(coordenadasPorMarcar->obtenerCursor()).first;
        int coordenadaY=(coordenadasPorMarcar->obtenerCursor()).second;
        Laberinto.SetPixel(origen.first+coordenadaX,origen.second+coordenadaY,nuevoColor);
    }
}

void GraficadorDeMapa::dibujarRecorridos(){
    marcarEjes();
    Laberinto.WriteToFile("Salida.bmp");
}

void GraficadorDeMapa::marcarEjes(){
    RGBApixel colorTexto;
    colorTexto.Red = 0 ;
    colorTexto.Green = 0;
    colorTexto.Blue = 0;

    char Norte[2] = "N";
    char Sur[2] = "S";
    char Oeste[2] = "O";
    char Este[2] = "E";

    int horizontal_NS = anchoBMP / 2.3;
    int vertical_OE = altoBMP / 2.3;
    int vertical_N = 3;
    int vertical_S= altoBMP-25;
    int horizontal_O = 3;
    int horizontal_E = anchoBMP-15;
    int tamanioFuente = 15;

    PrintString(Laberinto, Norte, horizontal_NS, vertical_N, tamanioFuente, colorTexto);
    PrintString(Laberinto, Sur, horizontal_NS, vertical_S, tamanioFuente, colorTexto);
    PrintString(Laberinto, Oeste, horizontal_O, vertical_OE, tamanioFuente, colorTexto);
    PrintString(Laberinto, Este, horizontal_E, vertical_OE, tamanioFuente, colorTexto);
}

GraficadorDeMapa::~GraficadorDeMapa(){
}
