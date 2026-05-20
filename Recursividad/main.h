#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

long long factorial (int num);
void mostrarCadenaChar (char* cadena);
void mostrarCadenaCharInv (char* cadena);

void mostrarProgresivo (char* cadena);
void _mostrarProgresivo (char* cadena, int largo); ///LA FUNCION ENVOLTORIO


void mostrarProgresivoInv (char* cadena);
void _mostrarProgresivoInv (char* cadena, int largo);

void mostrarProgresivocomunEInv (char* cadena);


bool esPalindromo (char* cadena);
bool _esPalindromo (char* ini,char *fin);
bool _esLetra(char x);
bool _esIgual (char x, char y);



#endif // MAIN_H_
