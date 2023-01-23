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

int main(){
    TipoApontador arvore = NULL;
    TipoRegistro reg;
    reg.chave = 1;
    Inicializa(arvore);
    insere(reg, &arvore);
    reg.chave = 5;
    insere(reg, &arvore);
    imprimir1(arvore);
    return 0;
}

//inicializar a arvore
void Inicializa(TipoApontador arvore){
    arvore = NULL;
}

void insere(TipoRegistro Reg, TipoApontador *ap){
    short cresceu;
    TipoRegistro RegRetorno;
    TipoPagina *apRetorno;
    TipoPagina *apTemp;

    ins(Reg, *ap, &cresceu, &RegRetorno, &apRetorno);

    //verifica se a pagina cresceu e cria uma nova pagina raiz
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
    //overflow - criando nova pagina
    apTemp = (TipoApontador) malloc (sizeof(TipoPagina));
    apTemp->n = 0;
    apTemp->p[0] = NULL;

    //Escolhe a pagina que o item será inserido
    if(i < M + 1){
        insereNaPag(apTemp, ap->r[2*M-1], ap->p[2*M]); // muda o ultimo item de pagina
        ap->n--; 
        insereNaPag(ap, *RegRetorno, *apRetorno); //insere na pagina corrente
    }
    else
        insereNaPag(apTemp, *RegRetorno, *apRetorno); //insere na nova pagina

    for(j = M + 2; j <= 2*M; j++)
        insereNaPag(apTemp, ap->r[j-1], ap->p[j]);
    
    //atualiza a pagina
    ap->n = M;
    apTemp->p[0] = ap->p[M+1];

    //retorna o registro e a pagina
    *RegRetorno = ap->r[M];
    *apRetorno = apTemp;

}

void insereNaPag(TipoApontador ap, TipoRegistro Reg, TipoApontador apDir){
    short naoAchouPosicao;
    int k;
    k = ap->n;
    naoAchouPosicao = (k > 0);

    //verifica se a pagina tem espaço para inserir o registro
    while (naoAchouPosicao){
        //verifica se a chave é menor que a chave do registro
        if(Reg.chave >= ap->r[k-1].chave){
            naoAchouPosicao = 0;
            break;
        }
        //arrasta os registros para a direita
        ap->r[k] = ap->r[k-1]; //
        ap->p[k+1] = ap->p[k];
        k--;
        if(k < 1)
            naoAchouPosicao = 0;
    }
    //insere o registro na pagina
    ap->r[k] = Reg;
    ap->p[k+1] = apDir;
    ap->n++;

}


int pesquisa(TipoRegistro *x, TipoApontador ap){
    long i = 1;

    if (ap == NULL){
        return 0;  
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
    return 0;
}

void imprimir1(TipoApontador arv){
    int i;
    if(arv == NULL)
        return;
    for(i = 0; i < arv->n; i++){
        imprimir1(arv->p[i]);
        printf("%ld ", arv->r[i].chave);
    }
    imprimir1(arv->p[i]);
}

void imprimir2(TipoApontador arv){
    int i = 0;
    if(arv == NULL)
        return;

    while (i <= arv->n){
        imprimir2(arv->p[i]);
        if(i != arv->n)
            printf("%ld ", arv->r[i].chave);
        i++;
    }
}
