#include "Pila.h"


void crearPila(tPila* p)
{
    *p = NULL;
}
int pilaLlena (const tPila* p, unsigned tamDato)
{
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    void* d = malloc(tamDato);

    free(nue);
    free(d);
    if(d == NULL || nue == NULL) return PILA_LLENA;

    return PILA_NO_LLENA;
}
int pilaVacia (const tPila* p)
{
    return *p == NULL? PILA_NO_VACIA: PILA_NO_VACIA;
}
int ponerEnPila (tPila* p, const void* d, unsigned tamDato)
{
     tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
     if(nue == NULL) return PILA_LLENA;
     nue->info = malloc(tamDato);
     if(nue->info == NULL)
     {
         free(nue);
         return PILA_LLENA;
     }
     ///COPIO LOS DATOS
     memcpy(nue->info,d,tamDato);
     nue->tamInfo = tamDato;

     if(*p) ///ME FIJO SI ES EL PRIMERO
    {
        nue->sig = (*p)->sig; ///HAGO EL ENLACE DE QUE, EL ULTIMO QUE INGRESO APUNTE AL ANTERIOR INGRESADO
        (*p)->sig = nue; ///EL PRIMER ELEMENTO DE LA PILA APUNTARA AL ULTIMO

    }
    else
    {
        *p = nue; ///SIEMPRE APUNTARA AL PRIMERO
        nue->sig = nue; ///SE APUNTA A SI MISMO
    }

    return TODO_OK;
}
int desapilar (tPila* p, void* d, unsigned tamDato)
{
    if(*p == NULL) return PILA_VACIA; ///ME FIJO SI LA PILA ESTA VACIA
    tNodo* elim = (*p)->sig;
    if(elim == *p)///YA NO QUEDAN ELEMENTOS
        *p = NULL;
    else
        (*p)->sig = elim->sig; ///AVANZO AL SIGUIENTE
    ///COPIO LOS DATOS EN LA VARIABLE
    memcpy(d,elim->sig,Minimo(tamDato,elim->tamInfo));
    free(elim->info);
    free(elim);

    return TODO_OK;
}
int verTope (const tPila* p, void* d, unsigned tamDato)
{
    if(*p == NULL) return PILA_VACIA; ///ME FIJO SI LA PILA ESTA VACIA
    memcpy(d,(*p)->sig->info,Minimo(tamDato,(*p)->sig->tamInfo));
    return TODO_OK;
}
void vaciarPila (tPila* p)
{
    while(*p)
    {
        tNodo* aux = (*p)->sig;
        if(aux == *p)
            *p = NULL;
        else
             (*p)->sig = aux->sig;
        free(aux->info);
        free(aux);
    }

}
