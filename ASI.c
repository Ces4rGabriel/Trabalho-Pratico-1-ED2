#include <stdio.h>

#define ITENSPAGINA 100
#define MAXTABELA 100

typedef struct{
    int chave;
}tipoindice;


typedef struct{
    int chave;
    long dado1;
    char dado2[5000] 
}tipoitem;

//pesquisa binaria recursiva
int pesquisaBinaria(tipoitem x[], int chave, int esq, int dir){
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
int pesquisa(tipoindice tabela[], int tam, tipoitem* item, FILE *arq){
    tipoitem pagina[ITENSPAGINA];
    int i, quantitens;
    long desloc;
    
    
    int i = 0;

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
            quantitens = (ftell(arq)/sizeof(tipoitem)) % ITENSPAGINA;
        }

        // ler a pagina
        desloc = (i-1) * ITENSPAGINA * sizeof(tipoitem);
        fseek(arq, desloc, SEEK_SET);
        fread(&pagina, sizeof(tipoitem), quantitens, arq);

        //pesquisa binaria na pagina
        if(pesquisaBinaria(pagina, item->chave, 0, quantitens-1) != 0)
            return 1;
        else
            return 0;
    }

}

int main(){
    tipoindice tabela[MAXTABELA];
    FILE *arq;
    tipoitem x[ITENSPAGINA];
    int cont;

    if(arq = fopen("arq.bin", "rb") == NULL){
        printf("Erro\n");
        exit(1);
    }

    cont = 0;
    //ler de 100 em 100 registros do arquivo
    while(fread(x, sizeof(tipoitem), ITENSPAGINA, arq) == 100){
        tabela[cont].chave = x[0].chave;
        cont++;
    }
}