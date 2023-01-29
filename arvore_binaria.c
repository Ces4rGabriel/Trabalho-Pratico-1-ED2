#include "arvore_binaria.h"

int main()
{
    TipoDadosRecolhidos* dados;
    TipoEntradaTerminal entrada;

    entrada.chaveDesejada = 500;
    entrada.metodoDePesquisa = 1;
    entrada.quantidadeDeRegistros = 2000;
    entrada.situacaoDoArquivo = 1;

    buscaBinariaMain(entrada, dados);
    return 0;
}

void buscaBinariaMain(TipoEntradaTerminal entrada, TipoDadosRecolhidos* dados)
{
    chamadaConvercao(entrada, dados);

    FILE* arq;
    TipoItemBinario itemDesejado;
    switch (entrada.situacaoDoArquivo)
    {
    case 1:
        arq = fopen("arqCreArvBin.bin", "rb");
        if(arq == NULL)
            printf("\nErro ao abrir arquivo");
        itemDesejado = localizaElementoNoArquivo(&arq,  entrada, dados);
        printf("\n%ld é o seu dado 1", itemDesejado.dado1);
        break;
    case 2:
        arq = fopen("arqCreArvBin.bin", "rb");
        if(arq == NULL)
            printf("\nErro ao abrir arquivo");
        itemDesejado = localizaElementoNoArquivo(&arq,  entrada, dados);
        printf("\n%ld é o seu dado 1", itemDesejado.dado1);
        break;
    case 3:
        arq = fopen("arqCreArvBin.bin", "rb");
        if(arq == NULL)
            printf("\nErro ao abrir arquivo");
        itemDesejado = localizaElementoNoArquivo(&arq,  entrada, dados);
        printf("\n%ld é o seu dado 1", itemDesejado.dado1);
    break;
    default:
        break;
    }

    
}

void chamadaConvercao(TipoEntradaTerminal entrada, TipoDadosRecolhidos* dados)
{
    FILE* arq;
    FILE* arqAvrEscrita;
    int checagem;

    printf("\nDeseja converter arqCre.bin (Arquivo crescente) para um arquivo em forma de arvore binaria (gera o arquivo arqCreArvBin.bin)? \n(1 - sim/0 - não) ");
    scanf("%d", &checagem);

    if(checagem != 0)
    {
        arq = fopen("arqCre.bin","rb");
        arqAvrEscrita = fopen("arqCreArvBin.bin", "w+b");
        if(arq == NULL || arqAvrEscrita == NULL)
            printf("\nErro ao abrir os arquivos");
        converteArquivoParaBinario(&arq, &arqAvrEscrita, entrada, dados);
        fclose(arq);
        fclose(arqAvrEscrita);
    }

    printf("\nDeseja converter arqDec.bin (Arquivo decrescente) para um arquivo em forma de arvore binaria (gera o arquivo arqDecArvBin.bin)? \n(1 - sim/0 - não) ");
    scanf("%d", &checagem);

    if(checagem != 0)
    {
        arq = fopen("arqDes.bin","rb");
        arqAvrEscrita = fopen("arqDesArvBin.bin", "w+b");
        if(arq == NULL || arqAvrEscrita == NULL)
            printf("\nErro ao abrir os arquivos");
        converteArquivoParaBinario(&arq, &arqAvrEscrita, entrada, dados);
        fclose(arq);
        fclose(arqAvrEscrita);
    }

    printf("\nDeseja converter arqCre.bin (Arquivo desordenado) para um arquivo em forma de arvore binaria (gera o arquivo arqDesArvBin.bin)? \n(1 - sim/0 - não) ");
    scanf("%d", &checagem);

    if(checagem != 0)
    {
        arq = fopen("arqDec.bin","rb");
        arqAvrEscrita = fopen("arqDecArvBin.bin", "w+b");
        if(arq == NULL || arqAvrEscrita == NULL)
            printf("\nErro ao abrir os arquivos");
        converteArquivoParaBinario(&arq, &arqAvrEscrita, entrada, dados);
        fclose(arq);
        fclose(arqAvrEscrita);
    }
}

void converteArquivoParaBinario(FILE** arq, FILE** arqAvrEscrita, TipoEntradaTerminal entrada, TipoDadosRecolhidos* dados)
{

    TipoItem* itensArquivoOriginal = malloc(1000 * sizeof(TipoItem));
    TipoItemBinario* itensTeste = malloc(2000 * sizeof(TipoItemBinario));
    TipoItemBinario itemParaBinario, itemRaizDaArvBinaria;
    int raizAtual;
    int condicional = 1;
    int aux = 0;


    for(int i = 0; i < entrada.quantidadeDeRegistros/1000; i++)
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

TipoItemBinario localizaElementoNoArquivo(FILE** arq, TipoEntradaTerminal entrada, TipoDadosRecolhidos* dados)
{
    TipoItemBinario itemObtido;
    TipoItemBinario itemRaiz;
    
    int posicao = 0;
    int condicional = 1;

    dados->numeroDeAcessos = 0;
    dados->numeroDeComparacoes = 0;
    dados->tempoDecorrido = 0;

    while(condicional)
    {
        fread(&itemRaiz, sizeof(TipoItemBinario), 1, *arq);
        
    }  
}