#include "pila.h"

#define Minimo( X , Y )    ( (X) <= (Y)  ? (X) : (Y) )

void crearPila(tPila* p)
{
    *p = NULL;///INDICA QUE LA PILA ESTA VACIA
}
int pilaLlena (const tPila* p, unsigned tamDato) ///ESTA FUNCION ES POLEMICA, LA HACEMOS POR CONVENCION
{///EL PROBLEMA ES QUE, MUCHAS APLICACIONES ACCEDEN AL HEAP. NADA ME ASEGURA DE QUE LUEGO DE LLAMAR A LA FUNCON Y PREGUNTAR SI HABIA MEMORIA,
/// ALGUIEN YA HAYA USADO ESA MEMORIA. ESTO SUCEDE PORQUE EL HEAP SE PUEDE LLENAR EB CUALQUIER MOMENTO

    tNodo *aux = (tNodo *)malloc(sizeof(tNodo)); ///GUARDO ESPACIO PARA LA INFORMACION
    void *info = malloc(tamDato); ///GUARDO EL DATO DE CUANTO OCUPA ESA INFORMACION

    ///LO QUE SE HACE ES, PREGUNTAR A LA FUERZA SI HAY ESPACIO PARA GUARDAR LA INFORMACION
    ///SI DEVUELVE NULL EN ALGUNAS DE LAS DOS, QUIERE DECIR QUE NO HAY ESPACIO. EL HEAP ESTA AGOTADO
    free(aux);
    free(info);
    ///AMBOS PUNTEROS QUEDAN COMO PUNTEROS COLGANTES. SIGUEN APUNTANDO A LA DIRECCION ANTIGUA PERO ESTA PUEDE SER ASIGNADA A OTRO PROCESO
    return (aux == NULL || info == NULL)? PILA_LLENA : PILLA_NO_LLENA;
}
int pilaVacia (const tPila* p)
{
    return *p == NULL? PILA_VACIA : PILA_VACIA;
}
void vaciarPila (tPila* p)
{
    while(*p)
    {
        tNodo *aux = *p;///AUX APUNTA AL TOPE
        *p = aux->sig; ///EL PUNTERO DE PILA APUNTA AL NODO ANTERIOR AL TOPE
        free(aux->info);///BORRO LA INFORMACION DEL TOPE
        free(aux);///BORRO ESE NODO
    }
}
int ponerEnPila (tPila* p, const void* d, unsigned tamDato)
{
    tNodo *nue;
    ///AHORA RESERVO ESPACIO PARA LA ESTRUCTURA DEL NODO Y PARA GUARDAR EL CONTENIDO
    if((nue = (tNodo*)malloc(sizeof(tNodo))) == NULL ||
       (nue->info = malloc(tamDato)) == NULL)
    {
        free(nue);
        return SIN_MEMORIA;
    }
    memcpy(nue->info,d,tamDato); ///COPIO LA NUEVA INFORMACION
    nue->taminfo = tamDato; ///GUARDO EL TAMAÑO DEL DATO
    nue->sig = *p; ///EL NUEVO NODO APUNTA HACIA DONDE APUNTABA EL TOPE ANTERIOR DE LA PILA.
    *p = nue; ///EL TOPE DE LA PILA PASA A SER EL NODO QUE ACABO DE CREAR
    return TODO_OK;
}
int desapilar (tPila* p, void* d, unsigned tamDato)
{
    tNodo *elim = *p;///USO UN PUNTERO DISTINTO AL ORIGINAL. LA BASE DEL TDA
    if(*p == NULL) return PILA_VACIA;
    *p = elim->sig;///ACTUALIZO EL TOPE. EL NUEVO TOPE ESTARA EN EL NODO ANTERIOR DEL QUE ESTA AHORA
    memcpy(d,elim->info,Minimo(elim->taminfo,tamDato));///AGARRO EL MENOR
    free(elim->info);///BORRO LA INFORMACION DEL TOPE
    free(elim);///BORRO EL NODO DEL TOPE
    return TODO_OK;
}
int verTope (const tPila* p, void* d, unsigned tamDato)
{
    if(*p == NULL)
    {
        return PILA_VACIA;
    }
    memcpy(d,(*p)->info,Minimo((*p)->taminfo, tamDato)); ///AGARRO EL MENOR TAMAÑO
    return PILA_NO_VACIA;
}
