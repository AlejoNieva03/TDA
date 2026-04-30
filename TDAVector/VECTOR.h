#ifndef VECTOR_H
#define VECTOR_H
#include<stdbool.h>
#include<stdio.h>
#define TAM_VEC 50

#define TODO_OK 0
#define VEC_LLENO 1
#define VEC_CAGAMOS 999
#define DUPLICADO 2
#define TODO_MAL 999
#define BUFFER


#define CAP_INI 10000
#define FACTOR_INCR 1.5
#define FACTOR_DECR 0.5
#define FACTOR_OCUP 0.25
#define BURBUJEO 1
#define SELECCION 2
#define INSECCION 3

///DINAMICO
typedef struct
{
    void* vec;
    int ce;
    int cap;
    size_t tamelem;
}
VectorDin;

///ITERADOR
typedef struct
{
    void* act;
    bool finIt;
    void* ult;
    VectorDin* vector;
}
VectorIterador;


typedef int (*CMP)(const void* e1, const void* e2);
typedef void (*Imprimir)(const void* e);
typedef void (*Accion)(void* elem, void* datos);


bool VectorDinCrear (VectorDin *v, size_t tipo);
int vectorCrearDeArchivo(VectorDin* v, const char* nomArch, size_t tamElem);
int _VectorDinRedimension(VectorDin*v);
int VectorDinInsertarAlfinal (VectorDin* v, void* elem, CMP cmp);
int VectorDinInsertarOrden(VectorDin *v, void* elem, CMP cmp);
void* VectorDinBuscar (VectorDin* v, void* elem,CMP cmp);
bool VectorDinEliminar (VectorDin* v,void* elem,CMP cmp);
void VectorDinDestruir (VectorDin *v);
void VectorDinMostrar (VectorDin* v, Imprimir imp);
void VectorDinVaciar (VectorDin* v);
int vectorGrabar (const VectorDin* v, const char* nomArch);
int vectorBuscar(const VectorDin* v, void* elem, CMP cmp);
void vectorRecorrer(VectorDin* vector, Accion accion, void* datos);

///BURBUJEO
void _ordenarBurbujeoMenaMay(VectorDin* v,CMP cmp);
void _ordenarBurbujeoMayaMen(VectorDin* v,CMP cmp);
///SELECCION
bool _ordenarSeleccionMenaMay(VectorDin* v, CMP cmp);
bool _ordenarSeleccionMayaMen (VectorDin* v, CMP cmp);
///INSERCCION
void _ordenarInserccionMenaMay (VectorDin* v, CMP cmp);
void _ordenarInserccionMayaMen (VectorDin* v, CMP cmp);
size_t MAX(size_t c, size_t e);

///Caballitos de batalla
void* Mayorgen(void* ini, void* fin,size_t tamElem,CMP cmp);
void* Menorgen(void* ini, void* fin,size_t tamElem, CMP cmp);
void _IntercambioGen(void* i, void* j,size_t tamElem);
void vectorOrdenarMenaMay (VectorDin* vec, int metodo,CMP cmp); ///NUEVO FUNCION CHAVALES
void vectorOrdenarMayaMen (VectorDin* vec, int metodo,CMP cmp);
int* Mayor(int* ini, int* fin);
int* Menor(int* ini, int* fin);
void Intercambio(int* i, int *j);

/// Iterador
void vectorIteradorCrear(VectorIterador* it, VectorDin* vector);
void* vectorIteradorPrimero (VectorIterador* it);
void* vectorIteradorActual(VectorIterador* it);
void* vectorIteradorSiguiente(VectorIterador* it);
bool vectorIteradorFin(VectorIterador* it);



///Estatico
//typedef struct
//{
//    int vec[TAM_VEC];
//    int ce;
//
//}
//VectorEst;
//bool VectorEstCrear (VectorEst *v);
//int VectorEstInsertarOrden(VectorEst *v, int elem);
//int* VectorEstBuscar (VectorEst* v, int elem);
//bool VectorEstEliminar (VectorEst* v,int elem);
//void VectorEstDestruir (VectorEst *v);
//void VectorEstMostrar (VectorEst* v);
//void VectorEstVaciar (VectorEst* v);
//bool VectorEstOrdenMenoraMayor(VectorEst* v);
//bool VectorEstOrdenMayoraMenor (VectorEst* v);
//int* VectorEstBuscar (VectorEst* v, int elem);



#endif // VECTOR_H
