#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
#define TAM_MAX_NOMBRE_PRODUCTO 50

typedef struct
{
    int codigo;
    char Nombre [TAM_MAX_NOMBRE_PRODUCTO + 1];
}tProducto;

int cmpProductos (const void* e1, const void* e2);
void impProductos (const void* e);


int main()
{
    tProducto producto;
    tLista lista;
    int ret;
    crearLista(&lista);
    producto.codigo = 104;
    strcpy(producto.Nombre,"PlayStation 4");
    ret = InsertarEnOrdenSinDupSinAccion(&lista,&producto,sizeof(tProducto),cmpProductos);
    if(ret == TODO_OK)    mostrarLista(&lista,impProductos);
    if(ret == SIN_MEM) puts("\nNo hay espacio en la memoria\n");
    if(ret == DUPLICADO) puts("\nNo se admiten elementos duplicados\n");
    puts("");

    producto.codigo = 105;
    strcpy(producto.Nombre,"PlayStation 5");
    ret = InsertarEnOrdenSinDupSinAccion(&lista,&producto,sizeof(tProducto),cmpProductos);
    if(ret == TODO_OK)    mostrarLista(&lista,impProductos);
    if(ret == SIN_MEM) puts("\nNo hay espacio en la memoria\n");
    if(ret == DUPLICADO) puts("\nNo se admiten elementos duplicados\n");
    puts("");


    producto.codigo = 102;
    strcpy(producto.Nombre,"PlayStation 2");
    ret = InsertarEnOrdenSinDupSinAccion(&lista,&producto,sizeof(tProducto),cmpProductos);
    if(ret == TODO_OK)    mostrarLista(&lista,impProductos);
    if(ret == SIN_MEM) puts("\nNo hay espacio en la memoria\n");
    if(ret == DUPLICADO) puts("\nNo se admiten elementos duplicados\n");
    puts("");

    producto.codigo = 103;
    strcpy(producto.Nombre,"PlayStation 3");
    ret = InsertarEnOrdenSinDupSinAccion(&lista,&producto,sizeof(tProducto),cmpProductos);
    if(ret == TODO_OK)    mostrarLista(&lista,impProductos);
    if(ret == SIN_MEM) puts("\nNo hay espacio en la memoria\n");
    if(ret == DUPLICADO) puts("\nNo se admiten elementos duplicados\n");


    puts("");

    producto.codigo = 101;
    strcpy(producto.Nombre,"PlayStation 1");
    ret = InsertarEnOrdenSinDupSinAccion(&lista,&producto,sizeof(tProducto),cmpProductos);
    if(ret == TODO_OK)    mostrarLista(&lista,impProductos);
    if(ret == SIN_MEM) puts("\nNo hay espacio en la memoria\n");
    if(ret == DUPLICADO) puts("\nNo se admiten elementos duplicados\n");
    puts("");


    producto.codigo = 102;
    strcpy(producto.Nombre,"PlayStation 2");
    ret = InsertarEnOrdenSinDupSinAccion(&lista,&producto,sizeof(tProducto),cmpProductos);
    if(ret == TODO_OK)    mostrarLista(&lista,impProductos);
    if(ret == SIN_MEM) puts("\nNo hay espacio en la memoria\n");
    if(ret == DUPLICADO) puts("\nNo se admiten elementos duplicados\n");
    puts("");


    puts("LISTA ORDENADA:");

    OrdenarLista(&lista,cmpProductos);

    puts("");

    mostrarLista(&lista,impProductos);
    putchar('\n');
    putchar('\n');
    puts("MOSTRANDO LA LISTA EN ORDEN INVERSO:");
    ///mostrarListaOrdenInverso(&lista,impProductos);
    mostrarListaOrdenInverso(&lista,impProductos);
    putchar('\n');
    mostrarLista(&lista,impProductos);


    vaciarLista(&lista);

    return 0;
}
int cmpProductos (const void* e1, const void* e2)
{
    tProducto* i1 = (tProducto*)e1;
    tProducto* i2 = (tProducto*)e2;

    return i1->codigo - i2->codigo;
}

void impProductos (const void* e)
{
     tProducto* i = (tProducto*)e;
     printf("%-3d  %*s\n",i->codigo,TAM_MAX_NOMBRE_PRODUCTO,i->Nombre);
}
