#include "Arbol.h"
#include <string.h>

void crearArbol (tArbol* pr)
{
    *pr = NULL;
}
int InsertarArbolBinario (tArbol* pr, void* dato, unsigned tamElem,CMP cmp)
{
    if(*pr == NULL)
    {
        *pr = (tNodo*)malloc(sizeof(tNodo));
        if(*pr == NULL)
            return SIN_MEM;
        (*pr)->info = malloc(tamElem);
        if((*pr)->info == NULL)
        {
            free(*pr);
            return SIN_MEM;
        }
        ///COPIO LOS DATOS
        memcpy((*pr)->info,dato,tamElem);
        (*pr)->tamElem = tamElem;
        (*pr)->Der = NULL;
        (*pr)->Izq = NULL;
        return TODO_OK;
    }
    int ret = cmp(dato,(*pr)->info);
    if(ret > 0)
        return InsertarArbolBinario(&(*pr)->Der,dato,tamElem,cmp);
    if(ret < 0)
         return InsertarArbolBinario(&(*pr)->Izq,dato,tamElem,cmp);

    return DUPLICADO; ///EN ARBOLES DE BUSQUEDA BINARIA NO SE ADMITEN DUPLICADOS

}
int InsertarArbolBinarioIterativo (tArbol* pr, void* dato, unsigned tamElem,CMP cmp)
{
    int ret = 10;
    while(*pr && ret != DUPLICADO)
    {
        ret = cmp(dato,(*pr)->info);
        if(ret > 0)
            pr = &(*pr)->Der;
        if(ret < 0)
            pr = &(*pr)->Izq;
    }
    if(ret != DUPLICADO)
    {
        *pr = (tNodo*)malloc(sizeof(tNodo));
        if(*pr == NULL)
            return SIN_MEM;
        (*pr)->info = malloc(tamElem);
        if((*pr)->info == NULL)
        {
            free(*pr);
            return SIN_MEM;
        }
        ///COPIO LOS DATOS
        memcpy((*pr)->info,dato,tamElem);
        (*pr)->tamElem = tamElem;
        (*pr)->Der = NULL;
        (*pr)->Izq = NULL;
        return TODO_OK;
    }

    return ret;
}



///FUNCIONES DE RECORRER COMUN
void recorrerArbol (tArbol* pr, int tipoDerecorrido, IMP imp)
{
    switch(tipoDerecorrido)
    {
    case PRE_ORDEN:
        {
            _preOrden(pr,imp);
                break;
        }
        case IN_ORDEN:
        {
            _InOrden(pr,imp);
                break;
        }
        case POS_ORDEN:
        {
            _posOrden(pr,imp);
                break;
        }
    default:
        {
            puts("Tipo de recorrido no valido");
        }
    }
}
void _preOrden (tArbol* pr,IMP imp)
{
    if(*pr == NULL)
        return;
    imp((*pr)->info); ///HAGO LA ACCION
    _preOrden(&(*pr)->Izq,imp);
    _preOrden(&(*pr)->Der,imp);
}
void _InOrden (tArbol* pr, IMP imp)
{
    if(*pr == NULL)
        return;
    _InOrden(&(*pr)->Izq,imp);
    imp((*pr)->info); ///HAGO LA ACCION
    _InOrden(&(*pr)->Der,imp);

}
void _posOrden (tArbol* pr, IMP imp)
{
    if(*pr == NULL)
        return;
    _posOrden(&(*pr)->Izq,imp);
    _posOrden(&(*pr)->Der,imp);
     imp((*pr)->info); ///HAGO LA ACCION
}

///EJERCICIOS
int contarTodosLosNodos (tArbol* pr)
{
    int nodos = 0;
    _contarTodosLosNodos(pr,&nodos);
    return nodos;
}
void _contarTodosLosNodos (tArbol* pr, int* cont)
{
    if(*pr == NULL) return;
    *cont += 1;
    _contarTodosLosNodos(&(*pr)->Izq,cont);
    _contarTodosLosNodos(&(*pr)->Der,cont);
}

int contarTodosLosNodosHojas (tArbol* pr)
{
    int nodos = 0;
    _contarTodosLosNodosHojas(pr,&nodos);
    return nodos;
}

void _contarTodosLosNodosHojas (tArbol* pr, int* cont)
{
    if(*pr == NULL) return;
    if((*pr)->Izq == NULL && (*pr)->Der == NULL)
    {
        *cont += 1;
        return;
    }

    _contarTodosLosNodosHojas(&(*pr)->Izq,cont);
    _contarTodosLosNodosHojas(&(*pr)->Der,cont);
}
