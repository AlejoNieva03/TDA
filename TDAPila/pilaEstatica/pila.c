#include "pila.h"
#include <string.h>

#define Minimo (X,Y)    ( (X) <= (Y)  ? (X) : (Y) )

void crearPila(tPila* p)
{
    p->tope = TAM_PILA;
}
int pilaLlena (const tPila* p, unsigned tamDato)
{
    return p->tope > (tamDato + sizeof(unsigned)) ? PILA_NO_LLENA : PILA_LLENA; ///NO ES QUE ME QUEDE CON 0 BYTES EN EL VECTOR
    ///ES QUE EL DATO JUNTO A SU TAMAÑO NO ENTRAN EN EL VECTOR
    ///PARA SABER ESTO, CALCULO SI EL TAMAÑO (EN BYTES) MAS EL TAMAÑO DE UN UNSIGNED, EXCEDE LO QUE QUEDA EN LA PILA PARA PODER LLENAR.

}
int pilaVacia (const tPila* p)
{
    return p->tope == TAM_PILA? PILA_VACIA : PILA_NO_VACIA; ///p->tope NOS DICE CUANTOS ELEMENTOS PODEMOS METER EN LA PILA
    ///SI SU NUMERO ES IGUAL AL TAMAÑO DE LA PILA, SIGNIFICA QUE LA PILA ESTA VACIA
}
void vaciarPila (tPila* p)
{
    p->tope = TAM_PILA;
}
int ponerEnPila (tPila* p, const void* d, unsigned tamDato)
{
   if(p->tope < (tamDato + sizeof(unsigned))) return PILA_LLENA; ///PILA LLENA
   p->tope -= tamDato; ///LE RESTO AL TOPE EL TAMA;O EN BYTES DE LA INFORMACION

   memcpy(p->pila + p->tope,d,tamDato); ///LE SUMO A LA PILA EL TOME Y COPIO LOS DATOS DE LA INFORMACION EN LA PILA

   p->tope-= sizeof(unsigned); ///LE RESTO AL TOPE CUANTO VALE ESCRIBIR EL TAMAÑO DEL ELEMENTO
   memcpy(p->pila + p->tope,&tamDato,sizeof(unsigned)); ///COPIO EL TAMAÑO DEL ELEMENTO EN LA PILA

   return PILA_NO_LLENA; ///TODO JOYA
}
int verTope (const tPila* p, void* d, unsigned tamDato)
{
    if(p->tope == TAM_PILA) return PILA_VACIA; ///PILA VACIA
    unsigned tamInfo;
    memcpy(&tamInfo, p->pila + p->tope,sizeof(unsigned)); ///EL TAMAÑO DE LO QUE OCUPA EL DATO (EL UNSIGNED QUE SE GUARDO EN EL VECTOR)
    memcpy(d,p->pila+p->tope + sizeof(unsigned),tamInfo > tamDato? tamDato : tamInfo);///LE DEBO SUMAR EL TAMAÑO DE UN UNSIGNED
    ///DEBO RECUPERAR EL MINIMO ENTRE TAMDATO Y TAMINFO PARA NO SOBREESCRIBIR NI PASARLE BASURA. ESTO SUCEDE PORQUE:
    ///SI EL DATO QUE QUIERO RECUPERAR ES MAS GRANDE QUE EL RECIPIENTE, SE PUEDE CRASHEAR EL PROGRAMA
    ///SI EL DATO QUE QUIERO RECUPERAR ES MAS CHICO QUE EL RECIPIENTE, VOY A LEER BASURA
    return PILA_NO_VACIA;
}

int desapilar (tPila* p, void* d, unsigned tamDato) ///ES LO MISMO QUE VERTOPE PERO ACTUALIZANDO EL TOPE
{
    if(p->tope == TAM_PILA) return PILA_VACIA;
    unsigned tamInfo;
    memcpy(&tamInfo, p->pila + p->tope,sizeof(unsigned));
    p->tope += sizeof(unsigned); ///ACTUALIZO EL TOPE CON EL TAMAÑO DE UN UNSIGNED
    memcpy(d,p->pila+p->tope,tamInfo > tamDato? tamDato : tamInfo);
    p->tope +=tamInfo;
    ///ESTO ESTA BIEN PORQUE SI PONGO EL MINIMO, PIERDO LA REFERENCIA AL PROXIMO. SI QUEDO ALGO ENTRE EL MINIMO, VA AL TACHO DE BASURA

    return JOYA;
}
