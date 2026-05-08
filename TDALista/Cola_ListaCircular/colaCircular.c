#include "colaCircular.h"
#include <stdlib.h>
#include <string.h>
#define Minimo(x,y) ( (x) <= (y) ? (x) : (y) )


void crearCola (tCola* c)
{
    *c = NULL;
}
int colaVacia (const tCola* c)
{
    return *c == NULL? COLA_VACIA : COLA_NO_VACIA;
}
int colaLlena (const tCola *c, unsigned tamInfo)
{
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    void* d = malloc(tamInfo);

    free(nue);
    free(d);

    if(nue == NULL || d == NULL) return COLA_LLENA;

    return COLA_NO_LLENA;

}
int ponerCola (tCola*c, void* d, unsigned tamInfo)
{
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    if(nue == NULL) return SIN_MEM;

    nue->info = malloc(tamInfo);
    if(nue->info == NULL)
    {
        free(nue);
        return SIN_MEM;
    }
    ///COPIO LOS DATOS
    memcpy(nue->info,d,tamInfo);
    nue->tamInfo = tamInfo;

    if(*c) ///ME FIJO SI ES EL PRIMER ELEMENTO
    {
        ///HAGO EL ENLACE
        nue->sig = (*c)->sig; ///EL SIG DEL ULTIMO INGRESADO APUNTA AL PRIMER ELEMENTO QUE INGRESE
        (*c)->sig = nue; ///EL SIG DEL ANTEULTIMO INGRESADO APUNTA AL ULTIMO ELEMENTO INGRESADO
    }
    else
        nue->sig = nue; ///COMO ES EL PRIMERO, SE APUNTA A SI MISMO

    *c = nue; ///HAGO QUE LA COLA APUNTE AL ULTIMO QUE INGRESO

    ///OBSERVACION: EL NULL DESAPARECE. PARA SABER SI SOLO QUEDA UN ELEMENTO EN LA COLA---> *C = (*C)->sig, C Y SU SIGUIENTE DEBEN APUNTAR AL MISMO NODO
    return TODO_OK;
}
int sacarCola (tCola*c, void* d, unsigned tamInfo)
{
    if(*c == NULL) return COLA_VACIA;

    tNodo* elim = (*c)->sig;///ELIMINO EL PRIMERO ELEMENTO QUE ENTRO
    if(elim == *c) ///ME FIJO SI EL SIGUIENTE DE C (ELIM) Y C APUNTAN AL MISMO NODO
        *c = NULL; ///YA NO HAY ELEMENTOS
    else
        (*c)->sig = elim->sig; ///HAGO EL ENLACE CON EL SIGUIENTE AL QUE SACO

    memcpy(d,elim->info,Minimo(tamInfo,elim->tamInfo));
    free(elim->info);
    free(elim);

    return TODO_OK;
}
int verTope (const tCola* c, void* d, unsigned tamInfo)
{
    if(*c == NULL) return COLA_VACIA;

    memcpy(d,(*c)->sig->info,Minimo(tamInfo,(*c)->sig->tamInfo));

    return TODO_OK;
}

void vaciarCola (tCola* c)
{
    while(*c)
    {
        tNodo* aux = (*c)->sig;
        if(*c == aux) ///LLEGUE AL ULTIMO ELEMENTO
            *c = NULL; ///SALGO DEL WHILE
        else
            (*c)->sig = aux->sig; ///ENLAZO

        free(aux->info);
        free(aux);
    }
}
