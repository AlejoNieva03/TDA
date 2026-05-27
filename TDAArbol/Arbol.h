#ifndef ARBOL_H_
#define ARBOL_H_

#include <stdio.h>
#include <stdlib.h>

#define PRE_ORDEN 0
#define IN_ORDEN 1
#define POS_ORDEN 2

#define TODO_OK 1
#define SIN_MEM -999
#define DUPLICADO 0


typedef struct sNodo
{
    void* info;
    unsigned tamElem;
    struct sNodo* Izq;
    struct sNodo* Der;
}tNodo;

typedef tNodo* tArbol;

typedef int(*CMP)(const void*,const void*);
typedef void (*IMP)(const void*);

void crearArbol (tArbol* pr);
int InsertarArbolBinario (tArbol* pr, void* dato, unsigned tamElem,CMP cmp);
int InsertarArbolBinarioIterativo (tArbol* pr, void* dato, unsigned tamElem,CMP cmp);
void recorrerArbol (tArbol* pr, int tipoDerecorrido, IMP imp);
void _preOrden (tArbol* pr, IMP imp);
void _InOrden (tArbol* pr, IMP imp);
void _posOrden (tArbol* pr, IMP imp);

///EJERCICIOS
int contarTodosLosNodos (tArbol* pr);
void _contarTodosLosNodos (tArbol* pr, int* cont);

int contarTodosLosNodosHojas (tArbol* pr);
void _contarTodosLosNodosHojas (tArbol* pr, int* cont);
#endif // ARBOL_H_
