#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pesquisa.h"
#include "gerador.h"

int main(int argc, char *argv[]){    
    tipoindice tabela[MAXTABELA];
    FILE *arq;
    tipoitem x[ITENSPAGINA];
    tipoitem item;
    int cont;
    int nRegistros = atoi(argv[1]);


    //evocar o gerador
    gerador(nRegistros);


    //abrir o arquivo
    if((arq = fopen("arq.bin", "rb")) == NULL){
        printf("Erro\n");
        exit(1);
    }


    //criar a tabela de indices
    cont = 0;
    
    //ler de 100 em 100 registros do arquivo
    while(fread(x, sizeof(tipoitem), ITENSPAGINA, arq) > 0){
        tabela[cont].chave = x[0].chave; 
        cont++;
    }
    printf("cont = %d\n", cont);


    //imprimir tabela
    for(int i = 0; i < cont; i++){
        printf("Tabela[%d]: %d\n", i, tabela[i].chave);
    }
    printf("Digite a chave a ser pesquisada: ");

    scanf("%d", &item.chave);

    //pesquisar
    if(pesquisa(tabela, cont, &item, arq))
        printf("Encontrado o item de chave %d registro_1: %ld registro_2: %s\n", item.chave, item.dado1,item.dado2);
    else
        printf("Não encontrado\n");
    
    fclose(arq);
    return 0;
}