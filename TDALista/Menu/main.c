#include "main.h"
/**
**Ejercicio de Programación: Menú para Manejo de una Lista**
Desarrolle un programa que permita al usuario gestionar una lista de datos mediante un menú de opciones.

El programa debe permitir realizar las siguientes operaciones sobre la lista:

* Crear la lista
* Cargar un dato al final de la lista
* Mostrar la lista
* Verificar si la lista está llena.
* Verificar si la lista está vacía
* Vaciar la lista
* Salir
*/

int mostrarMenu(tLista *p,bool *control,unsigned tamElem,Ing ING, imp IMP, cmp CMP);

///PERSONA
int cmpPersona (const void* e1, const void* e2);
void impPersona(const void* e);

///PRODUCTO
int cmpProducto (const void* e1, const void* e2);
void impProducto(const void* e);
void ingProd (void* e);


int main()
{
    tLista lista;
    bool creado = false;
    int selec;
    do{
     puts("==================================================");
    puts("          EJERCICIO DE CLASE          ");
    puts("==================================================");
    puts("  1. Crear la lista");
    puts("  2. Cargar un dato al final");
    puts("  3. Mostrar la lista");
    puts("  4. Verificar si la lista esta llena");
    puts("  5. Verificar si la lista esta vacia");
    puts("  6. Vaciar la lista");
    puts("  7. Insertar en Orden");
    puts("  8. Eliminar sin duplicados");
    puts("  9. Ordenar de Menor a Mayo");
    puts("  10. SALIR");
    puts("--------------------------------------------------");
    printf(" Seleccione una opcion [1-%d]: ",FIN_MENU);
    selec = mostrarMenu(&lista,&creado,sizeof(tProducto),ingProd,impProducto, cmpProducto);
    putchar('\n');
    }while(selec != FIN_MENU);
    sleep(1);
    return 0;
}
int mostrarMenu(tLista *p,bool *control,unsigned tamElem,Ing ING, imp IMP, cmp CMP)
{
    int seleccion;
    scanf("%d",&seleccion); fflush(stdin);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    if(!*control) ///NO SE CREO LA LISTA
    {
        if(seleccion != 1 && seleccion != FIN_MENU)
        {
            puts("No se puede hacer esta operacion porque no se creo la lista");
            getchar();
            return seleccion;
        }
    }

    switch(seleccion)
    {
    case 1:
        if(*control && *p) ///SOLO VACIA LA LISTA SI ESTA CREADA
        {
            puts("Vaciando la lista anterior...");
            sleep(1);
            vaciarLista(p); ///SI LA LISTA ESTA CREADA, LA VACIA Y CREO UNA NUEVA
        }
        crearLista(p);
        puts("Se creo la lista correctamente");
        *control = true;

        break;
    case 2:
         {
             void* elem = malloc(tamElem);
             if(elem == NULL)
             {
                 puts("No hay memoria");
                 return SIN_MEM;
             }
             ING(elem);

             if(InsertarAlFinal(p,elem,tamElem) == SIN_MEM) puts("NO HAY MEMORIA");
             else puts("SE INSERTO EL ELEMENTO CORRECTAMENTE");

             free(elem);
             break;
         }
    case 3:
        {
            if(_MostrarLista(p,IMP) == SIN_MEM) puts("LISTA VACIA");
            else puts("SE MOSTRO LA LISTA CORRECTAMENTE");

            break;
        }
    case 4:
        {
            if(listaLlena(p,sizeof(tPersona)) == SIN_MEM)
                puts("La lista esta llena");
            else
                puts("La lista aun no esta llena");
            break;
        }
    case 5:
        if(listaVacia(p) == LISTA_VACIA)
            puts("La lista esta vacia");
        else
            puts("La lista no esta vacia");
        break;
    case 6:
        {
            vaciarLista(p);
            puts("Se vacio la lista");
            *control = false;
            break;
        }
    case 7:
        {
            void* elem = malloc(tamElem);
             if(elem == NULL)
             {
                 puts("No hay memoria");
                 return SIN_MEM;
             }
             ING(elem);
            if(InsertarEnOrden(p,elem,tamElem,CMP,false,NULL) == SIN_MEM) puts("NO HAY MEMORIA");
             else puts("SE INSERTO EL ELEMENTO CORRECTAMENTE");

            free(elem);
             break;

        }
    case 8:
        {
            int pos;
            printf("Ingresar la posicion que quiere eliminar:\t");
            scanf("%d",&pos);
            void* elem = malloc(tamElem);
            if(elem == NULL)
             {
                 puts("No hay memoria");
                 return SIN_MEM;
             }
            int ret = eliminarElementoPosN(p,elem,tamElem,pos);
            if(ret == LISTA_VACIA) puts("No hay elementos en la lista");
            if(ret == ERROR) puts("La posicion que se envio, no existe");
            if(ret == NO_ENCONTRADO) puts("El elemento que se quiere eliminar, no existe en la lista");
            if(ret == TODO_OK)
            {
                puts("Se elimino el elemento correctamente");
                IMP(elem);
            }
            free(elem);
            break;
        }
    case 9:
        {
        if(OrdenarLista(p,cmpPersona) == TODO_OK) puts("Se ordeno la lista correctamente");
        else puts("La lista esta vacia");

        break;
        }
    case 10:
        {
        puts("Saliendo del programa");
        if(*p != NULL)
              {
               vaciarLista(p);///DEBO ASEGURARME DE QUE LA LISTA ESTE VACIA
               puts("Vaciando lista...");
               sleep(1);
              }
        break;
    default:
        puts("No elegiste ninguna de las opciones");
       }
    }
    puts("\n--------------------------------------------------");
    puts("Presione ENTER para continuar...");
    getchar();
    return seleccion;
}
int _InsertarEnOrden(tLista* p, cmp CMP)
{
    tPersona persona;
    printf("Ingresar el nombre de la persona:\t");
    fgets(persona.nyap,TAM_NYAP,stdin);
    putchar('\n');
    if(persona.nyap[strlen(persona.nyap) - 1] == '\n')
        persona.nyap[strlen(persona.nyap) - 1] = '\0';
    printf("Ingresar el dni de la persona:\t");
    scanf("%lld", &persona.dni);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return InsertarEnOrden(p,&persona,sizeof(tPersona),CMP,false,NULL);

}
int _InsertarAlFinal(tLista* p)
{
    tPersona persona;
    printf("Ingresar el nombre de la persona:\t");
    fgets(persona.nyap,TAM_NYAP,stdin);
    putchar('\n');
    if(persona.nyap[strlen(persona.nyap) - 1] == '\n')
        persona.nyap[strlen(persona.nyap) - 1] = '\0';
    printf("Ingresar el dni de la persona:\t");
    scanf("%lld", &persona.dni);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    return InsertarAlFinal(p,&persona,sizeof(persona));
}

///PUNTEROS A FUNCION:
int cmpPersona (const void* e1, const void* e2)
{
    tPersona* i1 = (tPersona*)e1;
    tPersona* i2 = (tPersona*)e2;
    return strcmpi(i1->nyap,i2->nyap);
}
int _MostrarLista(const tLista* p,imp IMP)
{
    if(*p == NULL) return SIN_MEM;
    while(*p)
    {
        IMP((*p)->info);
        p = &(*p)->sig; ///MUEVO LA VARIABLE LOCAL
    }
    return TODO_OK;
}
void impPersona(const void* e)
{
    tPersona* i = (tPersona*)e;
    printf("%*s -%8lld\n",TAM_NYAP,i->nyap,i->dni);
}

int cmpProducto (const void* e1, const void* e2)
{
    tProducto* i1 = (tProducto*)e1;
    tProducto* i2 = (tProducto*)e2;

    return i1->codigo - i2->codigo;
}
void impProducto(const void* e)
{
     tProducto* i = (tProducto*)e;
     printf("%*s -%8d\n",TAM_NOM_PRO,i->nombre,i->codigo);
}

///INGRESAR GENERICO
void ingProd (void* e)
{
    tProducto* prod = (tProducto*)e;
    printf("Ingresar el codigo del producto:\n");
    scanf("%d",&prod->codigo);
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    printf("Ingresar el nombre del producto:\t");
    fgets(prod->nombre,TAM_NOM_PRO,stdin);
    putchar('\n');
    if(strlen(prod->nombre) > 0 && prod->nombre[strlen(prod->nombre) - 1] == '\n')
        prod->nombre[strlen(prod->nombre) - 1] = '\0';
    while ((c = getchar()) != '\n' && c != EOF);
}

