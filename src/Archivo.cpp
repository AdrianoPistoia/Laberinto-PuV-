#include "Archivo.h"
#include <cstdlib> /// new y delete
#include<stdio.h> /// FILE ARCHIVOS
#include<string.h>
#include "Registro.h"
#include <iostream>
#include "Ranking.h"
//Ranking ObjRanking;
//Archivo ranking ("ranking.dat", sizeof(ObjRanking));

Archivo::Archivo(const char *nombre, int tam ) ///Nombre del archivo y sizeof del registro que contiene el archivo.
{
    nombreArchivo = new char[ strlen(nombre) + 1 ];
    if(nombreArchivo == NULL)exit(1);
    strcpy(nombreArchivo,nombre);
    tamanioRegistro = tam;
    pRegistro = (Registro*) malloc(tamanioRegistro);
    estado = Cerrado;
}

Archivo::~Archivo()
{
    delete [] nombreArchivo;
    free(pRegistro);
    if(p) fclose(p);
}

void Archivo::CargarpRegistro( Registro* padre )
{
    pRegistro = padre; /// la direccion que contiene padre, (ya sea Ranking o Config) se va a asignar en pRegistro.
}

//buscarRegistro(Registro &obj)
//COMPARA EL CAMPO CLAVE DEL REGISTRO RECIBIDO COMO PARAMETRO
//CON LOS REGISTROS DEL ARCHIVO.
//SI YA EXISTE EL VALOR DEL CAMPO CLAVE DEVUELVE LA POSICIÓN QUE OCUPA EN EL ARCHIVO
//SI NO LO ENCUENTRA DEVUELVE -1, Y SI NO PUDO ABRIR EL ARCHIVO DEVUELVE -2
//grabarRegistro( Registro &dato, int pos).
//ESCRIBE EN EL DISCO LOS DATOS EXISTENTES EN LA REFERENCIA dato
//SI EL VALOR DE POS ES -1 AGREGA UN REGISTRO NUEVO
// SI EL VALOR ES 0 O POSITIVO SOBREESCRIBE EL REGISTRO UBICADO EN ESA POSICION
//DEVUELVE 1 SI GRABO; -1 SI NO EXISTE; 0 SI NO PUDO GRABAR
//abrirArchivo(Modo modo)
//ABRE EL ARCHIVO EN EL MODO ESTABLECIDO POR EL PARAMETRO modo.
//DEVUELVE TRUE SI PUDO ABRIR Y FALSE SI NO PUDO ABRIR
bool Archivo::abrirArchivo(Modo modo)
{
    switch(estado)
    {
        case AbiertoRB:
        case AbiertoWB:
        case AbiertoAB:
        case AbiertoRBmas:cerrarArchivo();
        break;
    }
    switch(modo)
    {
        case SoloLectura:
            p=fopen(nombreArchivo,"rb");
            if(!p)return false;
            estado=AbiertoRB;
        break;
        case Escritura:
            p=fopen(nombreArchivo,"wb");
            if(!p)return false;
            estado=AbiertoWB;
        break;
        case Agregar:
            p=fopen(nombreArchivo,"ab");
            if(!p) return false;
            estado=AbiertoAB;
            break;
        case LecturaEscritura:
            p=fopen(nombreArchivo,"rb+");
            if(!p)return false;
            estado=AbiertoRBmas;
        break;
    }
    return true;
}

bool Archivo::defaultArchivo(int cantidad, Registro *padre)
{
    if( !abrirArchivo(SoloLectura) )
    {
        abrirArchivo(Escritura);
        for(int i = 0; i < cantidad; i++ )
        {
            if(! fwrite( padre, tamanioRegistro, 1, p) )
            {
                std::cout<<"\n ERROR::ESCRITURA"<<std::endl;
                cerrarArchivo();
                return false;
            }
        }
    }
    cerrarArchivo();
    return true;
}
