#ifndef PESQUISA_H
#define PESQUISA_H
#include "analise.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int chave;
}TipoIndice;


typedef struct{
    int chave;
    long dado1;
    char dado2[50]; 
}TipoItem;

#define ITENSPAGINA 1000
#define MAXTABELA 2000



int pesquisaBinaria(TipoItem [], TipoItem *, int , int , Analis *);

int pesquisa(TipoIndice [], int , TipoItem* , FILE *, int, Analis *);

void pesSeqInd(int,FILE*, int, Analis *, int pp);

int verifica(int , char *[] );


#endif