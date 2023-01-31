#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAMANHOSTRING 500
#define NUMERODEREGISTROS 1000000

typedef struct TipoRegistroBinario
{
    int chave;
    long dado1;
    char dado2[TAMANHOSTRING]; 
    int apontadorEsq;
    int apontadorDir;
}TipoRegistroBinario;

typedef struct TipoRegistroNormal
{
    int chave;
    long dado1;
    char dado2[TAMANHOSTRING]; 
}TipoRegistroNormal;

typedef struct TipoRegistroAux
{
    int chave;
    int apontadorEsq;
    int apontadorDir;
}TipoRegistroAux;

typedef struct TipoDadosRecolhidos
{
    int numeroDeAcessos;
    int numeroDeComparacoes;
    double tempoDecorrido;
    TipoRegistroNormal itemRetornado;
}TipoDadosRecolhidos;

typedef struct TipoEntradaTerminal
{
    int metodoDePesquisa;
    int quantidadeDeRegistros;
    int situacaoDoArquivo;
    int chaveDesejada;
    int argOpcional;
}TipoEntradaTerminal;

//Funcoes do gerador 
void geradorMain(TipoEntradaTerminal);
void gerarArquivoCrescente(int);
void gerarArquivoDecrescente(int);
void gerarArquivoDesordenado(int);

//Funcoes da arvore binaria
void buscaArvoreBinariaMain(TipoEntradaTerminal, TipoDadosRecolhidos*);
void chamadaConvercao(TipoEntradaTerminal, TipoDadosRecolhidos*);
void converteArquivoParaBinario(FILE**, FILE**, TipoEntradaTerminal, TipoDadosRecolhidos*);
TipoRegistroNormal localizaElementoNoArquivo(FILE** , TipoEntradaTerminal, TipoDadosRecolhidos*);


#endif