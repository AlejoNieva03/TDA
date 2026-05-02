#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "../../TDA/listaDinamica/lista.h"
#define TAM_NYAP 100
#define TAM_NOM_PRO 50
#define FIN_MENU 10

typedef struct
{
    char nyap[TAM_NYAP + 1];
    size_t dni;
}tPersona;

typedef struct
{
    int codigo;
    char nombre[TAM_NOM_PRO+1];
}tProducto;



int _InsertarAlFinal(tLista* p);
int _InsertarEnOrden(tLista* p, cmp CMP);
int _eliminarElementoPosN (tLista* p, void* d, int pos);

int _MostrarLista(const tLista *p, imp IMP);

#endif // MAIN_H_
