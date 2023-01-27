#ifndef PESQUISA_H
#define PESQUISA_H

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



int pesquisaBinaria(TipoItem [], TipoItem *, int , int );

int pesquisa(TipoIndice [], int , TipoItem* , FILE *, int);

void pesSeqInd(int,FILE*, int);

int verifica(int , char *[] );


#endif