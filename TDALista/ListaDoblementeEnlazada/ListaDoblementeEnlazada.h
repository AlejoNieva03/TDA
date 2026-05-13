#ifndef LISTADOBLEMENTEENLAZADA_H_
#define LISTADOBLEMENTEENLAZADA_H_

#define LISTA_VACIA 1
#define LISTA_NO_VACIA 0

//ERRORES

#define ERROR -888
#define NO_ENCONTRADO -777

#define LISTA_NO_LLENA 0

#define TODO_OK 0
#define SIN_MEM -999
#define Minimo(x,y) ( (x) <= (y)? (x) : (y))

typedef struct sNodo
{
    void* info;
    unsigned tamInfo;
    struct sNodo* ant;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;

typedef int (*cmp)(const void*,const void*);
typedef void (*accion) (void*, const void*);
typedef void (*imp) (const void*);
typedef void (*Ing) (void* e);

void crearLista (tLista* pl);
int insertarListaOrdenadaConDuplicados (tLista* pl, void* d, unsigned tamElem, cmp CMP);
int insertarListaOrdenadaConAccion (tLista* pl, void* d, unsigned tamElem, cmp CMP, accion ACCION);
int eliminarLista (tLista* pl, void* d, unsigned tamElem, cmp CMP);
void destruirLista (tLista* pl);


#endif // LISTADOBLEMENTEENLAZADA_H_
