#include "ListaDoblementeEnlazada.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void crearLista (tLista* pl)
{
    *pl = NULL;
}
int listaVacia (const tLista* pl)
{
    return *pl == NULL? LISTA_VACIA: LISTA_NO_VACIA;
}
int listaLlena (const tLista* pl, unsigned tamElem)
{
    tNodo* nue = malloc(sizeof(tNodo));
    void* d = malloc(tamElem);
    free(nue);
    free(d);
    if(nue == NULL || d == NULL) return LISTA_LLENA;

    return LISTA_NO_LLENA;
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
int insertarListaAlFinal (tLista* pl, void* d, unsigned tamElem)
{
    tNodo* act = *pl;
    tNodo* auxAnt;

    if(act == NULL) ///ES EL PRIMERO A INGRESAR
    {
        auxAnt = NULL;
    }
    else
    {
        while(act->sig)
            act = act->sig;
        auxAnt = act;
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
    nue->sig = NULL; ///LE PONGO ESTO PORQUE ES EL ULTIMO
    ///AHORA DEBO HACER QUE LA LISTA VEA AL NUEVO
    if(auxAnt) auxAnt->sig = nue;

    *pl = nue;

    return TODO_OK;

}
int insertarListaAlInicio (tLista* pl, void* d, unsigned tamElem)
{
    tNodo* act = *pl;
    tNodo* auxSig;

    if(act == NULL) ///ES EL PRIMERO A INGRESAR
    {
        auxSig = NULL;
    }
    else
    {
        while(act->ant)
            act = act->ant;
        auxSig = act;
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
    nue->ant = NULL;
    nue->sig = auxSig; ///LE PONGO ESTO PORQUE ES EL ULTIMO
    ///AHORA DEBO HACER QUE LA LISTA VEA AL NUEVO
    if(auxSig) auxSig->ant = nue;

    *pl = nue;

    return TODO_OK;
}
int eliminarElementoLista (tLista* pl, void* d, unsigned tamElem, cmp CMP)
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
int ordenarLista (tLista* pl, cmp CMP)
{
    if(*pl == NULL) return LISTA_VACIA;

    tNodo* act = *pl;
    tNodo* auxSig;
    tNodo* auxAnt;
     while(act->ant)
            act = act->ant;
    while(act->sig)
    {
        tNodo* menor = buscarMenor(act,CMP);
        if(menor != act)
        {
            ///DESENGANCHO EL MENOR DEL LUGAR EN EL QUE ESTA
            auxSig = menor->sig;
            auxAnt = menor->ant;
            auxAnt->sig = auxSig;
            if(auxSig)
                auxSig->ant = auxAnt;

            ///AHORA DEBO ENGANCHAR AL MENOR AL INICIO
            auxAnt = act->ant; ///GUARDO EL ANTERIOR AL MENOR
            menor->sig = act; ///EL SIGUIENTE DEL MENOR SE ENGANCHA CON EL ACTUAL
            menor->ant = auxAnt; ///EL ANTERIOR AL MENOR SE ENGANCHA CON EL ANTERIOR DEL ACTUAL
            act->ant = menor; ///EL NUEVO ANTERIOR DEL ACTUAL ES EL MENOR
            if(auxAnt) ///ME FIJO SI EL ANTERIOR ORIGIAL DEL ACTUAL ES NULO
                auxAnt->sig = menor; ///ENGANCHO QUE EL SIGUIENTE DEL ANTERIOR ORIGINAL DEL ACTUAL SE ENGANCHE CON EL MENOR
        }
        else
           act = act->sig;
    }


    return TODO_OK;
}
tNodo* buscarMenor (tNodo* act, cmp CMP)
{
    if(act == NULL) return NULL;
    tNodo* men = act;
    tNodo* aux = act->sig;
    while(aux)
    {
        if(CMP(men->info,aux->info) > 0)
             men = aux;
        aux = aux->sig;
    }
    return men;
}
int verActual (const tLista* pl, void* d, unsigned tamElem)
{
    if(*pl == NULL) return LISTA_VACIA;

    memcpy(d,(*pl)->info,Minimo(tamElem,(*pl)->tamInfo));

    return TODO_OK;
}
void vaciarLista (tLista* pl)
{
    tNodo* act = *pl;
    if(act)
    {
        while(act->sig)
           act = act->sig;
        while(act)
           {
               tNodo* aux = act->ant;
               free(act->info);
               free(act);
               act = aux;
           }
           *pl = NULL;
    }
}
