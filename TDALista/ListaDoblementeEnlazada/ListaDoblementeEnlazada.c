#include "ListaDoblementeEnlazada.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void crearLista (tLista* pl)
{
    *pl = NULL;
}
int insertarListaOrdenadaConDuplicados (tLista* pl, void* d, unsigned tamElem, cmp CMP)
{
    tNodo* act;
    tNodo* auxAnt;
    tNodo* auxSig;

    if(*pl == NULL) ///ES EL PRIMERO A INGRESAR
    {
        auxAnt = NULL;
        auxSig = NULL;
    }
    else
    {
        act = *pl;
        while(act->sig && CMP(d,act->info) > 0)
        {
            act = act->sig;
        }
        while(act->ant && CMP(d,act->info) < 0)
        {
              act = act->ant;
        }

        if(CMP(d,act->info) > 0) ///ME FIJO SI EL DATO QUE QUIERO INGRESAR ES MAYOR AL ACTUAL
        {
            auxAnt = act;
            auxSig = act->sig;

        }
        else
        {
            auxAnt = act->ant;
            auxSig = act;
        }
    }
    ///ENLAZO EL NUEVO A LA LISTA
    tNodo* nue = malloc(sizeof(tNodo));
    if(nue == NULL) return SIN_MEM;
    nue->info = malloc(tamElem);
    if(nue->info == NULL)
    {
        free(nue);
        return SIN_MEM;
    }
    ///COPIO LOS DATOS AL NUEVO NODO
    memcpy(nue->info,d,tamElem);
    nue->tamInfo = tamElem;
    nue->ant = auxAnt;
    nue->sig = auxSig;
    ///DEBO HACER QUE LA LISTA VEA EL NODO
    ///DEBO HACERLO SOLO CUANDO NO SEA NULO
    if(auxSig) auxSig->ant = nue;
    if(auxAnt) auxAnt->sig = nue;

    *pl = nue; ///QUE LA LISTA APUNTE AL ULTIMO QUE INGRESE, APUNTA AL ULTIMO POR CONVENCION DE LA CATEDRA

    return TODO_OK;
}
int eliminarLista (tLista* pl, void* d, unsigned tamElem, cmp CMP)
{
    if(*pl == NULL) return LISTA_VACIA;

    tNodo* act = *pl;
    while(act->sig && CMP(d,act->info) > 0)
    {
        act = act->sig;
    }
    while(act->ant && CMP(d,act->info) < 0)
    {
              act = act->ant;
    }

    if(CMP(d,act->info) != 0) ///ME FIJO SI EL DATO QUE QUIERO INGRESAR ES MAYOR AL ACTUAL
        return NO_ENCONTRADO;

    memcpy(d,act->info,Minimo(tamElem,act->tamInfo)); ///PASO EL DATO COMPLETO (AGARRANDO SIEMPRE EL MINIMO)
    tNodo* auxAnt = act->ant;
    tNodo* auxSig = act->sig;

    free(act->info);
    free(act);
    if(auxAnt)
     {
       auxAnt->sig = auxSig;
     }
     if(auxSig)
     {
       auxSig->ant = auxAnt;
     }
    *pl = auxAnt? auxAnt : auxSig;


    return TODO_OK;

}
