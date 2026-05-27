#include "Arbol.h"
int cmpInt (const void* e1,const void* e2);
void impInt (const void* e);

int main()
{
    tArbol arbol;
    int num = 5;
    crearArbol(&arbol);
    InsertarArbolBinarioIterativo(&arbol,&num,sizeof(num),cmpInt);
    recorrerArbol(&arbol,POS_ORDEN,impInt);
    puts("");
    num = 3;
    InsertarArbolBinarioIterativo(&arbol,&num,sizeof(num),cmpInt);
    recorrerArbol(&arbol,POS_ORDEN,impInt);
    puts("");
    num = 6;
    InsertarArbolBinarioIterativo(&arbol,&num,sizeof(num),cmpInt);
    recorrerArbol(&arbol,POS_ORDEN,impInt);
    puts("");
    printf("La cantidad de nodos es %d\n",contarTodosLosNodos(&arbol));
    printf("La cantidad de nodos hojas es %d\n",contarTodosLosNodosHojas(&arbol));
    return 0;
}

int cmpInt (const void* e1,const void* e2)
{
    int* i1 = (int*)e1;
    int* i2 = (int*)e2;
    return *i1 - *i2;
}
void impInt (const void* e)
{
    int* i = (int*)e;
    printf("%d ",*i);

}
