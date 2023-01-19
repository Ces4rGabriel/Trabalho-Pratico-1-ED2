#include "gerador.h"


void gerador(int qtd){
    FILE *arq;
    int i;
    registros item;
    srand(time(NULL));

    arq = fopen("arq.bin", "wb");
    item.chave = 0;
    for(i = 0; i < qtd; i++){
        item.chave++;
        //dado1 aleatorio
        item.dado1 = rand()%1000;
        //dado2 aleatorio
        for(int j = 0; j < 50 - 1; j++){
            item.dado2[j] = rand()%26 + 65;
        }
        item.dado2[50 - 1] = '\0';
        fwrite(&item, sizeof(registros), 1, arq);
    }
    fclose(arq); 
}