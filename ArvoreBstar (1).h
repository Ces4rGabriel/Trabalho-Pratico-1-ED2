#ifndef TP1_ARVOREBSTAR_H
#define TP1_ARVOREBSTAR_H

#include "Analise.h"
#include <iostream>
#include <ctime>
#include <cstring>
#define f(inicio,fim) for(int i =inicio ; i<fim; i++)
using namespace std;
#define MM 4
#define MM2 6


typedef struct tipoitem Item;
typedef enum {Interna, Externa} TipoIntExt;
typedef struct TipoPagina TipoPagina;
typedef struct TipoPagina* TipoApontador;
typedef struct tipoindice Indice;
typedef struct arvore Arvore;

TipoApontador geraArvoreBstar(Analise* analise);
void InsereNaPagina(TipoApontador Apontador, int Registro, TipoApontador ApontadorDireita,Analise* analise);
void Ins(Item *Registro, TipoApontador Apontador, short *Cresceu, Item *RegRetorno, TipoApontador* ApRetorno, short *Cresceu_no,Analise* analise);
void Insere(Item *Registro, TipoApontador* Apontador, Analise* analise);
bool InserenaFolha(Item *reg, TipoApontador nova_pagina,Analise* analise );
void ImprimeBSTAR(TipoApontador arvore);
bool PesquisaArvoreBstar(Item *x, TipoApontador *Ap,Analise* analise);


#endif //TP1_ARVOREBSTAR_H
