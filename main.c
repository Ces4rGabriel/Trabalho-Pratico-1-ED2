#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pesquisa.h"
#include "arv_B.h"
#include "gerador/gerador.h"

int main(int argc, char *argv[]){ 
    FILE *arq;
    int metodo, nRegistros, situacao, chave;
    metodo = nRegistros = situacao = chave = 0;

    //verificar se os parametros estão corretos
    if (verifica(argc, argv)==0) return 0;  
    
    metodo = atoi(argv[1]); //1 = PSI, 2 = ARVORE BINARIA, 3 = ARVORE B, 4 = ARVORE B*
    nRegistros = atoi(argv[2]);
    situacao = atoi(argv[3]); //1 = ordenado, 2 = inverso, 3 = aleatorio
    chave = atoi(argv[4]);

    //evocar o gerador
    gerador(nRegistros, situacao);

    //abrir o arquivo
    if((arq = fopen("arq.bin", "rb")) == NULL){
        printf("Erro\n");
        exit(1);
    }

    switch (metodo)
    {
    case 1:
        psi_main(chave, arq);
        break;
    case 3:
        arvB_main(chave, arq);
        break;
    }
    fclose(arq);
    return 0;
}