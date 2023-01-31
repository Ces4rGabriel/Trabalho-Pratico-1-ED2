#include "arv_B_estrela.h"
#include <stdlib.h>
#include <stdio.h>


short pesquisaBEstrela(TipoRegistroBE *x, TipoApontadorBE *Ap){
    int i = 1;
    TipoApontadorBE PageAtual;
    PageAtual = *Ap;

    if((*Ap)->Pt == Interna){
        while(i < PageAtual->UU.U0.ni && x->chave > PageAtual->UU.U0.ri[i-1].chave) i++;

        if(x->chave <= PageAtual->UU.U0.ri[i-1].chave)
            pesquisaBEstrela(x, &PageAtual->UU.U0.pi[i-1]);
        else
            pesquisaBEstrela(x, &PageAtual->UU.U0.pi[i]);

        return 1;
    }
    else{
        i = 1;

        while(i <= PageAtual->UU.U1.ne && x->chave > PageAtual->UU.U1.re[i-1].chave){
           // printf("Valor do i %d ", i);
           // printf("valor da chave %d\n", (*Ap)->UU.U1.re[i-1].chave);
            i++;
        }
        
        //printf("Comparando a buscada: %d com  a encontrada: %d\n", x->chave, (*Ap)->UU.U1.re[i-1].chave);
        if(x->chave == PageAtual->UU.U1.re[i-1].chave){
            (*x) = PageAtual->UU.U1.re[i-1];
            return 1;
        }
        else {
            //printf("Não achou nada\n");
            return 0;
        }
    }

}

void arvBE_main(int chave, FILE *arq, int qtd_limite, int pp){
    TipoApontadorBE arvore;
    TipoRegistroBE reg;
    TipoRegistroBE item;
    item.chave = chave;
    InicializaBE(&arvore);


    for (int i = 0; i < qtd_limite; i++)
    {
        fread(&reg, sizeof(TipoRegistroBE), 1, arq);
        InsereNaPagina(&arvore, reg);
    }

   //imprimeExterna(arvore);

    if(pesquisaBEstrela(&item, &arvore)){
        if (pp == 1)
            printf("\nEncontrado o item de chave %d\n registro_1: %ld\n registro_2: %s\n", item.chave, item.dado1,item.dado2);
    }else{
        printf("\nNao encontrado o item de chave %d\n", item.chave);
    }
}

void InicializaBE(TipoApontadorBE *arvore){
    (*arvore) = NULL;
}


void insereInterna(TipoApontadorBE Ap, TipoChaveBS Chave, TipoApontadorBE ApDir){
    int i;
    i = Ap->UU.U0.ni;
    int TemEspaco;
    TemEspaco = (i > 0);

    while(TemEspaco){
        if(Chave >= Ap->UU.U0.ri[i-1].chave){
            TemEspaco = 0;
            break;
        }

        Ap->UU.U0.ri[i].chave = Ap->UU.U0.ri[i-1].chave;
        Ap->UU.U0.pi[i+1] = Ap->UU.U0.pi[i];
        i--;
        if(i < 1) TemEspaco = 0;
    }

    //printf("CHAVE INSERIDA INTERNA  \n Chave: %d\n", Chave);

    Ap->UU.U0.ri[i].chave = Chave;
    Ap->UU.U0.pi[i+1] = ApDir;
    Ap->UU.U0.ni++;
}

void InserenaFolha(TipoRegistroBE reg, TipoApontadorBE Ap) {
    int i;
    i = Ap->UU.U1.ne;
    int TemEspaco;
    TemEspaco = (i > 0);

    while(TemEspaco){
        if(reg.chave >= Ap->UU.U1.re[i - 1].chave){
            TemEspaco = 0;
            break;
        }
        
        Ap->UU.U1.re[i] = Ap->UU.U1.re[i-1];
        i--;
        if(i < 1) TemEspaco = 0;
    }  

    //printf("VALORES INSERIDOS NA FOLHA \n Chave: %d\n Dado1: %ld\n Dado2: %s\n", reg->chave, reg->dado1, reg->dado2);

    Ap->UU.U1.re[i] = reg;
    Ap->UU.U1.ne++;
}

void bstar_Ins(TipoRegistroBE reg, TipoApontadorBE Ap, short *Cresceu, TipoRegistroBE *RegRetorno, TipoApontadorBE *ApRetorno) {
    long i = 1;
    long j;
    TipoApontadorBE ApTemp;
    //TipoApontadorBE new = NULL;
    //TipoRegistroBE Aux;

    if (Ap == NULL) {
        (*Cresceu) = 1;
        (*RegRetorno) = reg;
        (*ApRetorno) = NULL;

        //aloca aptemp
        /*ApTemp = (TipoPaginaBE *)malloc(sizeof(TipoPaginaBE));
        ApTemp->Pt = Externa;
        ApTemp->UU.U1.ne = 1;
        ApTemp->UU.U1.re[0] = reg;*/

        /*(*ApRetorno) = ApTemp;*/

        //free(ApTemp);
        return;
    }
   
    if(Ap->Pt == Interna){
        //(*RegRetorno) = reg;

        //if(reg.chave == 100)
        //printf("CHAVE INSERIDA NA arvInterna %d\n", RegRetorno->chave);
        //printf("Dado 1 inserido na arvInterna %ld\n", RegRetorno->dado1);
        //printf("Dado 2 inserido na arvInterna %s\n", RegRetorno->dado2);
        //printf("NUMERO DE ELEMENTOS NA ARVORE INTERNA %d\n", Ap->UU.U0.ni);

        while(i < Ap->UU.U0.ni && reg.chave > Ap->UU.U0.ri[i-1].chave){
            i++;
        }

        if(reg.chave < Ap->UU.U0.ri[i-1].chave){
            i--;
        }

        bstar_Ins(reg, Ap->UU.U0.pi[i], Cresceu, RegRetorno, ApRetorno);

       // printf("Resultado não cresceu %d\n", !(*Cresceu));
        if(!*Cresceu){
            return;
        }

        if(Ap->UU.U0.ni < MM2){
            //printf("Entrou aqui 3\n");
            insereInterna(Ap, RegRetorno->chave, *ApRetorno);
            (*Cresceu) = 0;
            return;
        }

        //Overflow: Pagina a ser dividida

        ApTemp = (TipoApontadorBE)malloc(sizeof(TipoPaginaBE));
        ApTemp->Pt = Interna;
        ApTemp->UU.U0.ni = 0;
        ApTemp->UU.U0.pi[0] = NULL;

        if(i < MM+1){
            insereInterna(ApTemp, Ap->UU.U0.ri[MM2-1].chave, Ap->UU.U0.pi[MM2]);
            Ap->UU.U0.ni--;
            insereInterna(Ap, RegRetorno->chave, *ApRetorno);
        }else {
            insereInterna(ApTemp, RegRetorno->chave, *ApRetorno);
        }

        for(j = MM + 2; j <= MM2; j++){
            insereInterna(ApTemp, Ap->UU.U0.ri[j-1].chave, Ap->UU.U0.pi[j]);
        }

        Ap->UU.U0.ni = MM;
        ApTemp->UU.U0.pi[0] = Ap->UU.U0.pi[MM+1];
        (*RegRetorno).chave = Ap->UU.U0.ri[MM].chave;
        (*ApRetorno) = ApTemp;

        return;
    }
    else{
        (*RegRetorno)  = reg;

        while(i < Ap->UU.U1.ne && reg.chave > Ap->UU.U1.re[i-1].chave) i++;

        if(reg.chave == Ap->UU.U1.re[i-1].chave && Ap->UU.U1.ne != 0){
            //printf("Erro: Registro ja esta presente\n");
            (*Cresceu) = 0;
            return;
        }

        if(!*Cresceu){
            return;
        }

        if(Ap->UU.U1.ne < MM2){
            InserenaFolha(*RegRetorno, Ap);
           (*Cresceu) = 0;
            return;
        }


        //criando nova página Overflow
        ApTemp = (TipoApontadorBE)malloc(sizeof(TipoPaginaBE));
        ApTemp->Pt = Externa;
        ApTemp->UU.U1.ne = 0;
        
        //Se o registro for menor ficará na página que já existe
        //Se não irá ir para a nova página criada

        if(i < MM+1){
            InserenaFolha(Ap->UU.U1.re[MM2-1], ApTemp);
            Ap->UU.U1.ne--;
            InserenaFolha(*RegRetorno, Ap);
        }else {
            InserenaFolha(*RegRetorno, ApTemp);
        }


        for(j = MM+2; j <= MM2; j++){
            InserenaFolha(Ap->UU.U1.re[j-1], ApTemp);
        }

        Ap->UU.U1.ne = MM + 1;
        
        
        (*RegRetorno) = Ap->UU.U1.re[MM];
        (*ApRetorno) = ApTemp;
    }
}


void InsereNaPagina(TipoApontadorBE *Ap, TipoRegistroBE Reg) {
    TipoPaginaBE *ApTemp;
    TipoPaginaBE *apRetorno;
    short cresceu;
    cresceu = 1;
    TipoRegistroBE RegRetorno;

    if(*Ap == NULL){
        ApTemp = (TipoPaginaBE*)malloc(sizeof(TipoPaginaBE));
        ApTemp->Pt = Externa;
        ApTemp->UU.U1.ne = 0;
        ApTemp->UU.U1.re[0] = Reg;
        *Ap = ApTemp;
    }

    bstar_Ins(Reg, *Ap, &cresceu, &RegRetorno, &apRetorno);

    if(cresceu){
        ApTemp = (TipoPaginaBE*)malloc(sizeof(TipoPaginaBE));
        ApTemp->Pt = Interna;
        ApTemp->UU.U0.ni = 1;
        ApTemp->UU.U0.ri[0].chave = RegRetorno.chave;
        ApTemp->UU.U0.pi[1] = apRetorno;
        ApTemp->UU.U0.pi[0] = *Ap;
        *Ap = ApTemp;
    }
}

void imprimeExterna(TipoApontadorBE arv){
    while (arv->UU.U1.re->chave != 80)
    {
        if(arv->Pt != Externa){
            printf("Interno:\n");

            for(int i = 0; i < arv->UU.U1.ne; i++){
                printf("%d ", arv->UU.U0.ri[i].chave);
            }
            printf("--\n");

            for(int i = 0; i < arv->UU.U0.ni+1; i++){ 
                imprimeExterna(arv->UU.U0.pi[i]);
                
            }
            return;
        }
        else{
            printf("Externo:\n");

            for(int i = 0; i < arv->UU.U1.ne; i++){
                printf("%d ", arv->UU.U1.re[i].chave);
            }
            printf("\n");
            return;
        }
        /* code */
    }
    
}



