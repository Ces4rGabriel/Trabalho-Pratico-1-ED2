#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pesquisa.h"
#include "arv_B.h"
#include "arv_B_estrela.h"

void analisar(FILE* arq){
    srand(time(NULL));
    Analis a[20];
    Analis r;
    int tam;
    //arvB
    tam = 100;
    r.tempo = 0; r.comparacoes = 0; r.nTransferencias = 0;

    for (int i = 0; i < 20; i++){
        arvB_main(rand() % tam, arq, tam, &a[i], 0);
    }
    //calcular a media de tempo
    for (int i = 0; i < 20; i++){
        r.tempo += a[i].tempo;
        r.nTransferencias += a[i].nTransferencias;
        r.comparacoes += a[i].comparacoes;
    }
    printf("TAMANHO: %d\n", tam);
    printf("Tempo medio: %.10f\n", r.tempo/20);
    printf("Comparacoes medio: %d\n", r.comparacoes/20);
    printf("Transferencias medio: %d\n", r.nTransferencias/20);

    //PSI

}

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
        arq = fopen("arq.bin", "rb");
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
        pesSeqInd(chave, arq, nRegistros);
        break;
    case 3:
        arvB_main(chave, arq, nRegistros, &a, printResult);
        break;
    case 4:
        arvBE_main(chave, arq, nRegistros);
    }
    analisar(arq);
    fclose(arq);
    return 0;
}