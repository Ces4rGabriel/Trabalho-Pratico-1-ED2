#include "arv_B.h"

void arvB_main(int chave, FILE *arq, int qtd_limite, Analis *analise, int pp){
    rewind(arq);
    Analis a;
    a.comparacoes = 0;
    a.comparacoesC = 0;
    TipoApontador arvore = NULL;
    TipoRegistro reg, item;
    item.chave = chave;
    int cont = 1;

    //inicializar a arvore
    clock_t inicioC = clock();
    Inicializa(arvore);
    //criar a arvore com os registros do arquivo e considerando a quantidade limite
    while(fread(&reg, sizeof(TipoRegistro), 1, arq)&& cont < qtd_limite){
        cont++;
        insere(reg, &arvore, &a);
    }
    printf("Comparaçoes: %d\n", a.comparacoesC);
    clock_t fimC = clock();
    analise->tempoC = (double)(fimC - inicioC) / CLOCKS_PER_SEC; //tempo de criacao
    analise->nTransferencias = cont;
    analise->criacao = cont;

    //pesquisar a chave
    clock_t inicio = clock();
    if(pesquisaArvB(&item, arvore, &a)){
        if (pp == 1)
            printf("\nEncontrado o item de chave %d\n registro_1: %ld\n registro_2: %s\n", item.chave, item.dado1,item.dado2);
    }
    else{
        if (pp == 1)
            printf("\nNao encontrado o item de chave %d\n", item.chave);
    }
    //limpa a memoria alocada
    limpaArvB(arvore);
    clock_t fim = clock();
    analise->tempo = (double)(fim - inicio) / CLOCKS_PER_SEC; 
    analise->comparacoes = a.comparacoes;
    analise->comparacoesC = a.comparacoesC;
    
}

//inicializar a arvore
void Inicializa(TipoApontador arvore){
    arvore = NULL;
}

void insere(TipoRegistro Reg, TipoApontador *ap, Analis *a){
    short cresceu;
    TipoRegistro RegRetorno;
    TipoPagina *apRetorno;
    TipoPagina *apTemp;

    ins(Reg, *ap, &cresceu, &RegRetorno, &apRetorno, a);

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

void ins(TipoRegistro Reg, TipoApontador ap, short *cresceu, TipoRegistro *RegRetorno, TipoApontador *apRetorno, Analis *a){
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
    while (i < ap->n && Reg.chave > ap->r[i-1].chave){
        i++;
        a->comparacoesC++;
    }
        

    //verifica se a chave é igual a chave do registro
    if(Reg.chave == ap->r[i-1].chave)
    {
        printf("Erro: Registro ja esta presente\n");
        *cresceu = 0;
        a->comparacoesC++;
        return;
    }

    //verifica se a chave é menor que a chave do registro
    if(Reg.chave < ap->r[i-1].chave){
        i--;
        a->comparacoesC++;
    }
        
    ins(Reg, ap->p[i], cresceu, RegRetorno, apRetorno, a);

    //verifica se a pagina não cresceu
    if (!*cresceu)
        return;
    
    //verifica se a pagina tem espaço para inserir o registro
    if(ap->n < 2*M){
        insereNaPag(ap, *RegRetorno, *apRetorno, a);
        *cresceu = 0;
        return;
    }
    //overflow - criando nova pagina
    apTemp = (TipoApontador) malloc (sizeof(TipoPagina));
    apTemp->n = 0;
    apTemp->p[0] = NULL;

    //Escolhe a pagina que o item será inserido
    if(i < M + 1){
        insereNaPag(apTemp, ap->r[2*M-1], ap->p[2*M], a); // muda o ultimo item de pagina
        ap->n--; 
        insereNaPag(ap, *RegRetorno, *apRetorno, a); //insere na pagina corrente
    }
    else
        insereNaPag(apTemp, *RegRetorno, *apRetorno, a); //insere na nova pagina

    for(j = M + 2; j <= 2*M; j++)
        insereNaPag(apTemp, ap->r[j-1], ap->p[j], a);
    
    //atualiza a pagina
    ap->n = M;
    apTemp->p[0] = ap->p[M+1];

    //retorna o registro e a pagina
    *RegRetorno = ap->r[M];
    *apRetorno = apTemp;

}
void insereNaPag(TipoApontador ap, TipoRegistro Reg, TipoApontador apDir, Analis *a){
    short naoAchouPosicao;
    int k;
    k = ap->n;
    naoAchouPosicao = (k > 0);

    //verifica se a pagina tem espaço para inserir o registro
    while (naoAchouPosicao){
        //verifica se a chave é menor que a chave do registro
        if(Reg.chave >= ap->r[k-1].chave){
            a->comparacoesC++;
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

int pesquisaArvB(TipoRegistro *x, TipoApontador ap, Analis *analise){
    long i = 1;
    if (ap == NULL){
        return 0;  
    }
    //pesquisa sequencial para encontrar o intervalo
    while (i < ap->n && x->chave > ap->r[i-1].chave){
        analise->comparacoes++;
        i++;
    }
    if (x->chave == ap->r[i-1].chave){ //verifica se a chave é igual a chave do registro
        *x = ap->r[i-1]; //se for igual, o registro é retornado
        analise->comparacoes++;
        return 1;
    }
    if(x->chave < ap->r[i-1].chave){
        analise->comparacoes++;
        return pesquisaArvB(x, ap->p[i-1], analise);
    }
    else{
        analise->comparacoes++;
        return pesquisaArvB(x, ap->p[i], analise);
    }   
}

void imprimir(TipoApontador arv){
    int i;
    if(arv == NULL)
        return;
    //percorre todos os filhos recursivamente
    for(i = 0; i < arv->n; i++){
        imprimir(arv->p[i]);
        printf("%d %ld %s\n", arv->r[i].chave, arv->r[i].dado1, arv->r[i].dado2);
    }
    //imprime a raiz
    imprimir(arv->p[i]);
}

void limpaArvB(TipoApontador ap){
    long i;
    if (ap == NULL)
        return;
    //percorre todos os filhos recursivamente
    for (i = 0; i < ap->n+1; i++)
        limpaArvB(ap->p[i]);
    //libera a memória alocada para a raiz
    free(ap);
}
