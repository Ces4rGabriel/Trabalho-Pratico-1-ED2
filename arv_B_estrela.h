#ifndef ARVOREBESTRELA
#define ARVOREBESTRELA
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "analise.h"
#include <time.h>

#define MM 2
#define MM2 2*MM


//*
typedef int TipoChaveBS;

typedef struct TipoRegistroBE{
    TipoChaveBS chave;
    long dado1;
    char dado2[50]; 
} TipoRegistroBE;

typedef enum {Interna, Externa} TipoIntExt;

typedef struct TipoPaginaBE* TipoApontadorBE;

typedef struct TipoPaginaBE {
    TipoIntExt Pt;
    union {
        struct {
            int ni;
            TipoRegistroBE ri[MM2];
            TipoApontadorBE pi[MM2 + 1];
        }U0;
        struct {
            int ne;
            TipoRegistroBE re[MM2];
            TipoApontadorBE prox;
        }U1;
    }UU;
} TipoPaginaBE;

short pesquisaBEstrela(TipoRegistroBE *x, TipoApontadorBE *Ap, Analis *analise);
void arvBE_main(int chave, FILE *arq, int qtd_limite, Analis *analise, int pp);
void InicializaBE(TipoApontadorBE *arvore);
void bstar_Insere(TipoRegistroBE reg, TipoApontadorBE *Ap, Analis *analise);
void bstar_Ins(TipoRegistroBE reg, TipoApontadorBE Ap, short *Cresceu, TipoRegistroBE* RegRetorno, TipoApontadorBE *ApRetorno, Analis *analise);
void InsereNaPagina(TipoApontadorBE *Ap, TipoRegistroBE Reg, Analis *analise);
void InserenaFolha(TipoRegistroBE reg, TipoApontadorBE Ap, Analis *analise);
void imprimeExterna(TipoApontadorBE arv);

#endif