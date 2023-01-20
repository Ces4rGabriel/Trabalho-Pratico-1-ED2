#ifndef PESQUISA_H
#define PESQUISA_H

#include <stdlib.h>

typedef struct{
    int chave;
}tipoindice;


typedef struct{
    int chave;
    long dado1;
    char dado2[50]; 
}tipoitem;

#define ITENSPAGINA 100
#define MAXTABELA 100



int pesquisaBinaria(tipoitem [], tipoitem *, int , int );

int pesquisa(tipoindice [], int , tipoitem* , FILE *);

void psi_main(int);


#endif