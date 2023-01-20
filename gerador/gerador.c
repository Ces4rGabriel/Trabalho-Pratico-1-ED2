#include "gerador.h"

void gerador(int qtd, int situacao){

    switch (situacao)
    {
    case 1:
        printf("\nGerando arquivo com chave ascendente\n");
        crescente(qtd);
        break;
    case 2:
        printf("\nGerando arquivo com chave descendente\n");
        descrescente(qtd);
        break;
    }
}

void crescente(int qtd){
    FILE *arq;
    registros item;
    srand(time(NULL));

    arq = fopen("arq.bin", "wb");
    item.chave = 0;
    for(int i = 0; i < qtd; i++){
        item.chave++;

        //dado1 aleatorio
        item.dado1 = rand()%1000;

        //dado2 aleatorio
        for(int j = 0; j < tam_str - 1; j++){
            item.dado2[j] = rand()%26 + 65;
        }
        item.dado2[tam_str - 1] = '\0';
        fwrite(&item, sizeof(registros), 1, arq);
    }
    fclose(arq);
}

void descrescente(int qtd){
    FILE *arq;
    registros item;
    srand(time(NULL));

    arq = fopen("arq.bin", "wb");
    item.chave = 0;
    //valores decrescentes
    for(int i = qtd; i > 0; i--){
        item.chave++;
        //dado1 aleatorio
        item.dado1 = rand()%1000;
        //dado2 aleatorio
        for(int j = 0; j < tam_str - 1; j++){
            item.dado2[j] = rand()%26 + 65;
        }
        item.dado2[tam_str - 1] = '\0';
        fwrite(&item, sizeof(registros), 1, arq);
    }
    fclose(arq);
}