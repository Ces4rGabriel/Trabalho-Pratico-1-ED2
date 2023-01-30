#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAMANHOSTRING 500
#define NUMERODEREGISTROS 100
#define ITENSPAGINA 1000
#define MAXTABELA 2000
#define M 10

typedef struct TipoRegistroBinario
{
    int chave;
    long dado1;
    char dado2[TAMANHOSTRING]; 
    int apontadorEsq;
    int apontadorDir;
}TipoRegistroBinario;

typedef struct TipoRegistro
{
    int chave;
    long dado1;
    char dado2[TAMANHOSTRING]; 
}TipoRegistro;

typedef struct TipoRegistroAux
{
    int chave;
    int apontadorEsq;
    int apontadorDir;
}TipoRegistroAux;

typedef struct TipoPagina
{
    short n; //quantidade de posições dentro do vetor r
    TipoRegistro r[2*M];
    TipoApontador p[2*M + 1];
}TipoPagina;


typedef struct TipoDadosRecolhidos
{
    int numeroDeAcessos;
    int numeroDeComparacoes;
    double tempoDecorrido;
    TipoRegistro itemRetornado;
}TipoDadosRecolhidos;

typedef struct TipoEntradaTerminal
{
    int metodoDePesquisa;
    int quantidadeDeRegistros;
    int situacaoDoArquivo;
    int chaveDesejada;
    int argOpcional;
}TipoEntradaTerminal;

typedef struct TipoIndice
{
    int chave;
}TipoIndice;

typedef struct TipoPagina* TipoApontador;

typedef int TipoChave;

//Funcoes do gerador 
void geradorMain(TipoEntradaTerminal);
void gerarArquivoCrescente(int);
void gerarArquivoDecrescente(int);
void gerarArquivoDesordenado(int);

//Funcoes pesquisa sequencial indexada
int pesquisaBinaria(TipoRegistro [], TipoRegistro *, int , int );
int pesquisa(TipoIndice [], int , TipoRegistro* , FILE *, int);
void pesSeqInd(int,FILE*, int);
int verifica(int , char *[] );

//Funcoes da arvore binaria
void buscaBinariaMain(TipoEntradaTerminal, TipoDadosRecolhidos*);
void chamadaConvercao(TipoEntradaTerminal , TipoDadosRecolhidos* );
void converteArquivoParaBinario(FILE**, FILE**, TipoEntradaTerminal, TipoDadosRecolhidos*);
TipoRegistro localizaElementoNoArquivo(FILE** , TipoEntradaTerminal, TipoDadosRecolhidos*);

//Funcoes da arvore B
void arvB_main(int , FILE *, int, TipoDadosRecolhidos *, int pp);
void Inicializa(TipoApontador arvore);
int pesquisaArvB(TipoRegistro *x, TipoApontador ap, TipoDadosRecolhidos *analise);
void imprimir(TipoApontador arv);
void insere(TipoRegistro Reg, TipoApontador *ap);
void ins(TipoRegistro Reg, TipoApontador ap, short *cresceu, TipoRegistro *RegRetorno, TipoApontador *apRetorno);
void insereNaPag(TipoApontador ap, TipoRegistro Reg, TipoApontador apDir);
void limpaArvB(TipoApontador ap);

#endif