#include "Arbol.h"

#include <string.h>



int cmpInt (const void* e1,const void* e2);

void CargarReg (const void* d, void* reg);


void impInt (const void* e);
void impIndice (const void* e);
void impReg (const void*e);


int cargarArchivo(char* nombrArch);
int mostrarArchivo (char* nombrArch);


int main(int argc, char* argv[])
{
    tArbol arbol;
///    int num = 5;
    crearArbol(&arbol);
///    InsertarArbolBinarioIterativo(&arbol,&num,sizeof(num),cmpInt);
//    recorrerArbol(&arbol,POS_ORDEN,impInt);
//    puts("");
//        printf("La altura del arbol es %d\n",contarAltura(&arbol));
//    printf("El nivel del arbol es %d\n",contarNivel(&arbol));
//
//    num = 3;
//    InsertarArbolBinarioIterativo(&arbol,&num,sizeof(num),cmpInt);
//    recorrerArbol(&arbol,POS_ORDEN,impInt);
//    puts("");
//    num = 7;
//    InsertarArbolBinarioIterativo(&arbol,&num,sizeof(num),cmpInt);
//    recorrerArbol(&arbol,POS_ORDEN,impInt);
//    puts("");
//    num = 1;
//    InsertarArbolBinarioIterativo(&arbol,&num,sizeof(num),cmpInt);
//    recorrerArbol(&arbol,POS_ORDEN,impInt);
//        puts("");
//     num = 8;
//    InsertarArbolBinarioIterativo(&arbol,&num,sizeof(num),cmpInt);
//    recorrerArbol(&arbol,POS_ORDEN,impInt);
//    puts("");
//     num = 6;
//    InsertarArbolBinarioIterativo(&arbol,&num,sizeof(num),cmpInt);
//    recorrerArbol(&arbol,POS_ORDEN,impInt);
//    puts("");
//    printf("La cantidad de nodos es %d\n",contarTodosLosNodos(&arbol));
//    printf("La cantidad de nodos hojas es %d\n",contarTodosLosNodosHojas(&arbol));
//    printf("La cantidad de nodos con hijos es %d\n",contarTodosLosNodosConHijos(&arbol));
//    printf("La cantidad de nodos con hijos por Izq es %d\n",contarTodosLosNodosConHijosPorIzq(&arbol));
//    printf("La cantidad de nodos con hijos por Der es %d\n",contarTodosLosNodosConHijosPorDer(&arbol));
//    printf("La cantidad de nodos con hijos SOLO por Izq es %d\n",contarTodosLosNodosConHijosSoloPorIzq(&arbol));
//
//    printf("La altura del arbol es %d\n",contarAltura(&arbol));
//    printf("El nivel del arbol es %d\n",contarNivel(&arbol));
//
//    buscarDatoPorNivel(&arbol,2,impInt);
//    puts("");
//
//    podarHojas(&arbol);
//    puts("Podando hojas");
//    recorrerArbol(&arbol,POS_ORDEN,impInt);
//
//
//    destruirArbol(&arbol);
//    puts("\nVaciando Arbol...");
//    recorrerArbol(&arbol,POS_ORDEN,impInt);
   cargarArchivo(argv[1]);
   cargarArchivoDesordenadoArbol(&arbol,argv[1],sizeof(tRegistro),cmpIndice,CargarReg);
   recorrerArbol(&arbol,PRE_ORDEN,impIndice);
  /// mostrarArchivo(argv[1]);
  puts("");puts("");
  cargarArbolArchivoOrdenado(&arbol,argv[2],argv[1],sizeof(tRegistro));
  mostrarArchivo(argv[1]);
  puts("");puts("");
     destruirArbol(&arbol);

tArbol indice;
crearArbol(&indice);

  balancearArbol(argv[1],&indice);
   recorrerArbol(&indice,PRE_ORDEN,impIndice);
  puts("");puts("");
  FILE* arch = fopen(argv[1],"rb");
  if(arch == NULL)
    return SIN_MEM;
  tRegistro reg;
  reg.dni = 6405637;
  if(buscarEnArchivoConIndice(arch,&indice,&reg) == CLAVE_ENCONTRADA)
  {
       printf("%-8s %-4s %-*s\n","DNI", "SEXO",
       TAM_NOMBRE,
       "NOMBRE Y APELLIDO");
        impReg(&reg);
  }
  else
    printf("El DNI: %-8d no existe en el archivo\n",reg.dni);

   destruirArbol(&indice);
   fclose(arch);
    return 0;
}
int cmpInt (const void* e1,const void* e2)
{
    int* i1 = (int*)e1;
    int* i2 = (int*)e2;
    return *i1 - *i2;
}
///PARA IMPRIMIR
void impInt (const void* e)
{
    int* i = (int*)e;
    printf("%d ",*i);
}
void impIndice (const void* e)
{
    tIndice* i = (tIndice*)e;
    printf("%ld %d\n",i->clave.dni,i->indiceRegistro);
}
void impReg (const void*e)
{
     tRegistro* registro = (tRegistro*)e;
     printf("%-8d %-4c %-*s\n",registro->dni,registro->sexo, TAM_NOMBRE,registro->nyA);
}

///PARA CARGAR
void CargarReg (const void* d, void* reg)
{
    tRegistro* registro = (tRegistro*)d;
    tIndice* indice = (tIndice*)reg;
    indice->clave.dni = registro->dni;
}

int cargarArchivo(char* nombrArch)
{
    FILE* arch = fopen(nombrArch,"wb");
    if(arch == NULL)
    {
        puts("No se pudo abrir el archivo");
        return ERROR_ARCHIVO;
    }
    tRegistro registro [] =
    {
        {46556068, "Alejo Nieva", 'M'},
        {48657123, "Roman Nieva", 'M'},
        {54024783, "Martin Nieva", 'M'},
        {28103258, "Cristian Nieva", 'M'},
        {28503258, "Maria Barboza", 'F'},
        {6405637, "Cristobal Nieva", 'M'}
    };
    ///tRegistro registro= {46556068, "Alejo Nieva", 'M'};
    int tamanio = sizeof(registro)/sizeof(tRegistro);
    fwrite(&registro,sizeof(tRegistro),tamanio,arch);
    fclose(arch);
    return TODO_OK;
}
int mostrarArchivo (char* nombrArch)
{
    FILE* arch = fopen(nombrArch,"rb");
    if(arch == NULL)
    {
        puts("No se pudo abrir el archivo");
        return ERROR_ARCHIVO;
    }
    tRegistro registro;
   printf("%-8s %-4s %-*s\n",
       "DNI",
       "SEXO",
       TAM_NOMBRE,
       "NOMBRE Y APELLIDO");
    while(fread(&registro,sizeof(registro),1,arch))
    {
        printf("%-8d %-4c %-*s\n",registro.dni,registro.sexo, TAM_NOMBRE,registro.nyA);
    }
    fclose(arch);
    return TODO_OK;
}
