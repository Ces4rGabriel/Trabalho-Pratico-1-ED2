#include "arvoreBinaria.h"

void buscaBinariaMain()
{
    pesquisaBinariaMain();
    TipoItemBinario itemDesejado = localizaElementoNoArquivo(&arq, chave, &numeroDeAcessos, &numeroDeComparacoes);
}

void pesquisaBinariaMain()
{
    FILE* arq;
    FILE* arqAvrEscrita;

    arq = fopen("arqCre.bin","rb");
    arqAvrEscrita = fopen("arqCreArvBin.bin", "w+b");
    if(arq == NULL || arqAvrEscrita == NULL)
        printf("\nErro ao abrir os arquivos");
    converteArquivoParaBinario(&arq, &arqAvrEscrita);
    fclose(arq);
    fclose(arqAvrEscrita);

    arq = fopen("arqDes.bin","rb");
    arqAvrEscrita = fopen("arqDesArvBin.bin", "w+b");
    if(arq == NULL || arqAvrEscrita == NULL)
        printf("\nErro ao abrir os arquivos");
    converteArquivoParaBinario(&arq, &arqAvrEscrita);
    fclose(arq);
    fclose(arqAvrEscrita);

    arq = fopen("arqDec.bin","rb");
    arqAvrEscrita = fopen("arqDecArvBin.bin", "w+b");
    if(arq == NULL || arqAvrEscrita == NULL)
        printf("\nErro ao abrir os arquivos");
    converteArquivoParaBinario(&arq, &arqAvrEscrita);
    fclose(arq);
    fclose(arqAvrEscrita);
}

void converteArquivoParaBinario(FILE** arq, FILE** arqAvrEscrita)
{

    TipoItem* itensArquivoOriginal = malloc(1000 * sizeof(TipoItem));
    TipoItemBinario* itensTeste = malloc(2000 * sizeof(TipoItemBinario));
    TipoItemBinario itemParaBinario, itemRaizDaArvBinaria;
    int raizAtual;
    int condicional = 1;
    int aux = 0;


    for(int i = 0; i < NUMERODEREGISTROS/1000; i++)
    {
        fread(itensArquivoOriginal, sizeof(TipoItem), 1000, *arq);
        for(int j = 0; j < 1000; j++)
        {
            itemParaBinario.apontadorDir = -1;
            itemParaBinario.apontadorEsq = -1;
            itemParaBinario.chave = itensArquivoOriginal[j].chave;
            itemParaBinario.dado1 = itensArquivoOriginal[j].dado1;
            //strcpy(itemParaBinario.dado2, itensArquivoOriginal[j].dado2);
            if(ftell(*arqAvrEscrita) == 0)
            {
                fwrite(&itemParaBinario, sizeof(TipoItemBinario), 1, *arqAvrEscrita);
                raizAtual = 0;
                condicional = 0;
            }
            else
                fwrite(&itemParaBinario, sizeof(TipoItemBinario), 1, *arqAvrEscrita);
            while(condicional)
            {
                fseek(*arqAvrEscrita, raizAtual * sizeof(TipoItemBinario), SEEK_SET);
                fread(&itemRaizDaArvBinaria, sizeof(TipoItemBinario), 1, *arqAvrEscrita);

                if(itemParaBinario.chave >= itemRaizDaArvBinaria.chave)
                {
                    if(itemRaizDaArvBinaria.apontadorDir == -1)
                    {
                        fseek(*arqAvrEscrita, 0 * sizeof(TipoItemBinario), SEEK_END);
                        itemRaizDaArvBinaria.apontadorDir = (ftell(*arqAvrEscrita))/sizeof(TipoItemBinario) - 1;
                        fseek(*arqAvrEscrita, raizAtual * sizeof(TipoItemBinario), SEEK_SET);
                        fwrite(&itemRaizDaArvBinaria, sizeof(TipoItemBinario), 1, *arqAvrEscrita);
                        fseek(*arqAvrEscrita, 0 * sizeof(TipoItemBinario), SEEK_END);
                        condicional = 0;
                    }
                    else
                        raizAtual = itemRaizDaArvBinaria.apontadorDir; 
                }
                else
                {
                    if(itemRaizDaArvBinaria.apontadorEsq == -1)
                    {
                        fseek(*arqAvrEscrita, 0 * sizeof(TipoItemBinario), SEEK_END);
                        itemRaizDaArvBinaria.apontadorEsq = (ftell(*arqAvrEscrita))/sizeof(TipoItemBinario) - 1;
                        fseek(*arqAvrEscrita, raizAtual * sizeof(TipoItemBinario), SEEK_SET);
                        fwrite(&itemRaizDaArvBinaria, sizeof(TipoItemBinario), 1, *arqAvrEscrita);
                        fseek(*arqAvrEscrita, 0 * sizeof(TipoItemBinario), SEEK_END);
                        condicional = 0;
                    }
                    else
                        raizAtual = itemRaizDaArvBinaria.apontadorEsq; 
                }
            }
            condicional = 1;
            raizAtual = 0;
            aux++;
            printf("\n%d", aux);
        }
            fseek(*arqAvrEscrita, 0 * sizeof(TipoItemBinario), SEEK_SET);
        fread(itensTeste, sizeof(TipoItemBinario), 1000, *arqAvrEscrita);
        fseek(*arqAvrEscrita, 0 * sizeof(TipoItemBinario), SEEK_END);
        
    }
    fseek(*arqAvrEscrita, 0 * sizeof(TipoItemBinario), SEEK_SET);
    fread(itensTeste, sizeof(TipoItemBinario), 2000, *arqAvrEscrita);
    fseek(*arqAvrEscrita, 0 * sizeof(TipoItemBinario), SEEK_END);
    free(itensArquivoOriginal);
    free(itensTeste);
}

TipoItemBinario localizaElementoNoArquivo(FILE** arq, int chave, int* numeroDeAcessos, int*numeroDeComparacoes)
{

}