#ifndef MAIN_H_
#define MAIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

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


void mostrarNumeroProgresivo(int num);
void _mostrarNumeroProgresivo(int num,int fin);

void mostrarNumeroProgresivoInv(int num);
void _mostrarNumeroProgresivoInv(int num,int fin);

 void mostrarNumeroProgresivoCompleto (int num);



 void printi1(int n);
void printi2(int n);
void printi3(int n);
void printi4(int n);
void printi5(int n);
void printi6(int n);

#endif // MAIN_H_
