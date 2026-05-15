#include <stdio.h>
#include <stdlib.h>
#include "ListaDoblementeEnlazada.h"
typedef struct
{
    int codigo;
    int cantidad;
}tRegistro;


void mostrarListaIzqDer (const tLista* l, imp IMP);
void mostrarListaDerIzq (const tLista* l, imp IMP);
void impReg (const void* e1);
int cmpXCodigo (const void* e1, const void* e2);
void accXCant (void* e1, const void* e2);
int main()
{
    tLista lista;
    crearLista(&lista);
    tRegistro producto;

    producto.codigo = 101;
    producto.cantidad = 40;

    //insertarListaAlFinal(&lista,&producto,sizeof(tRegistro),cmpXCodigo);
    insertarListaAlInicio(&lista,&producto,sizeof(tRegistro));

    mostrarListaIzqDer(&lista,impReg);
    mostrarListaDerIzq(&lista,impReg);

        puts("");

    producto.codigo = 103;
    producto.cantidad = 50;

    insertarListaAlFinal(&lista,&producto,sizeof(tRegistro));

    mostrarListaIzqDer(&lista,impReg);
    mostrarListaDerIzq(&lista,impReg);;

        puts("");

    producto.codigo = 100;
    producto.cantidad = 30;

   insertarListaAlFinal(&lista,&producto,sizeof(tRegistro));

    mostrarListaIzqDer(&lista,impReg);
    mostrarListaDerIzq(&lista,impReg);

        puts("");

    producto.codigo = 102;
    producto.cantidad = 50;

    insertarListaAlInicio(&lista,&producto,sizeof(tRegistro));

    mostrarListaIzqDer(&lista,impReg);
    mostrarListaDerIzq(&lista,impReg);

        puts("");
          verActual(&lista,&producto,sizeof(tRegistro));

    puts("El elemento actual apuntado es: ");
    impReg(&producto);

        puts("");
//
//    producto.codigo = 102;
//
//    eliminarElementoLista(&lista,&producto,sizeof(tRegistro),cmpXCodigo);
//
//    mostrarListaIzqDer(&lista,impReg);
//    mostrarListaDerIzq(&lista,impReg);
//         puts("");
//
//    puts("El elemento eliminado es: ");
//    impReg(&producto);
//
//        puts("");
//
//    producto.codigo = 103;
//    eliminarElementoLista(&lista,&producto,sizeof(tRegistro),cmpXCodigo);
//
//    mostrarListaIzqDer(&lista,impReg);
//    mostrarListaDerIzq(&lista,impReg);
//         puts("");
//
//    puts("El elemento eliminado es: ");
//    impReg(&producto);
//         puts("");
ordenarLista(&lista,cmpXCodigo);
  mostrarListaIzqDer(&lista,impReg);
    mostrarListaDerIzq(&lista,impReg);
    puts("");



    vaciarLista(&lista);

    return 0;
}
int cmpXCodigo (const void* e1, const void* e2)
{
    tRegistro* i1 = (tRegistro*)e1;
    tRegistro* i2 = (tRegistro*)e2;
    return i1->codigo - i2->codigo;
}
void accXCant(void* e1, const void* e2)
{
    tRegistro* i1 = (tRegistro*)e1;
    tRegistro* i2 = (tRegistro*)e2;
    i1->cantidad += i2->cantidad;
}
void mostrarListaIzqDer (const tLista* l, imp IMP)
{
    puts("Mostrando lista de Izquierda a Derecha:");
    if(*l)
    {
      while((*l)->ant)
           l = & (*l)->ant;
      while(*l)
      {
          IMP((*l)->info);
           l = & (*l)->sig;
      }
    }
}
void mostrarListaDerIzq (const tLista* l, imp IMP)
{
    puts("Mostrando lista de Derecha a Izquierda:");
    if(*l)
    {
      while((*l)->sig)
           l = & (*l)->sig;
      while(*l)
      {
          IMP((*l)->info);
           l = & (*l)->ant;
      }
    }
}
void impReg (const void* e1)
{
    tRegistro* i1 = (tRegistro*)e1;
    printf("%-3d %d\n",i1->cantidad,i1->codigo);
}
