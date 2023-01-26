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
    Registros item;
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
        fwrite(&item, sizeof(Registros), 1, arq);
    }
    fclose(arq);
}

void descrescente(int qtd){
    FILE *arq;
    Registros item;
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
        fwrite(&item, sizeof(Registros), 1, arq);
    }
    fclose(arq);
}

void random(int qtd){
    //criando o arquivo crescente que será embaralhado
    crescente(qtd);

    FILE* arq;
    int j, i;
    arq = fopen("arq.bin", "wb");
    Registros aux, aux2;

    //fisher yates adaptado
    for (i = qtd -1; i > 0; i--){
        j = rand() % (i + 1);
        fseek(arq, i * sizeof(Registros), SEEK_SET); //posiciona o ponteiro no final do arquivo
        fread(&aux, sizeof(Registros), 1, arq); //le o ultimo registro e guarda em aux
        fseek(arq, j * sizeof(Registros), SEEK_SET); //posiciona o ponteiro no registro aleatorio
        fread(&aux2, sizeof(Registros), 1, arq); //le o registro aleatorio
        fseek(arq, j * sizeof(Registros), SEEK_SET); //posiciona o ponteiro no registro aleatorio
        fwrite(&aux, sizeof(Registros), 1, arq); //escreve o ultimo registro no registro aleatorio
        fseek(arq, i * sizeof(Registros), SEEK_SET); //posiciona o ponteiro no final do arquivo
        fwrite(&aux2, sizeof(Registros), 1, arq); //escreve o registro aleatorio no final do arquivo
    }//end for
    fclose(arq);
}