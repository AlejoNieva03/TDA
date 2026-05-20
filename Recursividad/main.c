#include "main.h"

int main()
{
     char linea [] = "Anita lava la tina"; ///EL COMPILADOR LE AGREGA EL \0
    ///SI HICIERA char b[] = {'H','o','l','a'}; // NO AGREGA EL '\0'

    mostrarCadenaChar(linea);
    putchar('\n');
    mostrarCadenaCharInv(linea);
     putchar('\n'); putchar('\n');
    mostrarProgresivo(linea);
     putchar('\n');   putchar('\n');
    mostrarProgresivoInv(linea);
     putchar('\n');
      mostrarProgresivocomunEInv(linea);
     putchar('\n');
     esPalindromo(linea)? puts("Es palindromo"): puts("No es palindromo");
       putchar('\n');
    return 0;
}
long long factorial (int num)
{
    if(num <= 1) ///EL CORTE DE LA FUNCION
        return 1;

    return num * factorial(num-1);
}
void mostrarCadenaChar (char* cadena)
{
    if(*cadena)///ME FIJO SI ESTOY EN LA CADENA
    {
        printf("'%c' ",*cadena);
        mostrarCadenaChar(++cadena);
    }
}
void mostrarCadenaCharInv (char* cadena)
{
     if(*cadena)///ME FIJO SI ESTOY EN LA CADENA
    {
        mostrarCadenaChar(++cadena);
        printf("'%c' ",*cadena);
    }
}
void mostrarProgresivo (char* cadena)
{
    int largo = 1;
    _mostrarProgresivo(cadena,largo);
}
void _mostrarProgresivo (char* cadena, int largo) ///LA FUNCION ENVOLTORIO
{
    if(*(cadena + largo - 1) == '\0')
        return;
    printf("%*.*s\n",largo,largo,cadena);
    _mostrarProgresivo(cadena,largo+1);
}

void mostrarProgresivoInv (char* cadena)
{
    int largo = 1;
    _mostrarProgresivoInv(cadena,largo);
}

void _mostrarProgresivoInv (char* cadena, int largo) ///LA FUNCION ENVOLTORIO
{
    if(*(cadena + largo - 1) == '\0')
        return;
    _mostrarProgresivoInv(cadena,largo+1);
    printf("%*.*s\n",largo,largo,cadena);
}
void mostrarProgresivocomunEInv (char* cadena)
{
    int largo = 1;
    _mostrarProgresivo(cadena,largo);
    _mostrarProgresivoInv(cadena,largo);
}

bool esPalindromo (char* cadena)
{
    char* ini = cadena;
    char* fin = cadena + strlen(cadena) - 1;
    return _esPalindromo(ini,fin);
}
bool _esPalindromo(char* ini, char* fin)
{
    if(ini >= fin)
        return true;
    while(*ini && !_esLetra(*ini))
    {
        ini++;
    }
     while(fin > ini && !_esLetra(*fin))
    {
        fin--;
    }

    if(*ini && !_esIgual(*ini,*fin))
        return false;
    return _esPalindromo(++ini,--fin);

}
bool _esLetra(char x)
{
    return (('a' <= x && 'z' >= x) ||('A' <= x && 'Z' >= x) ||('Ñ' == x)
            ||('ñ' == x));
}
bool _esIgual (char x, char y)
{
    if(x != 'ñ' && x != 'Ñ')
    {
       if('a' > x || 'z' < x) x += 32;
    }
    else
        x = 'Ñ';
    if(y != 'ñ' && y != 'Ñ')
    {
        if('a' > y || 'z' < y) y += 32;
    }
    else
       y = 'Ñ';

    return x == y;

}
