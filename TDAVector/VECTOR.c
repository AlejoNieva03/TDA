#include "VECTOR.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

///DINAMICO
bool VectorDinCrear (VectorDin *v, size_t tipo)
{
    v->ce = 0;
    v->vec = malloc(CAP_INI * tipo);

    if(v->vec == NULL)
    {
        v->cap = 0;
        return false;
    }
    v->tamelem = tipo; ///Clave para que sea generico
    v->cap = CAP_INI;

    return true;
}
int _VectorDinRedimension(VectorDin*v)
{
    size_t nuevaCap = v->cap * FACTOR_INCR;
    void* vectorNue = realloc(v->vec,nuevaCap * v->tamelem); ///USO REALLOC EN OTRA VARIABLE
    if(vectorNue == NULL) ///NO USE EL PUNTERO ORIGINAL PORQUE SI FALLA Y DEVUELVE NULL, PIERDO EL BLOQUE ORIGINAL
                return VEC_CAGAMOS;

    printf("Aumento de %i a %i\n",v->cap,nuevaCap); ///INFORMO EL CAMBIO
    v->cap = nuevaCap; ///CAMBIO LA CAPACIDAD
    v->vec = vectorNue; ///Apunto al nuevo vector
    return TODO_OK;
}
int VectorDinInsertarOrden(VectorDin *v,void* elem, CMP cmp)
{
     if(v->ce == v->cap) ///Me fijo que no me haya pasado del maximo, si me pase, lo debo reallocar
        {
           if(_VectorDinRedimension(v) != 0)
                return VEC_CAGAMOS;
        }

    void* i = v->vec; ///No me muevo del vector original, asi que asigno su direccion a un puntero para recorrerlo
    void* ult = v->vec + (v->ce - 1) * v->tamelem; ///Me paro al final del vector. Uso el tamaño del elemento para hacerlo generico

    while(i <= ult && cmp(elem,i) > 0) ///Me muevo mientras no llegue a la ultima posición con un elemento del vector y
    {                            ///mientras el elemento apuntado actual sea menor al elemento a insertar
        i+= v->tamelem; ///Me muevo
    }

    if(i <= ult && cmp(elem,i) == 0)
    {
        return DUPLICADO;
    }
    void* j = ult; ///Asigno un variable a la ultima posición
    for(; j >= i; j -= v->tamelem) ///Me muevo mientras (para atras)la dirección de j sea igual o mayor a la dirección de i
    {
        memcpy(j + v->tamelem, j,v->tamelem); ///Le asigno el valor de actual de j a la siguiente posición
        ///Como es genereico, la siguiente posición de J se encuentra a v->tamelem bytes de la actual
    }
    memcpy(i,elem,v->tamelem);///Asigno el valor que quize ingresar a su correspondiente posición
    v->ce++; ///Aumento la cantidad de elementos
    return TODO_OK;
}
int VectorDinInsertarAlfinal (VectorDin* v, void* elem, CMP cmp)
{
     if(v->ce == v->cap) ///Me fijo que no me haya pasado del maximo, si me pase, lo debo reallocar
        {
            if(_VectorDinRedimension(v) != 0)
                return VEC_CAGAMOS;
        }
    void* i = v->vec;
    void* ult = v->vec + (v->ce-1) * v->tamelem; ///Apunto al ultimo elemento del vector
    while(i <= ult && cmp(i,elem) !=0)
        i += v->tamelem;

    if(i <= ult && cmp(i,elem) == 0) ///El elemento ya existe en el array
       return DUPLICADO;

    memcpy(i,elem,v->tamelem);///Si llegue aca es que esta todo okey asi que asigno el elemento a la posicion final del vector
    v->ce++; ///Aumento la cantidad de elementos
    return TODO_OK;
}
void vectorOrdenarMenaMay (VectorDin* vec, int metodo, CMP cmp)
{
    switch(metodo)
    {
    case BURBUJEO:
    _ordenarBurbujeoMenaMay(vec,cmp);
    break;
    case SELECCION:
    _ordenarSeleccionMenaMay(vec,cmp);
    break;
    case INSECCION:
    _ordenarInserccionMenaMay(vec,cmp);

    break;
    }
}
void vectorOrdenarMayaMen(VectorDin* vec, int metodo, CMP cmp)
{
    switch(metodo)
    {
    case BURBUJEO:
    _ordenarBurbujeoMayaMen(vec,cmp);
    break;
    case SELECCION:
    _ordenarSeleccionMayaMen(vec,cmp);
    break;
    case INSECCION:
    _ordenarInserccionMayaMen(vec,cmp);

    break;
    }
}
bool VectorDinEliminar (VectorDin* v,void* elem,CMP cmp)
 {
    if(v->ce == 0)
        return false;

    void* posElim = VectorDinBuscar(v,elem,cmp);

    if(!posElim) ///Si me devolvio el nulo es porque no esta el elemento en el vector
        return false;
    void* ult = v->vec + (v->ce - 1) * v->tamelem;
    for(void *i = posElim; i <= ult; i += v->tamelem)
        memcpy(i, i + v->tamelem,v->tamelem); ///Guardo en la siguiente posicion

    v->ce--; ///Le resto

    ///Puedo fijarme cuanta capacidad esta ocupada, si esa capacidad es minima, la reduzco
    if(v->cap > CAP_INI && (float)v->ce / v->cap <= FACTOR_OCUP)
    {
        size_t nuevaCap = MAX(v->cap * FACTOR_DECR, CAP_INI); ///Nueva capacidad, me fijo para no reducir menos que la capacidad inicial
        v->vec = realloc(v->vec, nuevaCap * v->tamelem); ///LO REALLOCO DE UNA PORQUE COMO ACHICO EL VECTOR, NO DEBERIA FALLAR
        printf("Decremento de %i a %i\n",v->cap,nuevaCap); ///INFORMO EL CAMBIO
        v->cap = nuevaCap;
    }
    return true;
}
size_t MAX(size_t c, size_t e)
{
   return c > e ? c : e;
}
//int buscarArch(VectorDin* v,void* elem, CMP cmp)
//{
//    void* i =
//}
void* VectorDinBuscar (VectorDin* v,void* elem,CMP cmp)
{
    void *i = v->vec;
    void *ult = v->vec + (v->ce - 1) * v->tamelem;
    while( i <= ult && cmp(elem,i) != 0)
    {
        i += v->tamelem;
    }
    if(i <= ult && cmp(elem,i) == 0) ///El elemento esa en el vector, asi que devuelvo la direccion de donde esta
        return i;

    return NULL; ///Si llegue aca, el elemento no esta en el vector
}
bool _ordenarSeleccionMenaMay(VectorDin* v, CMP cmp)
{
    if(v->ce == 0)
        return false;

    void* i = v->vec;
    void* m = i;
    void* ult = v->vec + (v->ce - 1) * v->tamelem;
    for( ;i <= ult - v->tamelem; i += v->tamelem)
    {
        m = Menorgen(i,ult,v->tamelem,cmp);
        _IntercambioGen(i,m,v->tamelem);
    }
    return true;
}

bool _ordenarSeleccionMayaMen(VectorDin* v, CMP cmp)
{
    if(v->ce == 0)
        return false;

    void* i = v->vec;
    void* m = i;
    void* ult = v->vec + (v->ce - 1) * v->tamelem;
    for( ;i <= ult - v->tamelem; i += v->tamelem)
    {
        m = Mayorgen(i,ult,v->tamelem,cmp);
        _IntercambioGen(i,m,v->tamelem);

    }
    return true;
}
void _ordenarBurbujeoMenaMay(VectorDin* v,CMP cmp)
{
    void* ult = v->vec + (v->ce-1) * v->tamelem;
    ///El for externo me limita la cantidad de vueltas
    for(void* i = v->vec, *limJ = ult - v->tamelem; i < ult; i += v->tamelem,limJ -= v->tamelem)
    {
        for(void* j = v->vec; j <= limJ; j += v->tamelem)
        {
            if(cmp(j,j + v->tamelem) > 0) ///Me fijo si la posicion actual es mayor a la posicion siguiente
            {
                _IntercambioGen(j,j + v->tamelem,v->tamelem);
            }
        }
    }
}
void _ordenarBurbujeoMayaMen(VectorDin* v,CMP cmp)
{
    void* ult = v->vec + (v->ce-1) * v->tamelem;
    for(void* i = v->vec,*limJ = ult - v->tamelem; i < ult; i += v->tamelem,limJ -= v->tamelem)
    {
        for(void* j = v->vec; j <= limJ; j += v->tamelem)
        {
            if(cmp(j,j + v->tamelem) < 0)
            {
                _IntercambioGen(j,j + v->tamelem,v->tamelem);
            }
        }
    }
}
void _ordenarInserccionMenaMay (VectorDin* v, CMP cmp)
{
    void* ult = v->vec + (v->ce-1) * v->tamelem;
    void* j;
    void* elemAIns = malloc(v->tamelem);
    for(void* i = v->vec + v->tamelem; i <= ult; i += v->tamelem)
    {
        j = i - v->tamelem; ///Apunto a una posicion antes de i
        memcpy(elemAIns,i,v->tamelem);
        while(j >= v->vec && cmp(elemAIns,j) < 0) ///Me muevo mientras el elemento a insertar sea menor al valor de j
        {                                        ///siempre chequeo estar apuntando a una dirección valida
            memcpy(j + v->tamelem,j,v->tamelem);
            j -=v->tamelem; ///
        }
        memcpy(j+v->tamelem,elemAIns,v->tamelem);///Inserto el elemento
    }
    free(elemAIns);

}
void _ordenarInserccionMayaMen (VectorDin* v, CMP cmp)
{
    void* ult = v->vec + (v->ce-1) * v->tamelem;
    void* j;
    void* elemAIns = malloc(v->tamelem);
    for(void* i = v->vec + v->tamelem; i <= ult; i += v->tamelem)
    {
        j = i - v->tamelem; ///Apunto a una posicion antes de i
        memcpy(elemAIns,i,v->tamelem);
        while(j >= v->vec && cmp(elemAIns,j) > 0) ///Me muevo mientras el elemento a insertar sea mayor al valor de j
        {                                         ///siempre chequeo estar apuntando a una dirección valida
            memcpy(j + v->tamelem,j,v->tamelem);
            j -=v->tamelem;
        }
        memcpy(j+v->tamelem,elemAIns,v->tamelem);///Inserto el elemento
    }
    free(elemAIns);
}
void VectorDinMostrar (VectorDin* v, Imprimir imp)
{
    void *ult = v->vec + (v->ce-1) * v->tamelem;///Me paro al final
    for(void* i = v->vec ; i <= ult; i += v->tamelem)
    {
         imp(i);
         putchar(' ');
    }
    putchar('\n');

}
void* Mayorgen(void* ini, void* fin, size_t tamElem, CMP cmp)
{
    void* i = ini; ///Asi no me muevo
    void* m = i; ///Asumo que el mayor es el primero
    for( ; i <= fin; i += tamElem)
    {
        if(cmp(i,m) > 0) ///Me fijo cual es el mayor
        {
            m = i; ///Guardo la dirección del memoria del mayor en el puntero m
        }
    }
    return m; ///Regreso el mayor
}
void* Menorgen(void* ini, void* fin,size_t tamElem, CMP cmp)
{
    void* i = ini; ///Asi no me muevo
    void* m = i; ///Asumo que el menor es el primero
    for( ; i <= fin; i += tamElem )
    {
        if(cmp(m,i) > 0) ///Me fijo cual es el menor
        {
            m = i; ///Guardo la dirección del memoria del menor en el puntero m
        }
    }
    return m; ///Regreso el mayor
}
void _IntercambioGen(void* i, void* j,size_t tamElem)
{
    void* aux = malloc(tamElem); ///MI AUXILIAR
    memcpy(aux,i,tamElem); ///Guardo el valor de i en el auxiliar
    memcpy(i, j, tamElem); ///Asigno el valor de j a i
    memcpy(j,aux,tamElem); ///Asigno el valor de i a j
    free(aux);
}
void VectorDinVaciar (VectorDin* v) ///EL VECTOR VUELVE A SU ESTADO BASE
{
    v->ce = 0;
    v->cap = CAP_INI;
    v->vec = realloc(v->vec, CAP_INI * sizeof(int));
}

void VectorDinDestruir (VectorDin *v)
{
 free(v->vec); ///LIBERO LA MEMORIA
 v->vec = NULL; ///PARA QUE EL USUARIO NO LO PUEDA VOLVER A USAR
 ///SI DEJO LA DIRECCION QUE ESTABA ANTES, ESTA PODRIA ESTAR OCUPADA. AL PONERLE NULL HACE QUE NO PUEDA SER USADA Y TERMINA EL PROGRAMA
v->ce = 0;
v->cap = 0;
}
int vectorCrearDeArchivo(VectorDin* v, const char* nomArch, size_t tamElem)
{
    FILE* arch = fopen(nomArch,"rb"); ///Abro el archivo en modo lectura
    if(arch == NULL)///Me fijo si abrio bien
    {
        return TODO_MAL;
    }
    ///Debo saber cuantos registros tengo (primero veo cuantos bytes tengo)
    fseek(arch,0L,SEEK_END);///me paro al final
    size_t bytesArch = ftell(arch);///Se cuantos bytes tengo
    size_t cantRegistros = bytesArch / tamElem; ///La cantidad de registros son todos los bytes divido el tamaño de cada registro

    v->vec = malloc(bytesArch);///Creo un vector con la cantidad de bytes conseguida

    if(!v->vec)
    {
        v->cap = 0;
        v->tamelem = 0;
        return VEC_CAGAMOS;
    }
    fread(v->vec,tamElem,cantRegistros,arch); ///LEO TODO EL CONTENIDO, TENGO LA MEMORIA NECESARIA PARA CREAR EL ARCHIVO INDICE
    ///Guardo todo
    v->cap = cantRegistros;
    v->ce = 0;

    fclose(arch); ///CIERRO EL ARCHIVO

    return TODO_OK;
}
int vectorGrabar (const VectorDin* v, const char* nomArch)
{
    FILE* arch = fopen(nomArch,"wb"); ///Abro el archivo en modo escritura
    if(arch == NULL)///Me fijo si abrio bien
    {
        return TODO_MAL;
    }

    fwrite(v->vec, v->tamelem,v->ce,arch); ///Como ya tengo todos los datos, queda asi
    fclose(arch);
    return TODO_OK;
}
int vectorBuscar(const VectorDin* v, void* elem, CMP cmp)
{
    void* i = v->vec;
    ///size_t salto =
    void* ult = v->vec + (v->ce - 1) * v->tamelem;

    while(i <= ult && cmp(elem ,i) > 0)
    {
        i += v->tamelem;
    }

    if(i <= ult && cmp(elem, i) == 0)
    {
        memcpy(elem, i, v->tamelem);
        return (i - v->vec) / v->tamelem;
    }

    return -1;
}
void vectorRecorrer(VectorDin* vector, Accion accion, void* datos)
{
    void* ult = vector->vec + (vector->ce - 1) * vector->tamelem;
    for(void* i = vector->vec; i <= ult; i += vector->tamelem)
    {
        accion(i, datos);
    }
}
void vectorIteradorCrear(VectorIterador* it, VectorDin* vector)
{
  it->act = vector->vec;
  it->finIt = false;
  it->vector = vector;

}
void* vectorIteradorPrimero (VectorIterador* it)
{
  if(it->vector->ce == 0)
  {
    it->finIt = true;
    return NULL;
  }
  it->ult = it->vector->vec + (it->vector->ce - 1) * it->vector->tamelem; ///Calculo el ultimo
  it->act = it->vector->vec; ///Calculo el primero
  return it->act;
}
void* vectorIteradorSiguiente(VectorIterador* it)
{
    if(it->act == it->ult)
    {
      it->finIt = true;
      return NULL;
    }
      it->act += it->vector->tamelem; ///Me muevo al siguiente
    return it->act;
}
bool vectorIteradorFin(VectorIterador* it)
{
  return it->finIt;
}

void* vectorIteradorActual(VectorIterador* it)
{
    return it->act;
}
///ESTATICO
//bool VectorEstCrear (VectorEst *v)
//{
//    v->ce = 0;
//    return true;
//}
//int VectorEstInsertarOrden (VectorEst *v, int elem)
//{
//    if(v->ce == TAM_VEC) ///Me fijo que no me haya pasado del maximo
//        return VEC_LLENO;
//
//    int* i = v->vec; ///No me muevo del vector original, asi que asigno su direccion a un puntero para recorrerlo
//    int* ult = v->vec + v->ce - 1; ///Me paro al final del vector
//    ///Lo puedo hacer asi de simple porque el compilador sabe que es un vector de entero, sabe cuanto aumentarle para moverse de posición
//    while(i <= ult && *i < elem) ///Me muevo mientras no llegue a la ultima posición con un elemento del vector y
//    {                            ///mientras el elemento apuntado actual sea menor al elemento a insertar
//        i++;
//    }
//
//     if(i <= ult && elem == *i)
//       {
//        return DUPLICADO;
//       }
//    int* j = ult; ///Asigno un variable a la ultima posición
//    for(; j >= i; j--) ///Me muevo mientras (para atras)la dirección de j sea igual o mayor a la dirección de i
//    {
//        *(j+1) = *j; ///Le asigno el valor de actual de j a la siguiente posición
//    }
//    *i = elem; ///Asigno el valor que quize ingresar a su correspondiente posición
//    v->ce++; ///Aumento la cantidad de elementos
//    return true;
//}
//bool VectorEstEliminar (VectorEst* v,int elem)
//{
//    if(v->ce == 0)
//        return false;
//
//    int* posElim = VectorBuscar(v,elem);
//
//    if(!posElim) ///Si me devolvio el nulo es porque no esta el elemento en el vector
//        return false;
//    int* ult = v->vec + v->ce - 1;
//    for(int *i = posElim; i <= ult; i++)
//        *i = *(i+1); ///Guardo en la siguiente posicion
//
//    v->ce--; ///Le resto
//    return true;
//
//}
//int* VectorEstBuscar (VectorEst* v, int elem)
//{
//    int *i = v->vec;
//    int *ult = v->vec + v->ce - 1;
//    while( i <= ult && *i != elem)
//    {
//        i++;
//    }
//    if(i <= ult && *i == elem) ///El elemento esa en el vector, asi que devuelvo la direccion de donde esta
//        return i;
//
//    return NULL; ///Si llegue aca, el elemento no esta en el vector
//}
//
//bool VectorEstOrdenMenoraMayor(VectorEst* v)
//{
//    if(v->ce == 0)
//        return false;
//
//    int* i = v->vec;
//    int* m = i;
//    int* ult = v->vec + v->ce - 1;
//    for( ;i <= ult - 1;i++)
//    {
//        m = Menor(i,ult);
//        Intercambio(i,m);
//
//    }
//    return true;
//}
//bool VectorEstOrdenMayoraMenor (VectorEst* v)
//{
//    if(v->ce == 0)
//        return false;
//
//    int* i = v->vec;
//    int* m = i;
//    int* ult = v->vec + v->ce - 1;
//    for( ;i <= ult - 1;i++)
//    {
//        m = Mayor(i,ult);
//        Intercambio(i,m);
//
//    }
//    return true;
//}
int* Mayor(int* ini, int* fin)
{
    int* i = ini; ///Asi no me muevo
    int* m = i; ///Asumo que el mayor es el primero
    for( ; i <= fin; i++)
    {
        if(*m < *i) ///Me fijo cual es el mayor
        {
            m = i; ///Guardo la dirección del memoria del mayor en el puntero m
        }
    }
    return m; ///Regreso el mayor

}
int* Menor(int* ini, int* fin)
{
    int* i = ini; ///Asi no me muevo
    int* m = i; ///Asumo que el menor es el primero
    for( ; i <= fin; i++)
    {
        if(*m > *i) ///Me fijo cual es el menor
        {
            m = i; ///Guardo la dirección del memoria del menor en el puntero m
        }
    }
    return m; ///Regreso el mayor

}
void Intercambio(int* i, int *j)
{
    int aux = *i;
    *i = *j;
    *j = aux;
}
//void VectorMostrar (VectorEst* v)
//{
//    int *i = v->vec;
//    int *ult = v->vec + v->ce - 1;///Me paro al final
//    for( ;i <= ult; i++)
//        printf("%02d ",*i);
//    putchar('\n');
//}
//void VectorEstDestruir (VectorEst *v)
//{
//    v->ce = 0;
//}
