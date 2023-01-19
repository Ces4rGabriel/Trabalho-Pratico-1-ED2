#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAXITEM 2000000

typedef struct{
    int chave;
    long int dado1;
    char dado2[500];
}TipoItem;

int main(){
    //Criar um arquivo binário de 2.000.000 de registros aleatŕoios
    FILE *arq;
    int i;
    TipoItem item;
    srand(time(NULL));
    arq = fopen("arquivo.bin", "wb");
    item.chave = 0;
    for(i = 0; i < MAXITEM; i++){
        item.chave++;
        //dado1 aleatorio
        item.dado1 = rand()%1000;
        //dado2 aleatorio
        for(int j = 0; j < 499; j++){
            item.dado2[j] = rand()%26 + 65;
        }
        item.dado2[499] = '\0';
        fwrite(&item, sizeof(TipoItem), 1, arq);
    }
    fclose(arq);
    return 0;
}