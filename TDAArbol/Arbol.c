#include "Arbol.h"
#include <string.h>

void crearArbol (tArbol* pr)
{
    *pr = NULL;
}
int InsertarArbolBinario (tArbol* pr, void* dato, unsigned tamElem,CMP cmp)
{
    if(*pr == NULL)
    {
        *pr = (tNodo*)malloc(sizeof(tNodo));
        if(*pr == NULL)
            return SIN_MEM;
        (*pr)->info = malloc(tamElem);
        if((*pr)->info == NULL)
        {
            free(*pr);
            return SIN_MEM;
        }
        ///COPIO LOS DATOS
        memcpy((*pr)->info,dato,tamElem);
        (*pr)->tamElem = tamElem;
        (*pr)->Der = NULL;
        (*pr)->Izq = NULL;
        return TODO_OK;
    }
    int ret = cmp(dato,(*pr)->info);
    if(ret > 0)
        return InsertarArbolBinario(&(*pr)->Der,dato,tamElem,cmp);
    if(ret < 0)
         return InsertarArbolBinario(&(*pr)->Izq,dato,tamElem,cmp);

    return DUPLICADO; ///EN ARBOLES DE BUSQUEDA BINARIA NO SE ADMITEN DUPLICADOS

}
int InsertarArbolBinarioIterativo (tArbol* pr, void* dato, unsigned tamElem,CMP cmp)
{
    int ret = 10;
    while(*pr && ret != DUPLICADO)
    {
        ret = cmp(dato,(*pr)->info);
        if(ret > 0)
            pr = &(*pr)->Der;
        if(ret < 0)
            pr = &(*pr)->Izq;
    }
    if(ret != DUPLICADO)
    {
        *pr = (tNodo*)malloc(sizeof(tNodo));
        if(*pr == NULL)
            return SIN_MEM;
        (*pr)->info = malloc(tamElem);
        if((*pr)->info == NULL)
        {
            free(*pr);
            return SIN_MEM;
        }
        ///COPIO LOS DATOS
        memcpy((*pr)->info,dato,tamElem);
        (*pr)->tamElem = tamElem;
        (*pr)->Der = NULL;
        (*pr)->Izq = NULL;
        return TODO_OK;
    }

    return ret;
}



///FUNCIONES DE RECORRER COMUN
void recorrerArbol (tArbol* pr, int tipoDerecorrido, IMP imp)
{
    switch(tipoDerecorrido)
    {
    case PRE_ORDEN:
        {
            _preOrden(pr,imp);
                break;
        }
        case IN_ORDEN:
        {
            _InOrden(pr,imp);
                break;
        }
        case POS_ORDEN:
        {
            _posOrden(pr,imp);
                break;
        }
    default:
        {
            puts("Tipo de recorrido no valido");
        }
    }
}
void _preOrden (tArbol* pr,IMP imp)
{
    if(*pr == NULL)
        return;
    imp((*pr)->info); ///HAGO LA ACCION
    _preOrden(&(*pr)->Izq,imp);
    _preOrden(&(*pr)->Der,imp);
}

void _InOrden (tArbol* pr, IMP imp)
{
    if(*pr == NULL)
        return;
    _InOrden(&(*pr)->Izq,imp);
    imp((*pr)->info); ///HAGO LA ACCION
    _InOrden(&(*pr)->Der,imp);

}
void _posOrden (tArbol* pr, IMP imp)
{
    if(*pr == NULL)
        return;
    _posOrden(&(*pr)->Izq,imp);
    _posOrden(&(*pr)->Der,imp);
     imp((*pr)->info); ///HAGO LA ACCION
}
void _posOrdenIterativo(tArbol* pr, IMP imp) ///I D R
{
    if(*pr)
    {
        if((*pr)->Izq)
        {
         tArbol* act = &(*pr)->Izq;
        ///  tArbol* guardar = act;
          while(*act)
          {
              tArbol* nodoAnterior = act;
              while((*act)->Izq)
                act = &(*act)->Izq;
              if((*act)->Der)
                act = &(*act)->Der;
            if(*act == NULL) imp((*nodoAnterior)->info);
          }
        }

        if((*pr)->Der)
        {
          tArbol* act = &(*pr)->Der;
          ///tArbol* guardar = act;
          while(*act)
          {
              tArbol* nodoAnterior = act;
             while((*act)->Izq)
                act = &(*act)->Izq;
            if((*act)->Der)
                act = &(*act)->Der;
            if(*act == NULL) imp((*nodoAnterior)->info);
          }
        }
        imp((*pr)->info);

    }
}
int eliminarNodo (tArbol* pr,void* clave, unsigned tamElem, CMP cmp)
{
    if(*pr == NULL) return ARBOL_VACIO;
    tArbol* nodoBuscado = _buscarNodoEnArbol(pr,clave,cmp); ///BUSCO LA DIRECCION DEL NODO

    if(nodoBuscado == NULL) return CLAVE_NO_ENCONTRADA;

    int alturaPorIzq = contarAltura(&(*nodoBuscado)->Izq);
    int alturaPorDer = contarAltura(&(*nodoBuscado)->Der);

    tNodo** nodoAnterior = (alturaPorIzq > alturaPorDer ? _buscarMayorNodo(nodoBuscado) : _buscarMenorNodo(nodoBuscado));
    memcpy(clave,(*nodoBuscado)->info,tamElem > (*nodoBuscado)->tamElem? (*nodoBuscado)->tamElem : tamElem);


    if(*nodoAnterior)
    {

      if(alturaPorIzq > alturaPorDer)
      {
        tNodo** elim = &(*nodoAnterior)->Der;
        (*nodoAnterior)->Der = (*elim)->Izq;
        free((*elim)->info);
        free(*elim);

      }
      else
       {

        tNodo** elim = &(*nodoAnterior)->Izq;
        (*nodoAnterior)->Izq = (*elim)->Der;
        free((*elim)->info);
        free(*elim);

       }

    }
    else ///ES HOJA
    {
        free((*nodoBuscado)->info);
        free(*nodoBuscado);
        *nodoBuscado = NULL;
    }


    return CLAVE_ENCONTRADA;
}
tNodo** _buscarNodoEnArbol(tArbol* pr,void* clave,CMP cmp)
{
    if(*pr == NULL) return NULL;
    int ret = cmp(clave,(*pr)->info);
    if(ret == 0)
    {
     return pr;
    }
    if(ret > 0)
        return _buscarNodoEnArbol(&(*pr)->Der,clave,cmp);
    else
        return _buscarNodoEnArbol(&(*pr)->Izq,clave,cmp);

}
tNodo** _buscarMayorNodo (tArbol* pr)
{
    tNodo** ant = &(*pr)->Izq;
    if(*ant)
    {

    tNodo** Act = &(*ant)->Der;
    while((*Act)->Der)
    {
        ant = Act;
        Act = &(*Act)->Der;
    }

    }

    return ant;
}
tArbol* _buscarMenorNodo (tArbol* pr)
{
    tNodo** ant = &(*pr)->Der;
    if(*ant)
    {
        tNodo** Act = &(*ant)->Izq;
     while((*Act)->Izq)
    {
        ant = Act;
        Act = &(*Act)->Izq;
    }
   }

    return ant;

}
///EJERCICIOS
int contarTodosLosNodos (tArbol* pr)
{
    int nodos = 0;
    _contarTodosLosNodos(pr,&nodos);
    return nodos;
}
void _contarTodosLosNodos (tArbol* pr, int* cont)
{
    if(*pr == NULL) return;
    *cont += 1;
    _contarTodosLosNodos(&(*pr)->Izq,cont);
    _contarTodosLosNodos(&(*pr)->Der,cont);
}

int contarTodosLosNodosHojas (tArbol* pr)
{
    int nodos = 0;
    _contarTodosLosNodosHojas(pr,&nodos);
    return nodos;
}

void _contarTodosLosNodosHojas (tArbol* pr, int* cont)
{
    if(*pr == NULL) return;
    if((*pr)->Izq == NULL && (*pr)->Der == NULL)
    {
        *cont += 1;
        return;
    }

    _contarTodosLosNodosHojas(&(*pr)->Izq,cont);
    _contarTodosLosNodosHojas(&(*pr)->Der,cont);
}

int contarTodosLosNodosConHijos(tArbol *pr)
{
    int nodos = 0;
    _contarTodosLosNodosConHijos(pr,&nodos);
    return nodos;
}
void _contarTodosLosNodosConHijos (tArbol* pr, int* cont)
{
    if(*pr == NULL) return;
    if((*pr)->Izq || (*pr)->Der)
    {
        *cont += 1;
    }
      _contarTodosLosNodosConHijos(&(*pr)->Izq,cont);
      _contarTodosLosNodosConHijos(&(*pr)->Der,cont);
}

int contarTodosLosNodosConHijosPorIzq(tArbol *pr)
{
    int nodos = 0;
    _contarTodosLosNodosConHijosPorIzq(pr,&nodos);
    return nodos;
}
void _contarTodosLosNodosConHijosPorIzq (tArbol* pr, int* cont)
{
    if(*pr == NULL) return;
    if((*pr)->Izq)
    {
        *cont += 1;
    }
      _contarTodosLosNodosConHijosPorIzq(&(*pr)->Izq,cont);
      _contarTodosLosNodosConHijosPorIzq(&(*pr)->Der,cont);
}

int contarTodosLosNodosConHijosPorDer(tArbol *pr)
{
    int nodos = 0;
    _contarTodosLosNodosConHijosPorDer(pr,&nodos);
    return nodos;
}
void _contarTodosLosNodosConHijosPorDer (tArbol* pr, int* cont)
{
    if(*pr == NULL) return;
    if((*pr)->Der)
    {
        *cont += 1;
    }
      _contarTodosLosNodosConHijosPorDer(&(*pr)->Izq,cont);
      _contarTodosLosNodosConHijosPorDer(&(*pr)->Der,cont);
}

int contarTodosLosNodosConHijosSoloPorIzq(tArbol *pr)
{
    if(*pr == NULL) return 0;
    if((*pr)->Izq && !(*pr)->Der)
        return 1 + contarTodosLosNodosConHijosSoloPorIzq((&(*pr)->Izq));

    return contarTodosLosNodosConHijosSoloPorIzq(&(*pr)->Izq) + contarTodosLosNodosConHijosSoloPorIzq(&(*pr)->Der);
}
int contarTodosLosNodosConHijosSoloPorDer(tArbol *pr)
{
    if(*pr == NULL) return 0;
    if(!(*pr)->Izq && (*pr)->Der)
        return 1 + contarTodosLosNodosConHijosSoloPorDer((&(*pr)->Der));

    return contarTodosLosNodosConHijosSoloPorDer(&(*pr)->Izq) + contarTodosLosNodosConHijosSoloPorDer(&(*pr)->Der);
}
int contarAltura (tArbol* pr)
{
    if(*pr == NULL) return 0;

    int alturaIzq = contarAltura(&(*pr)->Izq);
    int alturaDer = contarAltura(&(*pr)->Der);

   return 1 + ((alturaIzq > alturaDer) ? alturaIzq : alturaDer);
}
int contarNivel (tArbol* pr)
{
    int  nivel = contarAltura(pr);
    nivel = (nivel)? (nivel-1) : nivel; ///ES CLAVE SABER QUE CUALQUIER NUMERO DISTINTO DE 0 SE TOMA COMO VERDADERO Y EL 0 SE TOMA COMO FALSO
    return nivel;
}
void buscarDatoPorNivel (tArbol* pr, int nivel, ACC accion)
{
    _buscarDatoPorNivel(pr,nivel,0,accion);
}
void _buscarDatoPorNivel (tArbol* pr, int nivel, int Actnivel, ACC accion)
{
    if(*pr == NULL || nivel < 0 || nivel < Actnivel) return;

    if(nivel == Actnivel)
    {
        accion((*pr)->info);
    }

    _buscarDatoPorNivel(&(*pr)->Izq,nivel,Actnivel + 1, accion);
    _buscarDatoPorNivel(&(*pr)->Der,nivel,Actnivel + 1, accion);
}
int buscarEnArbol(const tArbol* pr,void* dato, unsigned tamElem,CMP cmp)
{
    if(*pr == NULL) return CLAVE_NO_ENCONTRADA;
    int ret = cmp(dato,(*pr)->info);
    if(ret == 0)
    {
     memcpy(dato,(*pr)->info,tamElem > (*pr)->tamElem? (*pr)->tamElem : tamElem);
     return CLAVE_ENCONTRADA;
    }
    if(ret > 0)
        return buscarEnArbol(&(*pr)->Der,dato,tamElem,cmp);
    else
        return buscarEnArbol(&(*pr)->Izq,dato,tamElem,cmp);

}
void podarHojas (tArbol* pr)
{
    if(*pr == NULL) return;

    if(!(*pr)->Izq && !(*pr)->Der)
    {
        free((*pr)->info);
        free(*pr);
        *pr = NULL;
        return;
    }
    podarHojas(&(*pr)->Izq);
    podarHojas(&(*pr)->Der);
}

void destruirArbol (tArbol* pr)
{
    if(*pr == NULL)
        return;
    destruirArbol(&(*pr)->Izq);
    destruirArbol(&(*pr)->Der);
    free((*pr)->info);
    free(*pr);
    *pr = NULL;
}
int cargarArchivoDesordenadoArbol(tArbol* pr, char* nombrArch,unsigned tamElem, CMP cmp, carIndice cargar)
{
    FILE* arch = fopen(nombrArch,"rb");
    if(arch == NULL)
    {
        puts("No se pudo abrir el archivo");
        return ERROR_ARCHIVO;
    }
    void* dato = malloc(tamElem);
    if(dato == NULL)
    {
        fclose(arch);
        return SIN_MEM;
    }

    int offset = 0;
    tIndice indice;
    while(fread(dato,tamElem,1,arch))
    {
        cargar(dato,&indice);
        indice.indiceRegistro = offset;
        InsertarArbolBinario(pr,&indice,sizeof(tIndice),cmp);
        offset++;
    }

    fclose(arch);
    free(dato);
    return TODO_OK;

}

int cargarArbolArchivoOrdenado (tArbol* pr, char* nuevoArch, char* archivoViejo, unsigned tamElem)
{
    FILE* viejo = fopen(archivoViejo,"rb");
    if(viejo == NULL)
    {
        puts("No se pudo abrir el archivo");
        return ERROR_ARCHIVO;
    }
    FILE* nuevo = fopen(nuevoArch,"wb");
    if(nuevo == NULL)
    {
        fclose(viejo);
        puts("No se pudo abrir el archivo");
        return ERROR_ARCHIVO;
    }
    tIndice indice;
    void* dato = malloc(tamElem);
    if(dato == NULL)
    {
        fclose(viejo);
        fclose(nuevo);
        return SIN_MEM;
    }
    _cargarArbolArchivoOrdenado(pr,nuevo,viejo,&indice,dato,tamElem);
    fclose(viejo);
    fclose(nuevo);
    free(dato);
    remove(archivoViejo);
    rename(nuevoArch,archivoViejo);
    return TODO_OK;
}
void _cargarArbolArchivoOrdenado (tArbol* pr, FILE* nuevo, FILE* viejo, tIndice* indice, void* dato,unsigned tamElem)
{
    if(*pr == NULL)
        return;
    _cargarArbolArchivoOrdenado(&(*pr)->Izq,nuevo,viejo,indice,dato,tamElem);
    indice = (tIndice*)((*pr)->info);
    fseek(viejo,indice->indiceRegistro*tamElem,0);
    fread(dato,tamElem,1,viejo);
    fwrite(dato,tamElem,1,nuevo);
    _cargarArbolArchivoOrdenado(&(*pr)->Der,nuevo,viejo,indice,dato,tamElem);

}
int balancearArbol(char* nombrArch, tArbol* pr)
{
    FILE* arch = fopen(nombrArch,"rb");
    if(arch == NULL)
    {
        puts("No se pudo abrir el archivo");
        return ERROR_ARCHIVO;
    }
    fseek(arch,0,SEEK_END); ///ME MUEVO ALA FINAL;
    int canBytes = ftell(arch);
    int cantRegistros = canBytes/sizeof(tRegistro);
    _balancearArbol(arch,pr,0,cantRegistros);
    fclose(arch);
    return TODO_OK;
}
void _balancearArbol (FILE* Arch, tArbol* pr, int ini, int fin)
{
    if(ini > fin)
        return;
    size_t medio = (ini + fin)/2;
    fseek(Arch,medio * sizeof(tRegistro),0); ///ME MUEVO
    tRegistro reg;
    tIndice idx;
    fread(&reg,sizeof(tRegistro),1,Arch);
    idx.clave.dni = reg.dni;
    idx.indiceRegistro = medio;
    InsertarArbolBinario(pr,&idx,sizeof(tIndice),cmpIndice);
     _balancearArbol(Arch,pr,ini,medio-1);
     _balancearArbol(Arch,pr,medio+1,fin);

}
int cmpIndice (const void* e1, const void* e2)
{
    tIndice* i1 = (tIndice*)e1;
    tIndice* i2 = (tIndice*)e2;
    return i1->clave.dni - i2->clave.dni;
}
int buscarEnArchivoConIndice(FILE *fp, const tArbol *pa, tRegistro* reg)
{
     int claveEncontrada;
     tIndice idx;
     idx.clave.dni = reg->dni;
    claveEncontrada = buscarEnArbol(pa,&idx,sizeof(tIndice),cmpIndice);

   if(claveEncontrada == CLAVE_ENCONTRADA)
    {
        fseek(fp, idx.indiceRegistro * sizeof(tRegistro), SEEK_SET);
        fread(reg, sizeof(tRegistro), 1, fp);
        return CLAVE_ENCONTRADA;
   }
    else
      {
          return CLAVE_NO_ENCONTRADA;
    }
}
