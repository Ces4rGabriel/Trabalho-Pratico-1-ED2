#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define M 10

typedef int TipoChave;

typedef struct TipoRegistro{
    TipoChave chave;
    long dado1;
    char dado2[50]; 
} TipoRegistro;

typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina
{
    short n; //quantidade de posições dentro do vetor r
    TipoRegistro r[2*M];
    TipoApontador p[2*M + 1];
}TipoPagina;

void arvB_main(int chave, FILE *arq);

void Inicializa(TipoApontador arvore);

int pesquisaArvB(TipoRegistro *x, TipoApontador ap);

void imprimir(TipoApontador arv);

void insere(TipoRegistro Reg, TipoApontador *ap);

void ins(TipoRegistro Reg, TipoApontador ap, short *cresceu, TipoRegistro *RegRetorno, TipoApontador *apRetorno);

void insereNaPag(TipoApontador ap, TipoRegistro Reg, TipoApontador apDir);

void limpaArvB(TipoApontador ap);