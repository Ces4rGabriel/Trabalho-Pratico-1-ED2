#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pesquisa.h"
#include "gerador/gerador.h"

int main(int argc, char *argv[]){    
    int metodo = atoi(argv[1]); //1 = PSI, 2 = ARVORE BINARIA, 3 = ARVORE B, 4 = ARVORE B*
    int nRegistros = atoi(argv[2]);
    int situacao = atoi(argv[3]); //1 = ordenado, 2 = inverso, 3 = aleatorio
    int chave = atoi(argv[4]);

    //verificar se os parametros estão corretos
    if (verifica(argc, metodo, situacao)==0) return 0;

    //evocar o gerador
    gerador(nRegistros, situacao);
    switch (metodo)
    {
    case 1:
        psi_main(chave);
        break;
    }
    
    return 0;
}