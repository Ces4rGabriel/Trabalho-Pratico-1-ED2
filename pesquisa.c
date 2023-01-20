#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "pesquisa.h"

void psi_main(int chave){
    tipoindice tabela[MAXTABELA];
    FILE *arq;
    tipoitem x[ITENSPAGINA];
    tipoitem item;
    int cont;
    
    //abrir o arquivo
    if((arq = fopen("arq.bin", "rb")) == NULL){
        printf("Erro\n");
        exit(1);
    }

    //criar a tabela de indices
    cont = 0; 

    while(fread(x, sizeof(tipoitem), ITENSPAGINA, arq) > 0){ //itenspagina = 100
        tabela[cont].chave = x[0].chave; 
        cont++;
    }

    /*imprimir tabela
    for(int i = 0; i < cont; i++){
        printf("Tabela[%d]: %d\n", i, tabela[i].chave);
    }
    */

    item.chave = chave;
    //pesquisar
    clock_t inicio = clock();
    if(pesquisa(tabela, cont, &item, arq))
        printf("\nEncontrado o item de chave %d\n registro_1: %ld\n registro_2: %s\n", item.chave, item.dado1,item.dado2);
    else
        printf("\nNão encontrado\n");
    clock_t fim = clock();
    double tempo = (double)(fim - inicio) / CLOCKS_PER_SEC;
    printf("\nTempo de execução da função Pesquisa Sequencial Indexada: %f\n", tempo);

    fclose(arq);
}



//pesquisa binaria recursiva
int pesquisaBinaria(tipoitem x[], tipoitem *item, int esq, int dir){
    if(dir >= esq){
        int meio = esq + (dir - esq) / 2;
        if(x[meio].chave == item->chave){
            *item = x[meio];
            return meio;
        }

        if(x[meio].chave > item->chave)
            return pesquisaBinaria(x, item, esq, meio - 1);

        return pesquisaBinaria(x, item, meio + 1, dir);
    }
    return -1;
}


//PESQUISA POR ACESSO SEQUENCIAL INDEXADO
int pesquisa(tipoindice tabela[], int tam, tipoitem* item, FILE *arq){
    tipoitem pagina[ITENSPAGINA];
    int i, quantitens;
    long desloc;
    
    i = 0;
    //procura pela pag
    while(i < tam && tabela[i].chave <= item->chave) i++;

    //se não encontrou
    if(i == 0)
        return 0;
    else{
        // contar quantos elementos tem na ultima pagina
        if (i < tam)
            quantitens = ITENSPAGINA;
        else {
            fseek(arq, 0, SEEK_END);
            quantitens = (ftell(arq) / sizeof(tipoitem)) % ITENSPAGINA;
            if (quantitens == 0)
                quantitens = ITENSPAGINA;
        }

        // ler a pagina
        desloc = (i - 1) * ITENSPAGINA * sizeof(tipoitem);
        fseek(arq, desloc, SEEK_SET); //indo pro local do arquivo onde começa a pagina desejada
        fread(&pagina, sizeof(tipoitem), quantitens, arq); //ler a pagina toda

        // pesquisa binaria na pagina
        if (pesquisaBinaria(pagina, item, 0, quantitens - 1) != -1)
            return 1;
        else
            return 0;

    }

}