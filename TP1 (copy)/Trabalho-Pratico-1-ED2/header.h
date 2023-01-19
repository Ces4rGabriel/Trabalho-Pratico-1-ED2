#ifndef HEADER.H
#define HEADER.H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ITENSPAGINA 100
#define MAXTABELA 100

typedef struct{
    int chave;
}TipoIndice;


typedef struct{
    int chave;
    long dado1;
    char dado2[5000]; 
}TipoItem;


int pesquisaBinaria(TipoItem x[], int chave, int esq, int dir);

int buscaSequencialIndexada(TipoIndice tabela[], int tam, TipoItem* item, FILE *arq);
#endif