#include "arv_B_estrela.h"

#define f(inicio,fim) for(int i =inicio ; i<fim; i++)

int pesquisa_BS(TipoRegistroBE *x, TipoApontadorBE *Ap){
    int i;

    if((*Ap)->Pt == Interna){
        i = 1;
        while(i < (*Ap)->UU.U0.ni && x->chave > (*Ap)->UU.U0.ri[i-1].chave)
            i++;
    

    if(x->chave < (*Ap)->UU.U0.ri[i-1].chave)
        pesquisa_BS(x, &(*Ap)->UU.U0.pi[i-1]);
    else
        pesquisa_BS(x, &(*Ap)->UU.U0.pi[i]);
    }

    i = 1;
    while(i < (*Ap)->UU.U1.ne && x->chave > (*Ap)->UU.U1.re[i-1].chave)
        i++;
    
    if(x->chave == (*Ap)->UU.U1.re[i-1].chave){
        x->chave = (*Ap)->UU.U1.re->chave;
        x->dado1 = (*Ap)->UU.U1.re->dado1;
        strcpy(x->dado2, (*Ap)->UU.U1.re->dado2);

        return 1;
    }else {
        x->chave = -1;
        return 0;
    }
}

void arvBE_main(int chave, FILE *arq, int qtd_limite){
    TipoApontadorBE arvore = NULL;
    TipoRegistroBE reg, item;
    item.chave = chave;
    int cont = 0;
    //inicializar a arvore
    InicializaBE(arvore);
    printf("chegou\n");
    //criar a arvore com os registros do arquivo e considerando a quantidade limite
    while(fread(&reg, sizeof(TipoRegistroBE), 1, arq) && cont < qtd_limite){
        printf("inseroi %d\n", cont);
        cont++;
        bstar_Insere(reg, &arvore);
        
    }
    //bstar_Imprime(arvore);
    
    if(pesquisa_BS(&item, &arvore))
        printf("\nEncontrado o item de chave %d\n registro_1: %ld\n registro_2: %s\n", item.chave, item.dado1,item.dado2);
    else
        printf("\nNao encontrado o item de chave %d\n", item.chave);

}

void InicializaBE(TipoApontadorBE arvore){
    arvore = NULL;
}

void bstar_Insere(TipoRegistroBE reg, TipoApontadorBE *Ap) {
    short Cresceu = 0;
    short CresceuNo = 0;
    TipoRegistroBE RegRetorno;
    TipoPaginaBE *ApRetorno, *ApTemp;
    ApRetorno = ApTemp = NULL;
    int newArvore = 0;
    //bstar_Ins(reg, *Ap, &Cresceu, &RegRetorno, &ApRetorno);

    if(*Ap == NULL) {
        ApTemp = (TipoPaginaBE *)malloc(sizeof(TipoPaginaBE));
        ApTemp->Pt = Externa;
        ApTemp->UU.U1.ne = 0;
        ApTemp->UU.U1.prox = NULL;

        printf("Entrou aqui\n");
        InserenaFolha(&reg, ApTemp);
        *Ap = ApTemp;

        return;
    }else{
        if((*Ap)->Pt == Externa)
            newArvore = 1;
        printf("Erro \n");
        bstar_Ins(reg, *Ap, &Cresceu, &CresceuNo, &RegRetorno, &ApRetorno);
    }

        if ((CresceuNo && newArvore) || Cresceu) {  //Arvore cresce na altura pela raiz 
        ApTemp = (TipoPaginaBE *)malloc(sizeof(TipoPaginaBE));

        ApTemp->Pt = Interna;

        ApTemp->UU.U0.ni = 1;
        ApTemp->UU.U0.ri[0].chave = RegRetorno.chave;

        ApTemp->UU.U0.pi[0] = *Ap;
        ApTemp->UU.U0.pi[1] = ApRetorno;


        /*if(ApRetorno == NULL) {
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
        }*/
        *Ap = ApTemp;
        free(ApTemp);
        
        return;
    }
}

int InserenaFolha(TipoRegistroBE *reg, TipoApontadorBE newPage) {
    int nmrItens = newPage->UU.U1.ne;
    int i = 0;
    int k = 0;

    while(reg->chave > newPage->UU.U1.re[i].chave && i < nmrItens)
        i++;
    
    if(reg->chave == newPage->UU.U1.re[i].chave && nmrItens != 0)
        return 0;
    
    if(i < nmrItens){
        k = nmrItens;
        while (k >= 0 && k > i)
        {
            newPage->UU.U1.re[k] = newPage->UU.U1.re[k-1];
            k--;
        }
        
        newPage->UU.U1.re[i] = *reg; //insere na posicao i
    } else {
        newPage->UU.U1.re[i] = *reg; //insere no final
    }
    newPage->UU.U1.ne++;

    return 1;
}

void bstar_Ins(TipoRegistroBE reg, TipoApontadorBE Ap, short *Cresceu, short *CresceuNo, TipoRegistroBE *RegRetorno, TipoApontadorBE *ApRetorno) {
    long i = 1;
    long j;
    TipoApontadorBE ApTemp;
    TipoApontadorBE new = NULL;
    TipoRegistroBE Aux;

    /*if (Ap == NULL) {
        *Cresceu = 1;
        (*RegRetorno) = reg;
        (*ApRetorno) = NULL;
        return;
    }*/
    //printf("Entrou aqui 0\n");
    if(Ap->Pt == Externa){
        //erro aqui print
        //printf("Entrou aqui\n");

        //Se entrou quer dizer que chegou ao ultimo nivel
        //tentar inserir na página externa
        //verifica se tem espaço na página
        if(Ap->UU.U1.ne < MM2)
        {
            //print erro
            printf("Entrou aqui 2\n");
            InserenaFolha(&reg, Ap);
            *Cresceu = 0;
            *CresceuNo = 0;
            return;
        }
        else {
            //print erro
           //printf("Entrou aqui 3\n");
            new = malloc(sizeof(TipoApontadorBE));
            new->Pt = Externa;
            new->UU.U1.ne = 0;
            Aux = Ap->UU.U1.re[MM2-1];

            //coloca o ultimo elemento na página à direita
            InserenaFolha(&Aux, new);
            //decrementa o numero elemento na página a direita
            Ap->UU.U1.ne--;

            //insere o novo
            int inseriu = InserenaFolha(&reg, Ap);

            if(!inseriu){
                Ap->UU.U1.ne++;
                free(new);
                *Cresceu = 0;
                *CresceuNo = 0;
                return;
            }

            f((MM2/2), MM2){
                //print erro
                //printf("Entrou aqui 4\n");
                InserenaFolha(&(Ap->UU.U1.re[i]), new);
                Ap->UU.U1.ne--;
            }

            //A chave do primeiro elemento do novo vetor será o pai
            (*RegRetorno).chave = Ap->UU.U1.re[0].chave;
            (*ApRetorno) = new;
            Ap->UU.U1.prox = new;
            new->UU.U1.prox = NULL;

            //Após inserir na arvore o novo registro, a chave que precisa subir
            //para o nó pai precisa ser inserida na arvore
            reg.chave = new->UU.U1.re[0].chave;
            *CresceuNo = 1;
            return;
        }
    }else {
        //print erro
        //printf("Entrou aqui 5\n");
        //se a pagina for interna
        while(i < Ap->UU.U0.ni && reg.chave > Ap->UU.U0.ri[i-1].chave) i++; 
        
        if(reg.chave == Ap->UU.U0.ri[i-1].chave){
            *Cresceu = 0;
            *CresceuNo = 0;
            return;
        }

        if(reg.chave < Ap->UU.U0.ri[i-1].chave) i--;

        if(!*CresceuNo){
            bstar_Ins(reg, Ap->UU.U0.pi[i], Cresceu, CresceuNo, RegRetorno, ApRetorno);
        }

        if(!*CresceuNo && !*Cresceu){
            return;
        }

        if(Ap->UU.U0.ni < MM){
            bstar_InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
            *Cresceu = 0;
            *CresceuNo = 0;
            return;
        }

        ApTemp = (TipoApontadorBE)malloc(sizeof(TipoPaginaBE));
        ApTemp->Pt = Interna;
        ApTemp->UU.U0.ni = 0;
        ApTemp->UU.U0.pi[0] = NULL;

        if(i < MM / 2 + 1){
            bstar_InsereNaPagina(ApTemp, Ap->UU.U0.ri[MM-1], Ap->UU.U0.pi[MM]);
            Ap->UU.U0.ni--;
            bstar_InsereNaPagina(Ap, *RegRetorno, *ApRetorno);
        }
        else {
            bstar_InsereNaPagina(ApTemp, *RegRetorno, *ApRetorno);
        }

        for(j = MM / 2 + 2; j <= MM; j++){
            bstar_InsereNaPagina(ApTemp, Ap->UU.U0.ri[j-1], Ap->UU.U0.pi[j]);
        }

        Ap->UU.U0.ni = MM / 2;
        ApTemp->UU.U0.pi[0] = Ap->UU.U0.pi[MM / 2 + 1];

        *RegRetorno = Ap->UU.U0.ri[MM / 2];

        *ApRetorno = ApTemp;
        *Cresceu = 1;
        *CresceuNo = 0;
        return;
    }
}


void bstar_InsereNaPagina(TipoApontadorBE Ap, TipoRegistroBE Reg, TipoApontadorBE ApDir) {
    int k = Ap->UU.U0.ni;
    short NaoAchouPosicao = (k > 0);

    while (NaoAchouPosicao) {
        if (Reg.chave >= Ap->UU.U0.ri[k - 1].chave) {
            NaoAchouPosicao = 0;
            break;
        }

        Ap->UU.U0.ri[k].chave = Reg.chave;
        Ap->UU.U0.pi[k + 1] = Ap->UU.U0.pi[k];
        k--;
        if (k < 1) 
            NaoAchouPosicao = 0;
    }
    //achou posicao
    Ap->UU.U0.ri[k].chave = Reg.chave;
    Ap->UU.U0.pi[k + 1] = ApDir;
    Ap->UU.U0.ni++;
    return;
    //Ap->Pt=Externa;
    //escreverValor(&Ap);*/
}

void bstar_Imprime(TipoApontadorBE Ap){
    int i;
    TipoApontadorBE aux;

    if(Ap == NULL) return;

    if(Ap->Pt == Interna){
        while(i <= Ap->UU.U0.ni){
            bstar_Imprime(Ap->UU.U0.pi[i]);
            if(i != Ap->UU.U0.ni)
                printf("%d ", Ap->UU.U0.ri[i].chave);
            i++;
        }
        printf("\n");
    } else {
        aux = Ap;
        for(int j = 0; j < aux->UU.U1.ne; j++){
            printf("(%d) %d | ", j, aux->UU.U1.re[j].chave);
        }
        printf("\n"); 
    }
}


