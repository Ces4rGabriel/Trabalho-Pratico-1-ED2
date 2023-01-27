#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int chave;
    long dado1;
    char dado2[50]; 
    int apontadorEsq;
    int apontadorDir;
}TipoItemBinario;

typedef struct{
    int chave;
    long dado1;
    char dado2[50]; 
}TipoItem;

#define ITENSPAGINA 1000
#define MAXTABELA 2000


void pesquisaBinariaMain();

void converteArquivoParaBinario(FILE**, FILE**);

#endif