#ifndef LISTA_H_
#define LISTA_H_

#define Minimo(x,y) ( (x) <= (y)? (x) : (y))

#define LISTA_VACIA 1
#define LISTA_NO_VACIA 0

///ERRORES
#define SIN_MEM -999
#define ERROR -888
#define NO_ENCONTRADO -777

#define LISTA_NO_LLENA 0

#define TODO_OK 0

#define REALIZAR_ACCION 1
#define NO_REALIZAR_ACCION 0
#include "../pilaEstatica/pila.h"


typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;

typedef int (*cmp) (const void*, const void*);
typedef cmp tComp;

typedef void (*accion) (void*, const void*);
typedef accion tAccion;
typedef void (*imp) (const void*);


typedef void (*Ing) (void* e);

void crearLista (tLista* p);
int listaVacia (const tLista* p);
int listaLlena (const tLista* p, unsigned tamElem);
void vaciarLista (tLista *p);
int verPrimero (const tLista *p, void* d, unsigned tamInfo);
int verUltimo (const tLista *p, void* d, unsigned tamInfo);
int InsertarAlFinal (tLista *p, void* d, unsigned tamInfo);
int InsertarPosicionN (tLista *p, void* d, unsigned tamInfo, int pos);
int InsertarAlComienzo (tLista *p, void* d, unsigned tamInfo);
int sacarPrimeroLista (tLista *p, void* d, unsigned tamInfo);
int sacarUltimoLista(tLista *p, void* d, unsigned tamInfo);
void mostrarLista (tLista* p, imp IMP);
///PARA QUE SEA GEMERICA, DEBO PASARLE PUNTEROS A FUNCIONAA
int InsertarEnOrdenSinDupSinAccion(tLista* p,const void*d, unsigned tamInfo, tComp CMP);
int InsertarEnOrdenDupSinAccion(tLista* p,const void*d, unsigned tamInfo, tComp CMP);

int eliminarElementoSinDupNoOrdenados(tLista*p, void* d, unsigned tamInfo, tComp CMP);
int eliminarElementoPosN (tLista*p, void* d, unsigned tamInfo, int pos);

int OrdenarLista (tLista* p, tComp CMP);
tNodo** buscarMenor (tLista* p, tComp CMP);

void _mostrarListaOrdenInversoRec (tLista* p, imp IMP);
int mostrarListaOrdenInverso(tLista* p, imp IMP);

#endif // LISTA_H_
