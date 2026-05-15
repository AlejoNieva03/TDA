#ifndef LISTADOBLEMENTEENLAZADA_H_
#define LISTADOBLEMENTEENLAZADA_H_

#include "../comun.h"

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* ant;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;

typedef int (*cmp)(const void*,const void*);
typedef void (*accion) (void*, const void*);
typedef void (*imp) (const void*);
typedef void (*Ing) (void* e);

void crearLista (tLista* pl);
int listaVacia (const tLista* pl);
int listaLlena (const tLista* pl, unsigned tamElem);
int verActual (const tLista* pl, void* d, unsigned tamElem);
int insertarListaOrdenadaConDuplicados (tLista* pl, void* d, unsigned tamElem, cmp CMP);
int insertarListaAlFinal (tLista* pl, void* d, unsigned tamElem);
int insertarListaAlInicio (tLista* pl, void* d, unsigned tamElem);
int insertarListaConAccion (tLista* pl, void* d, unsigned tamElem, cmp CMP, accion ACCION);
int eliminarElementoLista (tLista* pl, void* d, unsigned tamElem, cmp CMP);
int ordenarLista (tLista* pl, cmp CMP);
tNodo* buscarMenor (tNodo* act, cmp CMP);
void vaciarLista (tLista* pl);


#endif // LISTADOBLEMENTEENLAZADA_H_
