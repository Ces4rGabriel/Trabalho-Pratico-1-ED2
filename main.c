#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pesquisa.h"
#include "arv_B.h"
#include "arv_B_estrela.h"

void analisarPesq(FILE* arq);
void analisarCriacao(FILE* arq);

int main(int argc, char *argv[]){ 
    FILE *arq;
    Analis a;
    int metodo, nRegistros, situacao, chave;
    metodo = nRegistros = situacao = chave = 0;

    //verificar se os parametros estão corretos
    if (verifica(argc, argv)==0) return 0;  
    
    metodo = atoi(argv[1]); //1 = PSI, 2 = ARVORE BINARIA, 3 = ARVORE B, 4 = ARVORE B*
    nRegistros = atoi(argv[2]);
    situacao = atoi(argv[3]); //1 = ordenado, 2 = inverso, 3 = aleatorio
    chave = atoi(argv[4]);
    int printResult = 0;
    if ((argc == 6) && strcmp(argv[5], "-P") == 0)
        printResult = 1;

    //abrindo arquivo
    switch (situacao)
    {
    case 1:
        arq = fopen("arq_crescente.bin", "rb");
        break;
    case 2:
        arq = fopen("arq_decrescente.bin", "rb");
        break;

    case 3:
        arq = fopen("arq_random.bin", "rb");
        break;
    }
    if(arq == NULL){
        printf("Erro ao abrir o arquivo\n");
        return 0;
    }
    //chamando a função de pesquisa
    
    switch (metodo)
    {
    case 1:
        pesSeqInd(chave, arq, nRegistros, &a, printResult);
        break;
    case 3:
        arvB_main(chave, arq, nRegistros, &a, printResult);
        break;
    case 4:
        arvBE_main(chave, arq, nRegistros);
    }
    //analisarPesq(arq);
    //analisarCriacao(arq);
    fclose(arq);
    return 0;
}


void analisarCriacao(FILE* arq){
    Analis a[20];
    Analis r;
    int tam[5] = {100, 200, 20000, 200000, 2000000};
    int chave[20] = {1 , 3 ,5 , 9, 10, 20, 27,35, 40, 43, 55, 65, 68, 70, 85, 89, 91, 93, 98, 101};
    int mult[5] = {1, 2, 20, 2000, 20000};
    //arvB
    printf("Crescente\n");
    printf("__ARVORE B__\n");

    r.tempoC = 0; r.nTransferencias = 0; r.comparacoesC = 0;
    for(int i = 0; i < 5; i++){
        for (int j = 0; j < 20; j++){
            arvB_main(chave[j] * mult[i], arq, tam[i], &a[j], 0);
        }
        //calcular a media de tempo
        for (int j = 0; j < 20; j++){
            r.tempoC += a[j].tempoC;
            r.nTransferencias += a[j].nTransferencias;
            r.comparacoesC += a[j].comparacoesC;
        }
        printf("TAMANHO: -[%d]-\n", tam[i]);
        printf("Tempo medio: %.10f\n", r.tempoC/20);
        printf("  Comparacoes medio: %ld\n", r.comparacoesC/20);
        printf("    Transferencias medio: %d\n", r.nTransferencias/20);
        r.tempoC = 0; r.nTransferencias = 0; r.comparacoesC = 0;
    }

    printf("\nDecrescente\n");
    fclose(arq);
    fopen("arq_decrescente.bin", "rb");
    for(int i = 0; i < 5; i++){

        for (int j = 0; j < 20; j++){
            arvB_main(chave[j] * mult[i], arq, tam[i], &a[j], 0);
        }
        //calcular a media de tempo
        for (int j = 0; j < 20; j++){
            r.tempoC += a[j].tempoC;
            r.nTransferencias += a[j].nTransferencias;
            r.comparacoesC += a[j].comparacoesC;
        }

        printf("TAMANHO: %d\n", tam[i]);
        printf("Tempo medio: %.10f\n", r.tempoC/20);
        printf("  Comparacoes medio: %ld\n", r.comparacoesC/20);
        printf("    Transferencias medio: %d\n", r.nTransferencias/20);
        r.tempoC = 0; r.nTransferencias = 0; r.comparacoesC = 0;
    }
    fclose(arq);
/*
   printf("\CRIAÇÃO\n");
   fopen("arq_random.bin", "rb");
    //random
    for (int j = 0; j < 20; j++){
        arvB_main(chave[j] * 20000, arq, 2000000, &a[j], 0);
    }
    //calcular a media de tempo
    for (int j = 0; j < 20; j++){
        r.tempoC += a[j].tempoC;
        r.nTransferencias += a[j].nTransferencias;
        r.comparacoesC += a[j].comparacoesC;
    }

    printf("TAMANHO: %d\n", 200000);
    printf("Tempo medio: %.10f\n", r.tempoC/20);
    printf("  Comparacoes medio: %ld\n", r.comparacoesC/20);
    printf("    Transferencias medio: %d\n", r.nTransferencias/20);
    r.tempoC = 0; r.nTransferencias = 0; r.comparacoesC = 0;
    //fclose(arq);
    */
    //PSI
    fopen("arq_crescente.bin", "rb");
    printf("\nPESQUISA SEQUENCIAL INDEXADA\n");
    for(int i = 0; i < 5; i++){
        for (int j = 0; j < 20; j++){
            pesSeqInd(chave[j] * mult[i], arq, tam[i], &a[j], 0);
        }
        //calcular a media de tempo
        for (int j = 0; j < 20; j++){
            r.tempoC += a[j].tempoC;
            r.nTransferencias += a[j].nTransferencias;
            r.criacao += a[j].criacao;
        }
        printf("TAMANHO: %d\n", tam[i]);
        printf("Tempo medio: %.10f\n", r.tempoC/20);
        printf("  Comparacoes medio: %d\n", 0);
        printf("    Transferencias medio: %d\n", r.nTransferencias/20);
        r.tempoC = 0; r.nTransferencias = 0; r.comparacoesC = 0;
    }

}

void analisarPesq(FILE* arq){
    Analis a[20];
    Analis r;
    int tam[5] = {100, 200, 20000, 200000, 2000000};
    int chave[20] = {1 , 3 ,5 , 9, 10, 20, 27,35, 40, 43, 55, 65, 68, 70, 85, 89, 91, 93, 98, 101};
    int mult[5] = {1, 2, 20, 2000, 20000};
    
    //arvB
    printf("Crescente\n");
    printf("__ARVORE B__\n");
    r.tempo = 0; r.comparacoes = 0; r.nTransferencias = 0;
    for(int i = 0; i < 5; i++){
        for (int j = 0; j < 20; j++){
            arvB_main(chave[j] * mult[i], arq, tam[i], &a[j], 0);
        }
        //calcular a media de tempo
        for (int j = 0; j < 20; j++){
            r.tempo += a[j].tempo;
            r.nTransferencias += a[j].nTransferencias;
            r.comparacoes += a[j].comparacoes;
        }
        printf("TAMANHO: -[%d]-\n", tam[i]);
        printf("Tempo medio: %.10f\n", r.tempo/20);
        printf("  Comparacoes medio: %d\n", r.comparacoes/20);
        printf("    Transferencias medio: %d\n", r.nTransferencias/20);
        r.tempo = 0; r.comparacoes = 1; r.nTransferencias = 0;
    }

    printf("\nDecrescente\n");
    fclose(arq);
    fopen("arq_decrescente.bin", "rb");
    for(int i = 0; i < 5; i++){
        for(int i = 0; i < 20; i++){
            a[i].tempo = 0;
            a[i].comparacoes = 0;
            a[i].nTransferencias = 0;
        }
        for (int j = 0; j < 20; j++){
            arvB_main(chave[j] * mult[i], arq, tam[i], &a[j], 0);
        }
        //calcular a media de tempo
        for (int j = 0; j < 20; j++){
            r.tempo += a[j].tempo;
            r.nTransferencias += a[j].nTransferencias;
            r.comparacoes += a[j].comparacoes;
        }
        printf("TAMANHO: %d\n", tam[i]);
        printf("Tempo medio: %.10f\n", r.tempo/20);
        printf("  Comparacoes medio: %d\n", r.comparacoes/20);
        printf("    Transferencias medio: %d\n", r.nTransferencias/20);
        r.tempo = 0; r.comparacoes = 1; r.nTransferencias = 0;
    }
    fclose(arq);
    /*
    //random
    fclose(arq);
    fopen("arq_random.bin", "rb");
    printf("\nPESQUISA\n");
    for (int j = 0; j < 20; j++){
        arvB_main(chave[j] * 20000, arq, 2000000, &a[j], 0);
    }
    //calcular a media de tempo
    for (int j = 0; j < 20; j++){
        r.tempoC += a[j].tempoC;
        r.nTransferencias += a[j].nTransferencias;
        r.comparacoesC += a[j].comparacoesC;
    }

    printf("TAMANHO: %d\n", 2000000);
    printf("Tempo medio: %.10f\n", r.tempoC/20);
    printf("  Comparacoes medio: %ld\n", r.comparacoesC/20);
    printf("    Transferencias medio: %d\n", r.nTransferencias/20);
    r.tempoC = 0; r.nTransferencias = 0; r.comparacoesC = 0;
    //fclose(arq);
    */
    //PSI
    fopen("arq_crescente.bin", "rb")
    printf("\nPESQUISA SEQUENCIAL INDEXADA\n");
    for(int i = 0; i < 5; i++){
        for (int j = 0; j < 20; j++){
            pesSeqInd(chave[j] * mult[i], arq, tam[i], &a[j], 0);
        }
        //calcular a media de tempo
        for (int j = 0; j < 20; j++){
            r.tempo += a[j].tempo;
            r.nTransferencias += a[j].nTransferencias;
            r.comparacoes += a[j].comparacoes;
        }
        printf("TAMANHO: %d\n", tam[i]);
        printf("Tempo medio: %.10f\n", r.tempo/20);
        printf("  Comparacoes medio: %d\n", r.comparacoes/20);
        printf("    Transferencias medio: %d\n", r.nTransferencias/20);
        r.tempo = 0; r.comparacoes = 1; r.nTransferencias = 0;
    } 
}