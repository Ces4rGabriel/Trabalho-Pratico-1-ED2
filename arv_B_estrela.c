#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MM 3
#define MM2 2*MM

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
            TipoChave ri[MM2];
            TipoApontador pi[MM2 + 1];
        }U0;
        struct {
            int ne;
            TipoRegistro re[MM2];
        }U1;
    }UU;
} TipoPagina;

void arvB_main(int chave, FILE *arq, int qtd_limite){
    TipoApontador arvore = NULL;
    TipoRegistro reg, item;
    item.chave = chave;
    int cont = 0;
    //inicializar a arvore
    Inicializa(arvore);

    //criar a arvore com os registros do arquivo e considerando a quantidade limite
    while(fread(&reg, sizeof(TipoRegistro), 1, arq)&& cont < qtd_limite){
        cont++;
        bstar_Insere(reg, &arvore);
    }

    //pesquisar a chave
    if(pesquisaArvB(&item, arvore))
        printf("\nEncontrado o item de chave %d\n registro_1: %ld\n registro_2: %s\n", item.chave, item.dado1,item.dado2);
    else
        printf("\nNao encontrado o item de chave %d\n", item.chave);

}

void Inicializa(TipoApontador arvore){
    arvore = NULL;
}

void pesquisa_B(TipoRegistro *x, TipoApontador *Ap){
    int i;
    TipoApontador Pag;
    Pag = *Ap;
    if((*Ap)->Pt == Interna){
        i = 1;
        while(i < Pag->UU.U0.ni && x->chave > Pag->UU.U0.ri[i-1])
            i++;
        if(x->chave == Pag->UU.U0.ri[i-1])
        pesquisa(x, &Pag->UU.U0.pi[i-1]);
        else pesquisa(x, &Pag->UU.U0.pi[i-1]);
        return;
    }
    i = 1;
    while(i < Pag->UU.U1.ne && x->chave > Pag->UU.U1.re[i-1].chave)
        i++;
    if(x->chave == Pag->UU.U1.re[i-1].chave){
        *x = Pag->UU.U1.re[i-1];
    }
    else{
        printf("Registro nao esta presente na arvore\n");
    }

}
void bstar_Insere(TipoRegistro reg, TipoApontador *Ap) {
    short Cresceu;
    TipoRegistro RegRetorno;
    TipoPagina *ApRetorno, *ApTemp;
    bstar_Ins(reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);

    if (Cresceu) { /* Arvore cresce na altura pela raiz */
        ApTemp = (TipoPagina *)malloc(sizeof(TipoPagina));

        if(ApRetorno == NULL) {
            ApTemp->Pt = Externa;
            ApTemp->UU.U1.ne = 1;
            ApTemp->UU.U1.re[0] = RegRetorno;
            ApTemp->UU.U0.pi[1] = ApRetorno;
            ApTemp->UU.U0.pi[0] = *Ap;
        }
        else {
            ApTemp->Pt = Interna;
            ApTemp->UU.U0.ni = 1;
            ApTemp->UU.U0.ri[0] = RegRetorno.chave; //mudou (tirou o .chave)
            ApTemp->UU.U0.pi[1] = ApRetorno;
            ApTemp->UU.U0.pi[0] = *Ap;
        }

        *Ap = ApTemp;
    }
}

void bstar_Ins(TipoRegistro reg, TipoApontador Ap, short *Cresceu, TipoRegistro *RegRetorno, TipoApontador *ApRetorno) {
    long i = 1;
    long j;
    TipoApontador ApTemp;

    if (Ap == NULL) {
        *Cresceu = 1;
        (*RegRetorno) = reg;
        (*ApRetorno) = NULL;
        return;
    }

    while (i < Ap->UU.U0.ni && reg.chave > Ap->UU.U0.ri[i - 1]) i++;

    // Isso não vai acontecer por causa do conteúdo ser gerado sem repetição
    if (reg.chave == Ap->UU.U0.ri[i - 1]) {
        // printf("ERRO: Registro já existente\n");
        // teste // bstar_InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
        *Cresceu = 0;
        Ap->Pt = Interna;
        return;
    }

    if (reg.chave < Ap->UU.U0.ri[i - 1]) i--;
	
    bstar_Ins(reg, Ap->UU.U0.pi[i], Cresceu, RegRetorno, ApRetorno);

    if (!*Cresceu) 
		return;

    if (Ap->UU.U0.ni < MM2) { /* Página tem Espaço */
        bstar_InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
        printf("%s \n\n", Ap->Pt == Interna ? "Interna" : "Externa");
        *Cresceu = 0;
        return;
    }

    /* Overflow: Página tem que ser dividida */
    ApTemp = malloc(sizeof(TipoPagina));
    ApTemp->UU.U0.ni = 0;
    ApTemp->UU.U0.pi[0] = NULL;

    if (i < MM + 1) {
        bstar_InsereNaPagina(ApTemp, Ap->UU.U0.ri[MM2 - 1].chave, Ap->UU.U0.pi[MM]);
        printf("Registro %d adicionada na página dividida.\n", RegRetorno->chave);
        Ap->UU.U0.ni--;
        bstar_InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
    } else
        bstar_InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);

    for (j = MM + 2; j <= MM2; j++) 
		bstar_InsereNaPagina(ApTemp, Ap->UU.U0.ri[j - 1].chave, Ap->UU.U0.pi[j]);

    Ap->UU.U1.ne = MM;
    ApTemp->UU.U0.pi[0] = Ap->UU.U0.pi[MM + 1];
    (*RegRetorno).chave = Ap->UU.U0.ri[MM];
    *ApRetorno = ApTemp;
}

void bstar_InsereNaPagina(TipoApontador Ap, TipoRegistro Reg, TipoApontador ApDir) {
    int k = Ap->UU.U1.ne;
    short NaoAchouPosicao = (k > 0);

    while (NaoAchouPosicao) {
        if (Reg.chave >= Ap->UU.U1.re[k - 1].chave) {
            NaoAchouPosicao = 0;
            break;
        }
        Ap->UU.U1.re[k] = Ap->UU.U1.re[k - 1];
        Ap->UU.U0.pi[k + 1] = Ap->UU.U0.pi[k];
        k--;
        if (k < 1) NaoAchouPosicao = 0;
    }

    Ap->UU.U1.re[k] = Reg;
    Ap->UU.U0.pi[k + 1] = ApDir;
    Ap->UU.U1.ne++;
    // Ap->PT=Externa;
    escreverValor(&Ap);
}

void escreverValor(TipoApontador *Ap) {
    printf("PT: %s\n", (*Ap)->Pt == Interna ? "Interna" : "Externa");
    if ((*Ap)->Pt == Interna) {
        for (int i = 0; i < (*Ap)->UU.U0.ni; ++i) {
            printf("Codigo: %d\n", (*Ap)->UU.U0.ri[i]);
        }
    } else {
        for (int i = 0; i < (*Ap)->UU.U1.ne; ++i) {
            printf("Codigo: %d\n", (*Ap)->UU.U1.re[i].chave);
        }
    }
}

