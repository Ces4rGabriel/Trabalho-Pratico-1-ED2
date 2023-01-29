#include "arv_B_estrela.h"

int pesquisa_BS(TipoRegistroBE *x, TipoApontadorBE *Ap){
    int i;
    TipoApontadorBE Pag;
    Pag = *Ap;
    if((*Ap)->Pt == Interna){
        i = 1;
        while(i < Pag->UU.U0.ni && x->chave > Pag->UU.U0.ri[i-1].chave)
            i++;
        if(x->chave < Pag->UU.U0.ri[i-1].chave)
            pesquisa_BS(x, &Pag->UU.U0.pi[i-1]);
        else pesquisa_BS(x, &Pag->UU.U0.pi[i]);
        return 0;
    }
    i = 1;
    while(i < Pag->UU.U1.ne && x->chave > Pag->UU.U1.re[i-1].chave)
        i++;
    if(x->chave == Pag->UU.U1.re[i-1].chave){
        *x = Pag->UU.U1.re[i-1];
        return 1;
    }
    else{
        return 0;
    }
}
/*
int pesquisa_BS(TipoRegistroBE *x, TipoApontadorBE *Ap) {
    long i = 1;
    if (*Ap == NULL) return 0;

    while (i < (*Ap)->UU.U0.ni && x->chave > (*Ap)->UU.U0.ri[i - 1].chave) i++;

    if (x->chave == (*Ap)->UU.U0.ri[i - 1].chave) {
        *x = (*Ap)->UU.U0.ri[i - 1];
        return 1;
    }

    if (x->chave < (*Ap)->UU.U0.ri[i - 1].chave) i--;

    return pesquisa_BS(x, &(*Ap)->UU.U0.pi[i]);
}
*/
void arvBE_main(int chave, FILE *arq, int qtd_limite){
    TipoApontadorBE arvore = NULL;
    TipoRegistroBE reg, item;
    item.chave = chave;
    int cont = 0;
    //inicializar a arvore
    InicializaBE(arvore);
    //criar a arvore com os registros do arquivo e considerando a quantidade limite
    while(fread(&reg, sizeof(TipoRegistroBE), 1, arq)&& cont < qtd_limite){
        cont++;
        bstar_Insere(reg, &arvore);
    }
    bstar_Imprime(arvore);
    /*
    if(pesquisa_BS(&item, &arvore))
        printf("\nEncontrado o item de chave %d\n registro_1: %ld\n registro_2: %s\n", item.chave, item.dado1,item.dado2);
    else
        printf("\nNao encontrado o item de chave %d\n", item.chave);
*/
}

void InicializaBE(TipoApontadorBE arvore){
    arvore = NULL;
}

void bstar_Insere(TipoRegistroBE reg, TipoApontadorBE *Ap) {
    short Cresceu;
    TipoRegistroBE RegRetorno;
    TipoPaginaBE *ApRetorno, *ApTemp;
    bstar_Ins(reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);

    if (Cresceu) { /* Arvore cresce na altura pela raiz */
        ApTemp = (TipoPaginaBE *)malloc(sizeof(TipoPaginaBE));

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
            ApTemp->UU.U0.ri[0].chave = RegRetorno.chave; //mudou (tirou o .chave)
            ApTemp->UU.U0.pi[1] = ApRetorno;
            ApTemp->UU.U0.pi[0] = *Ap;
        }

        *Ap = ApTemp;
    }
}

void bstar_Ins(TipoRegistroBE reg, TipoApontadorBE Ap, short *Cresceu, TipoRegistroBE *RegRetorno, TipoApontadorBE *ApRetorno) {
    long i = 1;
    long j;
    TipoApontadorBE ApTemp;

    if (Ap == NULL) {
        *Cresceu = 1;
        (*RegRetorno) = reg;
        (*ApRetorno) = NULL;
        return;
    }

    while (i < Ap->UU.U0.ni && reg.chave > Ap->UU.U0.ri[i - 1].chave) i++;

    // Isso não vai acontecer por causa do conteúdo ser gerado sem repetição
    if (reg.chave == Ap->UU.U0.ri[i - 1].chave) {
        // printf("ERRO: Registro já existente\n");
        // teste // bstar_InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
        *Cresceu = 0;
        Ap->Pt = Interna;
        return;
    }

    if (reg.chave < Ap->UU.U0.ri[i - 1].chave) i--;
	
    bstar_Ins(reg, Ap->UU.U0.pi[i], Cresceu, RegRetorno, ApRetorno);

    if (!*Cresceu) 
		return;

    if (Ap->UU.U0.ni < MM2) { /* Página tem Espaço */
        bstar_InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
        //printf("%s \n\n", Ap->Pt == Interna ? "Interna" : "Externa");
        *Cresceu = 0;
        return;
    }

    /* Overflow: Página tem que ser dividida */
    ApTemp = malloc(sizeof(TipoPaginaBE));
    ApTemp->UU.U0.ni = 0;
    ApTemp->UU.U0.pi[0] = NULL;

    if (i < MM + 1) {
        bstar_InsereNaPagina(ApTemp, Ap->UU.U0.ri[MM2 - 1], Ap->UU.U0.pi[MM]);
        printf("Registro %d adicionada na página dividida.\n", RegRetorno->chave);
        Ap->UU.U0.ni--;
        bstar_InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
    } else
        bstar_InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);

    for (j = MM + 2; j <= MM2; j++) 
		bstar_InsereNaPagina(ApTemp, Ap->UU.U0.ri[j - 1], Ap->UU.U0.pi[j]);

    Ap->UU.U1.ne = MM;
    ApTemp->UU.U0.pi[0] = Ap->UU.U0.pi[MM + 1];
    (*RegRetorno).chave = Ap->UU.U0.ri[MM].chave;
    *ApRetorno = ApTemp;
}

void bstar_InsereNaPagina(TipoApontadorBE Ap, TipoRegistroBE Reg, TipoApontadorBE ApDir) {
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
    //Ap->Pt=Externa;
    //escreverValor(&Ap);
}

/*void escreverValor(TipoApontadorBE *Ap) {
    printf("PT: %s\n", (*Ap)->Pt == Interna ? "Interna" : "Externa");
    if ((*Ap)->Pt == Interna) {
        for (int i = 0; i < (*Ap)->UU.U0.ni; ++i) {
            printf("Codigo: %d\n", (*Ap)->UU.U0.ri[i].chave);
        }
    } else {
        for (int i = 0; i < (*Ap)->UU.U1.ne; ++i) {
            printf("Codigo: %d\n", (*Ap)->UU.U1.re[i].chave);
        }
    }
}*/

//imprimir chaves e registros da arvore B*
void bstar_Imprime(TipoApontadorBE Ap) {
    long i;
    if (Ap == NULL)
        return;

    if (Ap->Pt == Interna) {
        for (i = 0; i < Ap->UU.U0.ni; i++) {
            bstar_Imprime(Ap->UU.U0.pi[i]);
            printf("%d %ld %s Interna\n", Ap->UU.U0.ri[i].chave, Ap->UU.U0.ri[i].dado1, Ap->UU.U0.ri[i].dado2);
        }
        bstar_Imprime(Ap->UU.U0.pi[i]);
    }
    else 
        for (i = 0; i < Ap->UU.U1.ne; i++) 
            printf("%d %ld %s Externa\n", Ap->UU.U1.re[i].chave, Ap->UU.U1.re[i].dado1, Ap->UU.U1.re[i].dado2);
        
}
