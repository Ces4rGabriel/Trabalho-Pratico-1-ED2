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

//inicializar a arvore
void Inicializa(TipoApontador arvore){
    arvore = NULL;
}

int pesquisa(TipoRegistro *x, TipoApontador ap){
    long i = 1;

    if (ap == NULL){
        return;  
    }
    //pesquisa sequencial para encontrar o intervalo (MUDAR PARA BINARIA!!!!!!!)
    while (i < ap->n && x->chave > ap->r[i-1].chave)
        i++;
    if (x->chave == ap->r[i-1].chave){ //verifica se a chave é igual a chave do registro
        *x = ap->r[i-1]; //se for igual, o registro é retornado
        return 0;
    }
    if(x->chave < ap->r[i-1].chave)
        pesquisa(x, ap->p[i-1]);
    else
        pesquisa(x, ap->p[i]);
}

void imprimir1(TipoApontador arv){
    int i;
    if(arv == NULL)
        return;
    for(i = 0; i < arv->n; i++){
        imprimir(arv->p[i]);
        printf("%ld ", arv->r[i].chave);
    }
    imprimir(arv->p[i]);
}

void imprimir2(TipoApontador arv){
    int i = 0;
    if(arv == NULL)
        return;

    while (i <= arv->n){
        imprimir(arv->p[i]);
        if(i != arv->n)
            printf("%ld ", arv->r[i].chave);
        i++;
    }
}

void insere(TipoRegistro Reg, TipoApontador *ap){
    short cresceu;
    TipoRegistro RegRetorno;
    TipoPagina *apRetorno;
    TipoPagina *apTemp;

    ins(Reg, *ap, &cresceu, &RegRetorno, &apRetorno);
    if(cresceu){
        apTemp = (TipoPagina*)malloc(sizeof(TipoPagina));
        apTemp->n = 1;
        apTemp->r[0] = RegRetorno;
        apTemp->p[1] = apRetorno;
        apTemp->p[0] = *ap;
        *ap = apTemp;
    }
}

void ins(TipoRegistro Reg, TipoApontador ap, short *cresceu, TipoRegistro *RegRetorno, TipoApontador *apRetorno){
    long i = 1;
    long j;
    TipoApontador apTemp;

    //verifica se a pagina é folha ou arvore vazia
    if (ap == NULL){
        *cresceu = 1;
        (*RegRetorno) = Reg;
        (*apRetorno) = NULL;
        return;
    }

    //pesquisa sequencial para encontrar o intervalo
    while (i < ap->n && Reg.chave > ap->r[i-1].chave)
        i++;

    //verifica se a chave é igual a chave do registro
    if(Reg.chave == ap->r[i-1].chave)
    {
        printf("Erro: Registro ja esta presente\n");
        *cresceu = 0;
        return;
    }

    //verifica se a chave é menor que a chave do registro
    if(Reg.chave < ap->r[i-1].chave)
        i--;
    ins(Reg, ap->p[i], cresceu, RegRetorno, apRetorno);

    //verifica se a pagina não cresceu
    if (!*cresceu)
        return;
    
    //verifica se a pagina tem espaço para inserir o registro
    if(ap->n < 2*M){
        insereNaPag(ap, *RegRetorno, *apRetorno);
        *cresceu = 0;
        return;
    }
    

}

int insereNaPag(TipoApontador ap, TipoRegistro Reg, TipoApontador apDir){

}