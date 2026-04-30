#ifndef PILA_H_
#define PILA_H_
#define TAM_PILA 340
#include <stdio.h>
#include <stdlib.h>
///DEBO HACER LO POSIBLE PARA QUE EL USUARIO NO ROMPA EL TDA.
#define TAM_PILA 340
#define PILA_LLENA 1
#define PILA_NO_LLENA 0
#define PILA_VACIA 1
#define PILA_NO_VACIA 0
#define JOYA 0
#define MOSTRAR 0
#define NO_MOSTRAR 1

typedef struct
{
   char pila[TAM_PILA];
   unsigned tope;
}tPila;

///Me da lo mismo ponerle o no el const a las variables de tamaño por ser una copia.
void crearPila(tPila* p); ///ACONDICIONO ALGO QUE YA EXISTE. La realidad es que no crea algo. Entonces, no puede fallar. Le paso el puntero de la pila para que lo acondicione. Va sin const.
int pilaLlena (const tPila* p, unsigned tamDato); ///Lo paso por puntero porque ocupa menos espacio que si le mando una copia
int pilaVacia (const tPila* p); ///No necesito el tamaño
void vaciarPila (tPila* p); ///No puede fallar
int ponerEnPila (tPila* p, const void* d, unsigned tamDato);
///El cliente es un mono con navaja. Entonces, debo fijarme si la pila esta llena (no puedo llamar a la primitiva que hice por ser una primitiva).
int desapilar (tPila* p, void* d, unsigned tamDato);
int verTope (const tPila* p, void* d, unsigned tamDato);


#endif // PILA_H_
