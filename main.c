#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pesquisa.h"
#include "gerador/gerador.h"

int main(int argc, char *argv[]){    
    int metodo = atoi(argv[1]);
    int nRegistros = atoi(argv[2]);
    int situacao = atoi(argv[3]);
    int chave = atoi(argv[4]);

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