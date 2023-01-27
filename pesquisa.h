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

#define ITENSPAGINA 1000
#define MAXTABELA 2000



int pesquisaBinaria(tipoitem [], tipoitem *, int , int );

int pesquisa(tipoindice [], int , tipoitem* , FILE *, int);

void psi_main(int,FILE*, int);

int verifica(int , char *[] );


#endif