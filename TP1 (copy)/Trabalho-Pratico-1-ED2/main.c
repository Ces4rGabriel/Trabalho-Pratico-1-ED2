#include "header.h"

int main(){
    TipoIndice tabela[MAXTABELA];
    FILE *arq;
    TipoItem x[ITENSPAGINA];
    TipoItem item;
    int cont;

    //abrir o arquivo
    if((arq = fopen("arquivo.bin", "rb")) == NULL){
        printf("Erro\n");
        exit(1);
    }

    //criar a tabela de indices
    cont = 0;
    //ler de 100 em 100 registros do arquivo
    while(fread(x, sizeof(TipoItem), ITENSPAGINA, arq) > 0){
        cont++;
        tabela[cont].chave = x[0].chave;  
    }

    printf("Digite a chave a ser pesquisada: ");

    scanf("%d", &item.chave);

    //pesquisar
    if(buscaSequencialIndexada(tabela, cont, &item, arq))
        printf("Encontrado o item de chave %d registro1: %ld\n", item.chave, item.dado1);
    else
        printf("Não encontrado\n");
    
    fclose(arq);
    return 0;
}