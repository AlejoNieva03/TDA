#ifndef PILA_H_
#define PILA_H_

#include "../comun.h"

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tPila;


void crearPila(tPila* p); ///ACONDICIONO ALGO QUE YA EXISTE. La realidad es que no crea algo. Entonces, no puede fallar. Le paso el puntero de la pila para que lo acondicione. Va sin const.
int pilaLlena (const tPila* p, unsigned tamDato); ///Lo paso por puntero porque ocupa menos espacio que si le mando una copia
int pilaVacia (const tPila* p); ///No necesito el tamaño
void vaciarPila (tPila* p); ///No puede fallar
int ponerEnPila (tPila* p, const void* d, unsigned tamDato); ///El cliente es un mono con navaja. Entonces, debo fijarme si la pila esta llena (no puedo llamar a la primitiva que hice por ser una primitiva).
int desapilar (tPila* p, void* d, unsigned tamDato);
int verTope (const tPila* p, void* d, unsigned tamDato);

#endif // PILA_H_
