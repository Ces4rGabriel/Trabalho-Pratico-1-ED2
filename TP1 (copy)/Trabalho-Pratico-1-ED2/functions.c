#include "header.h"

//pesquisa binaria recursiva
int pesquisaBinaria(TipoItem *x, int chave, int esq, int dir){
    int meio;
    if(esq > dir)
        return 0;
    else{
        meio = (esq + dir)/2;
        if(x[meio].chave == chave)
            return meio;
        else if(x[meio].chave > chave)
            return pesquisaBinaria(x, chave, esq, meio-1);
        else
            return pesquisaBinaria(x, chave, meio+1, dir);
    }
}

//PESQUISA POR ACESSO SEQUENCIAL INDEXADO
int buscaSequencialIndexada(TipoIndice tabela[], int tam, TipoItem* item, FILE *arq){
    TipoItem pagina[ITENSPAGINA];
    int i, quantitens;
    long desloc;
    
    i = 0;

    //procura pela pag
    while(i < MAXTABELA && tabela[i].chave < item->chave) i++;

    //se não encontrou
    if(i == 0)
        return 0;
    else{
        // contar quantos elementos tem na ultima pagina
        if (i < tam)
            quantitens = ITENSPAGINA;
        else {
            fseek(arq, 0, SEEK_END);
            quantitens = (ftell(arq) / sizeof(TipoItem)) % ITENSPAGINA;
            if (quantitens == 0)
                quantitens = ITENSPAGINA;
        }

        // ler a pagina
        desloc = (i - 1) * ITENSPAGINA * sizeof(TipoItem);
        fseek(arq, desloc, SEEK_SET); //indo pro local do arquivo onde começa a pagina desejada
        fread(&pagina, sizeof(TipoItem), quantitens, arq); //ler a pagina toda

        // pesquisa binaria na pagina
        if (pesquisaBinaria(pagina, item->chave, 0, quantitens - 1) != 0)
            return 1;
        else
            return 0;
    }

}