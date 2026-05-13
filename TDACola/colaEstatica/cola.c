#include "cola.h"
#include <string.h>
#define MINIMO(x,y) (((x) <= (y) )? (x) : (y) )
void crearCola (tCola* p)
{
    p->tamDis = TAM_COLA;
    p->ini = TAM_COLA - 70;
    p->ult = TAM_COLA - 70;
    ///INICIALIZO INI Y ULT CON ALGUNA POSICION VALIDA
    ///ESTO SIGNIFICA QUE, UN ELEMENTO PUEDE ESTAR FRAGMENTANDO
}
int colaLlena (const tCola* p,unsigned tamElem)
{
    return p->tamDis < (tamElem + sizeof(unsigned))? COLA_LLENA : COLA_NO_LLENA;
}
int colaVacia (const tCola* p)
{
    return p->tamDis == TAM_COLA? COLA_VACIA : COLA_NO_VACIA;
}
int ponerEnCola (tCola* p, const void* dato, unsigned tamElem)
{
    if(p->tamDis < (tamElem + sizeof(unsigned) )) return SIN_MEM;
    p->tamDis = p->tamDis - tamElem - sizeof(unsigned);
    unsigned ini,
             fin;
    ///    hago sizeof de un sizeof, esto me da cuanto ocupa un size_t en mi arquitectura
    if( (ini = MINIMO(sizeof(tamElem),TAM_COLA - p->ult)) != 0) ////si el tamaño del dato entra sin tener que partirlo   || si ini da 0 es porque el tamDato no entra de este lado de la cola
        memcpy(p->cola + p->ult, &tamElem, ini);
    if( (fin = sizeof(tamElem) - ini) != 0)///Me fijo si quedo fragmentado. Si quedo fragmentado, fin va a dar distinto de 0
        memcpy(p->cola, ((char*)&tamElem) + ini, fin);
    ///ACTUALIZO P->ULT
    ///SI FIN VALE 0, CUENTA COMO FALSO Y SIGNIFICA QUE EL DATO NO SE FRAGMENTO, p->ult va a valer p->ult + ini
    ///
    p->ult = fin? fin : p->ult + ini;
    if( (ini = MINIMO(tamElem,TAM_COLA - p->ult)) != 0)
         memcpy(p->cola + p->ult, dato, ini);
    if( (fin = tamElem - ini) != 0)///Me fijo si quedo fragmentado. Si quedo fragmentado, fin va a dar distinto de 0
        memcpy(p->cola, ((char*)dato) + ini, fin);
    ///ACTUALIZO P->ULT
    p->ult = fin? fin : p->ult + ini;

    return TODO_OK;
}
int SacarDeCola (tCola* p, void* dato, unsigned tamElem)
{
    if( p->tamDis == TAM_COLA) return COLA_VACIA; ///ME FIJO SI LA COLA ESTA VACIA
    unsigned tamInfo; ///El tamaño de la informacion
    unsigned ini,
             fin;
    if( (ini = MINIMO(sizeof(unsigned),TAM_COLA - p->ini)) != 0 )
        memcpy(&tamInfo,p->cola + p->ini, ini);
    if( (fin = sizeof(unsigned) - ini) != 0)
        memcpy( ((char*)&tamInfo) + ini, p->cola,fin);
    p->ini = fin? fin: p->ini + ini;

    ///ACTUALIZO EL TAMAÑO DISPONIBLE
     p->tamDis += tamInfo + sizeof(unsigned);
     tamInfo = MINIMO(tamInfo,tamElem); ///AGARRO EL MINIMO

    if( (ini = MINIMO(tamInfo,TAM_COLA - p->ini)) != 0)
        memcpy(dato,p->cola + p->ini,ini);
    if( (fin = tamInfo - ini) != 0)
        memcpy(((char*)dato) + ini,p->cola,fin);

    p->ini = fin? fin: p->ini + ini;
    ///ACTUALIZO El tamaño disponible

    return TODO_OK;
}
int verPrimero (const tCola *p, void* dato, unsigned tamElem)
{
    if( p->tamDis == TAM_COLA) return COLA_VACIA; ///ME FIJO SI LA COLA ESTA VACIA
    unsigned tamInfo; ///El tamaño de la informacion
    unsigned ini,
             fin;
    unsigned pos = p->ini;

    if( (ini = MINIMO(sizeof(unsigned),TAM_COLA - pos)) != 0 )
        memcpy(&tamInfo,p->cola + pos, ini);
    if( (fin = sizeof(unsigned) - ini) != 0)
        memcpy( ((char*)&tamInfo) + ini, p->cola,fin);

    pos = fin? fin: pos + ini;

     tamInfo = MINIMO(tamInfo,tamElem); ///AGARRO EL MINIMO

    if( (ini = MINIMO(tamInfo,TAM_COLA - pos)) != 0)
        memcpy(dato,p->cola + pos,ini);
    if( (fin = tamInfo - ini) != 0)
        memcpy(((char*)dato) + ini,p->cola,fin);

    return TODO_OK;
}
void vaciarCola (tCola* p)
{
    p->tamDis = TAM_COLA;
    p->ult = p->ini;
}
