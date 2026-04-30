#ifndef COLA_H_
#define COLA_H_

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

typedef struct
{
    tNodo* pri;
    tNodo* ult;
}tCola;


void crearCola (tCola* p);
int colaVacia (const tCola* p);
int colaLlena (const tCola* p, unsigned tamElem);
int ponerEnCola (tCola* p, const void* dato, unsigned tamElem);
int SacarDeCola (tCola* p, void* dato, unsigned tamElem);
void vaciarCola (tCola* p);
int verPrimero (const tCola *p, void* dato, unsigned tamElem);


#endif // COLA_H_
