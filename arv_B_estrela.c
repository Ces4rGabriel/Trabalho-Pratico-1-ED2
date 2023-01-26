#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MM 3
#define MM2 2*MM

typedef long TipoChave;
typedef struct TipoRegistro {
TipoChave Chave;
/* outros componentes */
} TipoRegistro;

typedef enum {Interna, Externa} TipoIntExt;
typedef struct TipoPagina* TipoApontador;

typedef struct TipoPagina {
    TipoIntExt Pt;
    union {
        struct {
            int ni;
            TipoChave ri[MM];
            TipoApontador pi[MM + 1];
        }U0;
        struct {
            int ne;
            TipoRegistro re[MM2];
        }U1;
    }UU;
} TipoPagina;

void pesquisa(TipoRegistro *x, TipoApontador *Ap){
    int i;
    TipoApontador Pag;
    Pag = *Ap;
    if((*Ap)->Pt == Interna){
        i = 1;
        while(i < Pag->UU.U0.ni && x->Chave > Pag->UU.U0.ri[i-1])
            i++;
        if(x->Chave == Pag->UU.U0.ri[i-1])
        pesquisa(x, &Pag->UU.U0.pi[i-1]);
        else pesquisa(x, &Pag->UU.U0.pi[i-1]);
        return;
    }
    i = 1;
    while(i < Pag->UU.U1.ne && x->Chave > Pag->UU.U1.re[i-1].Chave)
        i++;
    if(x->Chave == Pag->UU.U1.re[i-1].Chave){
        *x = Pag->UU.U1.re[i-1];
    }
    else{
        printf("Registro nao esta presente na arvore\n");
    }

}

