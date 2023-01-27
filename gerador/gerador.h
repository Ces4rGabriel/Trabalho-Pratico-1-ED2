#ifndef GERADOR_H
#define GERADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAMANHOSTRING 500
#define NUMERODEREGISTROS 2000000

typedef struct{
    int chave;
    long dado1;
    char dado2[TAMANHOSTRING]; 
}Registro;

void gerarArquivoCrescente(int);

void gerarArquivoDecrescente(int);

void gerarArquivoDesordenado(int);


#endif