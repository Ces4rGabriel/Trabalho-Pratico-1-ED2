#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pesquisa.h"

void pesSeqInd(int chave, FILE* arq, int qtd_limite, Analis * analise, int pp){
    rewind(arq);
    analise->nTransferencias = 0; analise->comparacoes = 0; analise->tempo = 0;
    TipoIndice tabela[MAXTABELA];
    TipoItem x[ITENSPAGINA];
    TipoItem item;
    int cont, cont_limite;
    cont_limite = 0;
    item.chave = chave; //chave a ser pesquisada
    //criar a tabela de indices
    cont = 0;
    clock_t inicioC = clock();
    while(fread(x, sizeof(TipoItem), ITENSPAGINA, arq) > 0 && cont_limite < qtd_limite){ //itenspagina = 1000
        tabela[cont].chave = x[0].chave; 
        cont_limite += ITENSPAGINA;
        cont++;
    }
    clock_t fimC = clock();
    analise->tempoC = (double)(fimC - inicioC) / CLOCKS_PER_SEC;
    analise->nTransferencias = cont;
    analise->criacao = cont_limite;

    //pesquisar
    clock_t inicio = clock();
    fseek(arq, 0, SEEK_SET);
    if(pesquisa(tabela, cont, &item, arq, qtd_limite, analise)){
        if(pp == 1)
            printf("\nEncontrado o item de chave %d\n registro_1: %ld\n registro_2: %s\n", item.chave, item.dado1,item.dado2);
    }
    else{
        if(pp == 1)
            printf("\nNao encontrado o item de chave %d\n", item.chave);
    }
    clock_t fim = clock();
    analise->tempo = (double)(fim - inicio) / CLOCKS_PER_SEC; 

}

//pesquisa binaria recursiva
int pesquisaBinaria(TipoItem x[], TipoItem *item, int esq, int dir, Analis * analise){
    analise->comparacoes++;
    if(dir >= esq){
        int meio = esq + (dir - esq) / 2;
        if(x[meio].chave == item->chave){
            *item = x[meio];
            return meio;
        }
        if(x[meio].chave > item->chave){
            return pesquisaBinaria(x, item, esq, meio - 1, analise);
        }
        return pesquisaBinaria(x, item, meio + 1, dir, analise);
    }
    return -1;
}


//PESQUISA POR ACESSO SEQUENCIAL INDEXADO
int pesquisa(TipoIndice tabela[], int tam, TipoItem* item, FILE *arq, int qtd_limite, Analis * analise){
    TipoItem pagina[ITENSPAGINA];
    int i, quantitens;
    long desloc;
    
    i = 0;
    //procura pela pag
    while(i < tam && tabela[i].chave <= item->chave){
        analise->comparacoes++;
        i++;
    }

    //se não encontrou
    if(i == 0)
        return 0;
    else{
        // contar quantos elementos tem na ultima pagina
        if (i < tam) // se nao for a ultima pagina
            quantitens = ITENSPAGINA;
        else {
            quantitens = qtd_limite % ITENSPAGINA;
            if (quantitens == 0)
                quantitens = ITENSPAGINA;
        }

        // ler a pagina
        desloc = (i - 1) * ITENSPAGINA * sizeof(TipoItem);
        fseek(arq, desloc, SEEK_SET); //indo pro local do arquivo onde começa a pagina desejada
        fread(&pagina, sizeof(TipoItem), quantitens, arq); //ler a pagina toda

        // pesquisa binaria na pagina
        if (pesquisaBinaria(pagina, item, 0, quantitens - 1, analise) != -1)
            return 1;
        else
            return 0;
    }
}

int verifica(int argc, char *argv[]){
    int x = 0;
    
    //verifica o numero de argumentos
    if (argc < 5 || (argc < 5 && strcmp(argv[4], "-P") == 0)){
        printf("Numero de argumentos invalido.\n");
        return 0;
    }
    
    int metodo = atoi(argv[1]); //1 = PSI, 2 = ARVORE BINARIA, 3 = ARVORE B, 4 = ARVORE B*
    int situacao = atoi(argv[3]); //1 = ordenado, 2 = inverso, 3 = aleatorio

    //verifica a situação
    if (situacao < 1 && situacao > 3){
        printf("Situação inválida.\n");
    }

    //verifica o metodo
    if(metodo < 1 && metodo > 4) {
        printf("Metodo inválido\n");
        x++;
    }

    //verifica se é possivel fazer a pesquisa sequencial indexada
    if(metodo == 1 && situacao != 1){
        printf("Este metodo nao suporta a situacao escolhida.\n");
        x++;
    }

    //se tudo estiver ok
    if (x == 0) return 1;
    else return 0;
}