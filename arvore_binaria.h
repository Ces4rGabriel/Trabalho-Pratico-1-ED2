#ifndef ARVOREBINARIA_H
#define ARVOREBINARIA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define TAMANHOSTRING 500
#define NUMERODEREGISTROS 2000


typedef struct
{
    int chave;
    long dado1;
    char dado2[TAMANHOSTRING]; 
    int apontadorEsq;
    int apontadorDir;
}TipoItemBinario;

typedef struct
{
    int chave;
    long dado1;
    char dado2[TAMANHOSTRING]; 
}TipoItem;

typedef struct
{
    int numeroDeAcessos;
    int numeroDeComparacoes;
    double tempoDecorrido;
    TipoItem itemRetornado;
}TipoDadosRecolhidos;

typedef struct
{
    int metodoDePesquisa;
    int quantidadeDeRegistros;
    int situacaoDoArquivo;
    int chaveDesejada;
    int argOpcional;
}TipoEntradaTerminal;

void buscaBinariaMain(TipoEntradaTerminal, TipoDadosRecolhidos*);

void chamadaConvercao(TipoEntradaTerminal , TipoDadosRecolhidos* );

void converteArquivoParaBinario(FILE**, FILE**, TipoEntradaTerminal, TipoDadosRecolhidos*);

TipoItem localizaElementoNoArquivo(FILE** , TipoEntradaTerminal, TipoDadosRecolhidos*);

#endif