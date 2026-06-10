#ifndef ARBOL_H_
#define ARBOL_H_

#include <stdio.h>
#include <stdlib.h>

#define PRE_ORDEN 0
#define IN_ORDEN 1
#define POS_ORDEN 2

#define TODO_OK 1
#define SIN_MEM -999
#define DUPLICADO 0
#define ERROR_ARCHIVO -888

#define ARBOL_VACIO -1


typedef struct sNodo
{
    void* info;
    unsigned tamElem;
    struct sNodo* Izq;
    struct sNodo* Der;
}tNodo;

typedef tNodo* tArbol;

typedef int(*CMP)(const void*,const void*);
typedef void (*IMP)(const void*);
typedef void (*ACC)(const void*);
typedef void(*carIndice) (const void*, void*);

void crearArbol (tArbol* pr);
int InsertarArbolBinario (tArbol* pr, void* dato, unsigned tamElem,CMP cmp);
int InsertarArbolBinarioIterativo (tArbol* pr, void* dato, unsigned tamElem,CMP cmp);
void recorrerArbol (tArbol* pr, int tipoDerecorrido, IMP imp);
void _preOrden (tArbol* pr, IMP imp);
void _InOrden (tArbol* pr, IMP imp);
void _posOrden (tArbol* pr, IMP imp);
void _posOrdenIterativo(tArbol* pr, IMP imp);


///EJERCICIOS
int contarTodosLosNodos (tArbol* pr);
void _contarTodosLosNodos (tArbol* pr, int* cont);

int contarTodosLosNodosHojas (tArbol* pr);
void _contarTodosLosNodosHojas (tArbol* pr, int* cont);

int contarTodosLosNodosConHijos(tArbol *pr);
void _contarTodosLosNodosConHijos (tArbol* pr, int* cont);

int contarTodosLosNodosConHijosPorIzq(tArbol *pr);
void _contarTodosLosNodosConHijosPorIzq (tArbol* pr, int* cont);

int contarTodosLosNodosConHijosSoloPorIzq(tArbol *pr);

int contarTodosLosNodosConHijosPorDer (tArbol* pr);
void _contarTodosLosNodosConHijosPorDer (tArbol* pr, int* cont);


int contarTodosLosNodosConHijosSoloPorDer(tArbol *pr);

int contarAltura (tArbol* pr);

int contarNivel (tArbol* pr);

void buscarDatoPorNivel (tArbol* pr, int nivel, ACC accion);
int buscarEnArbol(const tArbol* pr,void*dato, unsigned tamElem,CMP cmp);
void _buscarDatoPorNivel (tArbol* pr, int nivel, int Actnivel, ACC accion);


void destruirArbol (tArbol* pr); ///DEBE SER EN POS ORDEN
void podarHojas (tArbol* pr); ///DEBE SER EN PRE ORDEN

int eliminarNodo (tArbol* pr,void* clave, unsigned tamElem, CMP cmp);
tArbol* _buscarNodoEnArbol(tArbol* pr,void* clave,CMP cmp);
tNodo** _buscarMayorNodo (tArbol* pr);
tNodo** _buscarMenorNodo (tArbol* pr);


///EJERCICIOS CON ARCHIVOS

#define TAM_NOMBRE 50
#define CLAVE_ENCONTRADA 1
#define CLAVE_NO_ENCONTRADA 0

typedef struct
{
    int dni;
    char nyA [TAM_NOMBRE + 1];
    char sexo;
}tRegistro;

typedef struct
{
   unsigned long dni;
 } tClave;
typedef struct
{
  tClave clave;
   unsigned indiceRegistro;
 } tIndice;

int cargarArchivoDesordenadoArbol(tArbol* pr, char* nombrArch,unsigned tamElem, CMP cmp, carIndice cargar);
int cargarArbolArchivoOrdenado (tArbol* pr, char* nuevoArch, char* archivoViejo, unsigned tamElem);
void _cargarArbolArchivoOrdenado (tArbol* pr, FILE* nuevo, FILE* viejo, tIndice* indice, void* dato,unsigned tamElem);
int balancearArbol (char* nombrArch, tArbol* pr);
void _balancearArbol (FILE* Arch, tArbol* pr, int ini, int fin);

int cmpIndice (const void* e1, const void* e2);

int buscarEnArchivoConIndice(FILE *fp, const tArbol *pa, tRegistro *reg);

#endif // ARBOL_H_
