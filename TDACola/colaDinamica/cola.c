#include "cola.h"
#include <stdlib.h>
#include <string.h>
#define Minimo(x,y) ( (x) <= (y) ? (x) : (y) )


void crearCola (tCola* p)
{
    p->pri = NULL;
    p->ult = NULL; ///NO HACE FALTA
}
int colaVacia (const tCola* p)
{
    return p->pri == NULL? COLA_VACIA : COLA_NO_VACIA;
}
int colaLlena (const tCola* p, unsigned tamElem)
{
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    void* d = malloc(tamElem);

    free(nue);
    free(d);

    if(nue == NULL || d == NULL) return COLA_LLENA;

    return COLA_NO_LLENA;
}
int ponerEnCola (tCola* p, const void* dato, unsigned tamElem)
{
    tNodo* nue = (tNodo*) malloc(sizeof(tNodo));

    if(nue == NULL || (nue->info = malloc(tamElem)) == NULL)
    {
        free(nue);
        return SIN_MEM;
    }
    ///SI ESTOY ACA, HAY MEMORIA
    memcpy(nue->info,dato,tamElem);
    nue->tamInfo = tamElem;
    nue->sig = NULL;
    ///DEBO FIJARME SI ES EL PRIMER ELEMENTO A INGRESAR
    if(p->ult)
        p->ult->sig = nue; ///HAGO EL ENLACE
    else
        p->pri = nue; ///SI ES EL PRIMERO, LO ASIGNO

    p->ult = nue; ///PONGO CUAL ES EL ULTIMO ACTUAL

    return TODO_OK;
}
int SacarDeCola (tCola* p, void* dato, unsigned tamElem)
{
    if(p->pri == NULL) return COLA_VACIA;
    tNodo* aux = p->pri; ///Uso un nuevo puntero
    p->pri = aux->sig; ///Hago que el primero apunte al siguiente nodo (o a NULL si no hay mas elementos)
    memcpy(dato,aux->info,Minimo(tamElem,aux->tamInfo)); ///AGARRO EL MINIMO
    ///LIBERO EL NODO ANTIGUO
    free(aux->info);
    free(aux);
    ///ME FIJO SI YA NO QUEDA ELEMENTOS EN LA COLA
    if(p->pri == NULL) p->ult = NULL;


    return TODO_OK;

}
void vaciarCola (tCola* p)
{
    while(p->pri) ///ME MUEVO MIENTRAS NO SEA P->PRI == NULL
    {
        tNodo* aux = p->pri;
        p->pri = aux->sig;
        free(aux->info);
        free(aux);
    }
    p->ult = NULL; ///PONGO EL ULTIMO EN NULL
}
int verPrimero (const tCola *p, void* dato, unsigned tamElem)
{
    if(p->pri == NULL) return COLA_VACIA;
    memcpy(dato,p->pri->info,Minimo(tamElem,p->pri->tamInfo)); ///AGARRO EL MINIMO
    return TODO_OK;

}
