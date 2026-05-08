#ifndef COLACIRCULAR_H
#define COLACIRCULAR_H

#define COLA_LLENA 1
#define COLA_NO_LLENA 0
#define SIN_MEM -999


#define COLA_VACIA 1
#define COLA_NO_VACIA 0


#define TODO_OK 0

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tCola;

void crearCola (tCola* c);
int colaLlena (const tCola *c, unsigned tamInfo);
int ponerCola (tCola*c, void* d, unsigned tamInfo);
int sacarCola (tCola*c, void* d, unsigned tamInfo);
int colaVacia (const tCola* c);
int verTope (const tCola* c, void* d, unsigned tamInfo);
void vaciarCola (tCola* c);

#endif // COLACIRCULAR_H
