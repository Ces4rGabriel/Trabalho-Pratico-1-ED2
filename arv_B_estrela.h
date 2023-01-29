#ifndef ARVOREBESTRELA
#define ARVOREBESTRELA
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MM 3
#define MM2 2*MM
//*
typedef int TipoChave;

typedef struct TipoRegistro{
    TipoChave chave;
    long dado1;
    char dado2[50]; 
} TipoRegistro;

typedef enum {Interna, Externa} TipoIntExt;

typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina {
    TipoIntExt Pt;
    union {
        struct {
            int ni;
            TipoRegistro ri[MM2];
            TipoApontador pi[MM2 + 1];
        }U0;
        struct {
            int ne;
            TipoRegistro re[MM2];
        }U1;
    }UU;
} TipoPagina;

int pesquisa_BS(TipoRegistro *x, TipoApontador *Ap);
void arvB_main(int chave, FILE *arq, int qtd_limite);
void Inicializa(TipoApontador arvore);
void bstar_Insere(TipoRegistro reg, TipoApontador *Ap);
void bstar_Ins(TipoRegistro reg, TipoApontador Ap, short *Cresceu, TipoRegistro *RegRetorno, TipoApontador *ApRetorno);
void bstar_InsereNaPagina(TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir);
void escreverValor(TipoApontador *Ap);
void bstar_Imprime(TipoApontador Ap);

#endif