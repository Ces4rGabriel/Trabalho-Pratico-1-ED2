#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ITENSPAGINA 100
#define MAXTABELA 100

typedef struct{
    int chave;
}tipoindice;


typedef struct{
    int chave;
    long dado1;
    char dado2[50]; 
}tipoitem;

//pesquisa binaria recursiva
int pesquisaBinaria(tipoitem x[], int chave, int esq, int dir){
    int meio;
    if(esq > dir)
        return 0;
    else{
        meio = (esq + dir)/2;
        if(x[meio].chave == chave)
            return meio;
        else if(x[meio].chave > chave)
            return pesquisaBinaria(x, chave, esq, meio-1);
        else
            return pesquisaBinaria(x, chave, meio+1, dir);
    }
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


        //pesquisa sequencial
        for (i=0; i < quantitens; i++)
            if (pagina[i].chave == item->chave) {
                *item = pagina[i];
                return 1;
        }
        return 0;
        
        // pesquisa binaria na pagina
        /*
        if (pesquisaBinaria(pagina, item->chave, 0, quantitens - 1) != 0)
            return 1;
        else
            return 0;
            */
    }

}

int main(){    
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