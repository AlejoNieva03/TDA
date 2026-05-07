#include "lista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void crearLista (tLista* p)
{
    *p = NULL;
}
int listaVacia (const tLista* p)
{
    return *p == NULL? LISTA_VACIA : LISTA_NO_VACIA;
}
int listaLlena (const tLista* p, unsigned tamElem)
{
    tNodo* lista = (tNodo*)malloc(sizeof(tNodo));
    void* elem = malloc(tamElem);
    free(lista);
    free(elem);
    if(lista == NULL || elem == NULL) return SIN_MEM;
    return LISTA_NO_LLENA;
}
void vaciarLista (tLista *p)
{
    while(*p) ///ME MUEVO MIENTRAS *p sea NULL
    {
        tNodo* aux = *p;
        *p = aux->sig;
        free(aux->info);
        free(aux);
    }
}
///FUNCIONES DE INSERTAR
int InsertarAlComienzo (tLista *p, void* d, unsigned tamInfo)
{
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    if(nue == NULL) return SIN_MEM;
    nue->info = malloc(tamInfo);
    if(nue->info == NULL)
    {
        free(nue);
        return SIN_MEM;
    }
    memcpy(nue->info,d,tamInfo);
    nue->tamInfo = tamInfo;
    nue->sig = *p; ///HAGO EL ENLACE CON EL SIGUIENTE
    *p = nue; ///ACTUALIZO EL NUEVO
    return TODO_OK;
}
int InsertarPosicionN (tLista *p, void* d, unsigned tamInfo, int pos)
{
    int cant = 1;
    if(pos <= 0) return ERROR;
    while(*p && cant < pos) ///ME MUEVO MIENTRAS PUEDA Y HASTA QUE LLEGUE A LA POSICION QUE BUSCO
    {
        p = &(*p)->sig; ///MUEVO LA VARIABLE LOCAL
        cant++;
    }
    if(cant < pos && pos != 1) ///ME FIJO SI, MANDE UNA POSICION INVALIDA Y SI ESA POSICION NO SERA LA PRIMERA INGRESADA
        return ERROR;
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    if(nue == NULL) return SIN_MEM;
    nue->info = malloc(tamInfo);
    if(nue->info == NULL)
    {
        free(nue);
        return SIN_MEM;
    }
    ///AHORA SI, ACTUALIZO EL NUEVO NODO
    memcpy(nue->info,d,tamInfo);
    nue->tamInfo = tamInfo;
    nue->sig = *p;
    *p = nue; ///HAGO EL ENLACE
    return TODO_OK;
}
int InsertarEnOrden(tLista* p,const void* d, unsigned tamInfo, tComp CMP, int esDup, tAccion ACCION)
{
    tNodo* nue = (tNodo*)malloc (sizeof(tNodo));
    if(nue == NULL) return SIN_MEM;
    nue->info = malloc (tamInfo);
    if(nue->info == NULL)
    {
        free(nue);
        return SIN_MEM;
    }
    memcpy(nue->info,d,tamInfo);
    nue->tamInfo = tamInfo;
    int dato;
    while(*p && (dato = CMP(nue->info,(*p)->info)) > 0)///ME MUEVO MIENTRAS NO SEA NULL Y MIENTRAS EL VALOR A INGRESAR SEA MAYOR AL VALOR APUNTADO
    {
        p = &(*p)->sig; ///MUEVO LA VARIABLE LOCAL
    }
    if(*p && dato == 0 && esDup) ///SI EL DATO ES DUPLICADO Y QUIERO REALIZAR UNA ACCION, ENTRO A ESTE IF
    {
        ACCION(nue->info,(*p)->info);
    }
    ///HAGO EL ENLACE
    nue->sig = *p;
    *p = nue;
    return TODO_OK;
}
int InsertarAlFinal (tLista *p, void* d, unsigned tamInfo)
{
    tNodo* lista;
    while(*p) ///ME MUEVO HASTA QUE LLEGUE A NULL
    {
       ///lista = &(*lista)->sig; MODIFICO LA VARIABLE LOCAL
       ///MODIFICO LA LISTA!!! *lista = nuevo;
       ///lista = direccion del sig de lo que apunta lista. (*lista)->sig
        p = &(*p)->sig; ///APUNTO AL SIGUIENTE
    } ///COMO PUEDO RECORRER LA LISTA, DEBO LLEGAR HASTA EL FINAL
    ///RESERVO HEAP PARA EL NUEVO NODO
    lista = (tNodo*)malloc(sizeof(tNodo));
    if(lista == NULL) return SIN_MEM;
    lista->info = malloc(tamInfo);
    if(lista->info == NULL)
    {
        free(lista);
        return SIN_MEM;
    }
    ///METO LOS DATOS DEL NUEVO NODO
    memcpy(lista->info,d,tamInfo);
    lista->tamInfo = tamInfo;
    lista->sig = NULL; ///LE METO ESTO PORQUE ES EL ULTIMO
    *p = lista; ///ASIGNO EL NUEVO NODO. *p ESTA APUNTADO AL SIG DEL ANTERIOR

    return TODO_OK;
}
///FUNCIONES DE SACAR
int sacarPrimeroLista (tLista *p, void* d, unsigned tamInfo)
{
    if(*p == NULL) return LISTA_VACIA; ///Me fijo si la lista esta vacia
    tNodo* aux = *p; ///APUNTO AL PRIMER ELEMENTO
    *p = aux->sig; ///APUNTO AL SIGUIENTE
    ///COPIO LOS DATOS
    memcpy(d,aux->info,Minimo(tamInfo,aux->tamInfo)); ///AGARRO EL MINIMO
    free(aux->info);
    free(aux);
    return TODO_OK;
}
int sacarUltimoLista(tLista *p, void* d, unsigned tamInfo)
{
    if(*p == NULL) return LISTA_VACIA; ///Me fijo si la lista esta vacia
    ///ME VOY MOVIENDO HASTA LLEGAR AL ULTIMO
    while((*p)->sig)
    {
        p = &(*p)->sig;
    }
    ///APUNTO AL ULTIMO
    memcpy(d,(*p)->info,Minimo(tamInfo,(*p)->tamInfo));
    ///LIBERO EL NODO
    free((*p)->info);
    free(*p);
    *p = NULL; ///ACTUALIZO EL ULTIMO

    return TODO_OK;

}
///FUNCIONES DE VER
int verPrimero (const tLista *p, void* d, unsigned tamInfo)
{
     if(*p == NULL) return LISTA_VACIA; ///Me fijo si la lista esta vaciarLista
    ///COPIO LOS DATOS
    memcpy(d,(*p)->info,Minimo(tamInfo,(*p)->tamInfo)); ///AGARRO EL MINIMO
    return TODO_OK;
}
int verUltimo (const tLista *p, void* d, unsigned tamInfo)
{
    if(*p == NULL) return LISTA_VACIA; ///Me fijo si la lista esta vacia
    ///ME VOY MOVIENDO HASTA LLEGAR AL ULTIMO
    while((*p)->sig)
    {
        p = &(*p)->sig;
    }
    memcpy(d,(*p)->info,Minimo(tamInfo,(*p)->tamInfo));

    return TODO_OK;
}
///FUNCIONES DE ELIMINAR
int eliminarElementoSinDupNoOrdenados(tLista*p, void* d, unsigned tamInfo, tComp CMP)
{
    if(*p == NULL) return LISTA_VACIA;
    while(*p && CMP(d,(*p)->info) != 0)
    {
        p = &(*p)->sig;
    }
    if(*p == NULL) ///LLEGUE AL FINAL Y NO HAY NINGUN ELEMENTO
    {
        return NO_ENCONTRADO;
    }
    memcpy(d,(*p)->info,Minimo(tamInfo,(*p)->tamInfo)); ///NUNCA OLVIDAR ESTO
    tNodo* elim = *p; ///APUNTO AL NODO QUE QUIERO ELIMINAR
    *p = elim->sig;
    ///ELIMINO EL NODO
    free(elim->info);
    free(elim);
    return TODO_OK;
}
int eliminarElementoPosN (tLista*p, void* d, unsigned tamInfo, int pos)
{
    if(*p == NULL) return LISTA_VACIA;
    if(pos < 1) return ERROR;
    int cant = 1;
    while(*p && cant < pos)
    {
        p = &(*p)->sig;
        cant++;
    }
    if(*p == NULL) ///LLEGUE AL FINAL Y NO ENCONTRE EL ELEMENTO
    {
        return NO_ENCONTRADO;
    }
    memcpy(d,(*p)->info,Minimo(tamInfo,(*p)->tamInfo)); ///NUNCA OLVIDAR ESTO
    tNodo* elim = *p; ///APUNTO AL NODO QUE QUIERO ELIMINAR
    *p = elim->sig; ///HAGO EL ENLACE
    ///ELIMINO EL NODO
    free(elim->info);
    free(elim);
    return TODO_OK;
}

///ORDENAMIENTO
int OrdenarLista (tLista* p, tComp CMP)
{
    if(*p == NULL) return LISTA_VACIA;

    while((*p)->sig) ///ME MUEVO MIENTRAS HAYA SIGUIENTE, MIENTRAS SEA DISTINTO DE NULL
    {
        tNodo* menor = (tNodo*)buscarMenor(p,CMP); ///TENGO EL MENOR
        if(menor != *p) ///ME FIJO SI EL MENOR NO ES EL QUE  YA ESTOY APUNTANDO
        {
        ///HAGO UN INTERCAMBIO
        void* auxInfo = (*p)->info;
        (*p)->info = menor->info;
        menor->info = auxInfo;

        unsigned auxTam = (*p)->tamInfo;
        (*p)->tamInfo = menor->tamInfo;
        menor->tamInfo = auxTam;
        }
        p = &(*p)->sig; ///AVANZO CON LA VARIABLE LOCAL
    }
    return TODO_OK;

}
///ORDENAMIENTO

int OrdenarLista (tLista* p, tComp CMP)
{
    if(*p == NULL) return LISTA_VACIA;
    tNodo* nodoAmover;
    tNodo** menor;
    while((*p)->sig) ///ME MUEVO MIENTRAS HAYA SIGUIENTE, MIENTRAS SEA DISTINTO DE NULL
    {
        menor = buscarMenor(p,CMP); ///BUSCO EL MENOR
        if(*menor != *p)
        {
            nodoAmover = *menor; ///GUARDO LA DIRECCION DEL MENOR
            *menor = nodoAmover->sig;
            nodoAmover->sig = *p;
            *p = nodoAmover;
        }
        p = &(*p)->sig;
    }
    return TODO_OK;

}
tNodo** buscarMenor (tLista* p, tComp CMP)
{
    ///tNodo* min = (tNodo*)malloc(sizeof(tNodo));
    ///if(min == NULL) return NULL;
    ///min->info = (tNodo*)
    tNodo** min = p;
    while(*p)
    {
        if(CMP((*min)->info,(*p)->info) > 0)
            min = p;

         p = &(*p)->sig;
    }
    return min;
}
///MOSTRAR
void mostrar (tLista* p, imp IMP)
{
    while(*p)
    {
        IMP((*p)->info);
        p = &(*p)->sig;
    }
}

