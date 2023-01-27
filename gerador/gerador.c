#include "gerador.h"

int main(){
    printf("\nGerando crescente ...");
    gerarArquivoCrescente(NUMERODEREGISTROS);
    printf("\nCrescente gerado!");

    printf("\nGerando decrescente ...");
    gerarArquivoDecrescente(NUMERODEREGISTROS);
    printf("\nDecrescente gerado!");

    printf("\nGerando desordenado ...");
    gerarArquivoDesordenado(NUMERODEREGISTROS);
    printf("\nDesordenado gerado!");

    FILE* arqCre = fopen("arqCre.bin", "r+b");
    FILE* arqDec = fopen("arqDec.bin", "r+b");
    FILE* arqDes = fopen("arqDes.bin", "r+b");

    Registro* itensTeste = malloc(1000 * sizeof(Registro));

    fread(itensTeste, sizeof(Registro), 1000, arqCre);
    fread(itensTeste, sizeof(Registro), 1000, arqDec);
    fread(itensTeste, sizeof(Registro), 1000, arqDes);
    
    free(itensTeste);
    fclose(arqCre);
    fclose(arqDec);
    fclose(arqDes);

}


void gerarArquivoCrescente(int numeroDeRegistros){
    FILE *arq;
    Registro item;
    srand(time(NULL));

    arq = fopen("arqCre.bin", "wb");
    for(int i = 0; i < numeroDeRegistros; i++){
        item.chave = i;
        //dado1 aleatorio, valor numerico
        item.dado1 = item.chave + 1000;
        //dado2 aleatorio
        for(int j = 0; j < TAMANHOSTRING - 1; j++){
            item.dado2[j] = rand()%26 + 65;
        }
        item.dado2[TAMANHOSTRING - 1] = '\0';
        fwrite(&item, sizeof(Registro), 1, arq);
    }
    fclose(arq);
}

void gerarArquivoDecrescente(int numeroDeRegistros){

    FILE *arq;
    Registro item;
    srand(time(NULL));
    
    arq = fopen("arqDec.bin", "wb");
    //valores decrescentes
    for(int i = numeroDeRegistros; i >= 0; i--){
        item.chave = i - 1;
        //dado1 aleatorio
        item.dado1 = item.chave + 1000;
        //dado2 aleatorio
        for(int j = 0; j < TAMANHOSTRING - 1; j++){
            item.dado2[j] = rand()%26 + 65;
        }
        item.dado2[TAMANHOSTRING - 1] = '\0';
        fwrite(&item, sizeof(Registro), 1, arq);
    }
    fclose(arq);
}


void gerarArquivoDesordenado(int numeroDeRegistros){

    FILE* arq; 
    Registro item;
    int* chaves = malloc(numeroDeRegistros * sizeof(int));

    srand(time(NULL));

    for(int i = 0; i < numeroDeRegistros; i++){
        chaves[i] = i;
    }

    for(int k = 0; k < 1000; k++){
        for (int i = numeroDeRegistros - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            int temp = chaves[i];
            chaves[i] = chaves[j];
            chaves[j] = temp;
        }
        printf("\n%d", k);
    }

    for(int i = 0; i < numeroDeRegistros; i++){
        if(chaves[i] < 100){
            printf("\n%d   ,   %d", chaves[i], i);
        }
    }

    arq = fopen("arqDes.bin", "wb");
    for(int i = 0; i < numeroDeRegistros; i++){
        item.chave = chaves[i];
        item.dado1 = item.chave + 1000;
        for(int j = 0; j < TAMANHOSTRING - 1; j++){
            item.dado2[j] = rand()%26 + 65;
        }
        item.dado2[TAMANHOSTRING - 1] = '\0';
        fwrite(&item, sizeof(Registro), 1, arq);
    }
    fclose(arq);
}