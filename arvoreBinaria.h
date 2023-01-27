#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHOSTRING 500

typedef struct{
    int chave;
    long dado1;
    char dado2[TAMANHOSTRING]; 
    int apontadorEsq;
    int apontadorDir;
}TipoItemBinario;

typedef struct{
    int chave;
    long dado1;
    char dado2[TAMANHOSTRING]; 
}TipoItem;

#define NUMERODEREGISTROS 2000


void pesquisaBinariaMain();

void converteArquivoParaBinario(FILE**, FILE**);

#endif