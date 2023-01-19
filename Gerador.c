#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAXITEM 530
#define STRTAM 50
typedef struct{
    int chave;
    long dado1;
    char dado2[STRTAM]; 
}tipoitem;

int main(){
    //Criar um arquivo binário de 2.000.000 de registros aleatŕoios
    FILE *arq;
    int i;
    tipoitem item;
    srand(time(NULL));
    arq = fopen("arq.bin", "wb");
    item.chave = 0;
    for(i = 0; i < MAXITEM; i++){
        item.chave++;
        //dado1 aleatorio
        item.dado1 = rand()%1000;
        //dado2 aleatorio
        for(int j = 0; j < STRTAM - 1; j++){
            item.dado2[j] = rand()%26 + 65;
        }
        item.dado2[STRTAM - 1] = '\0';
        fwrite(&item, sizeof(tipoitem), 1, arq);
    }
    fclose(arq);
    return 0;
    
}