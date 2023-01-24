#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define M 2

typedef long TipoChave;

typedef struct TipoRegistro{
    TipoChave chave;

} TipoRegistro;

typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina
{
    short n; //quantidade de posições dentro do vetor r
    TipoRegistro r[2*M];
    TipoApontador p[2*M + 1];
}TipoPagina;

void Inicializa(TipoApontador arvore);
int pesquisa(TipoRegistro *x, TipoApontador ap);
void imprimir1(TipoApontador arv);
void imprimir2(TipoApontador arv);
void insere(TipoRegistro Reg, TipoApontador *ap);
void ins(TipoRegistro Reg, TipoApontador ap, short *cresceu, TipoRegistro *RegRetorno, TipoApontador *apRetorno);
void insereNaPag(TipoApontador ap, TipoRegistro Reg, TipoApontador apDir);