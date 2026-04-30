#ifndef PILA_H_
#define PILA_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
///DEBO HACER LO POSIBLE PARA QUE EL USUARIO NO ROMPA EL TDA.
#define TAM_PILA 340
#define PILA_LLENA 1
#define PILLA_NO_LLENA 0
#define PILA_VACIA 1
#define PILA_NO_VACIA 0
#define TODO_OK 0
#define SIN_MEMORIA -222



///DINAMICO

typedef struct snodo
{
    void      *info;
    unsigned  taminfo;
    struct snodo *sig; ///ES EL SIGUIENTE A SER PROCESADO
    ///Le pongo la 's' como convención. Esto porque estoy usando la palabra reservada struct
} tNodo; ///Si pongo la 't' significa que tNodo es un tipo de dato y no necesito usar la palabra reservada struct

typedef tNodo *tPila; ///EN MI MEMORIA DE PILA, CADA PILA APUNTA A UN NODO.
///tPila --> TNodo*
///CrearPila(&p1) ---> &tNodo* ---> Recibe ** --->  tPila*
///                                                 tNodo**

///Me da lo mismo ponerle o no el const a las variables de tamaño por ser una copia.
///PERO TENGO QUE FIJARME QUE LOS PUNTEROS TENGAN LOS CONST
void crearPila(tPila* p); ///ACONDICIONO ALGO QUE YA EXISTE. La realidad es que no crea algo. Entonces, no puede fallar. Le paso el puntero de la pila para que lo acondicione. Va sin const.
int pilaLlena (const tPila* p, unsigned tamDato); ///Lo paso por puntero porque ocupa menos espacio que si le mando una copia
int pilaVacia (const tPila* p); ///No necesito el tamaño
void vaciarPila (tPila* p); ///No puede fallar
int ponerEnPila (tPila* p, const void* d, unsigned tamDato); ///El cliente es un mono con navaja. Entonces, debo fijarme si la pila esta llena (no puedo llamar a la primitiva que hice por ser una primitiva).
int desapilar (tPila* p, void* d, unsigned tamDato);
int verTope (const tPila* p, void* d, unsigned tamDato);


#endif // PILA_H_
