#include "header.h"

int main()
{
    TipoEntradaTerminal entrada;
    entrada.situacaoDoArquivo = 3;
    entrada.quantidadeDeRegistros = 200;
    geradorMain(entrada);
}

void geradorMain(TipoEntradaTerminal entrada)
{
    int comando;
    printf("\nGERADOR DE ARQUIVOS BINARIOS\n\n");
    printf("Caso voce tenha selecionado a situacao de arquivo 3, EH NECESSARIO GERAR UM ARQUIVO DO TAMANHO DA ENTRADA PARA A BUSCA EM ARQUIVO DESORDENADO! Isso ocorrerá automaticamente.\n");
    printf("Para gerar um arquivo desordenado de 2.000.000 de registros, passe esse argumento no terminal com situacao 3\n");
    printf("Se voce nao quer recriar o arquivo desordenado, digite -1 (Caso voce tenha alterado a quantidade de registros e utilize esse comando, o programa não funcionara corretamente)\n");
    printf("Para gerar as outras 2 situacoes, crescente e decrescente, de arquivos com 2.000.000 de registros digite 1\n");
    printf("\nComando: ");
    scanf("%d", &comando);
    if(comando == 1)
    {
        printf("\nGerando crescente ...");
        gerarArquivoCrescente(NUMERODEREGISTROS);
        printf("\nCrescente gerado!");

        printf("\nGerando decrescente ...");
        gerarArquivoDecrescente(NUMERODEREGISTROS);
        printf("\nDecrescente gerado!");
    }
    if(entrada.situacaoDoArquivo == 3 && comando != 1);
    {
        printf("\nGerando desordenado ...");
        gerarArquivoDesordenado(entrada.quantidadeDeRegistros);
        printf("\nDesordenado gerado!");
    }
}

void gerarArquivoCrescente(int numeroDeRegistros)
{
    FILE *arq;
    TipoRegistro item;
    srand(time(NULL));

    arq = fopen("arqCre.bin", "wb");
    for(int i = 0; i < numeroDeRegistros; i++){
        item.chave = i;
        //dado1 aleatorio, valor numerico
        item.dado1 = item.chave + 1000;
        //dado2 aleatorio
        for(int j = 0; j < TAMANHOSTRING - 1; j++){
            item.dado2[j] = rand()%26 + 65;
        }
        item.dado2[TAMANHOSTRING - 1] = '\0';
        fwrite(&item, sizeof(TipoRegistro), 1, arq);
    }
    fclose(arq);
}

void gerarArquivoDecrescente(int numeroDeRegistros)
{

    FILE *arq;
    TipoRegistro item;
    srand(time(NULL));

    arq = fopen("arqDec.bin", "wb");
    //valores decrescentes
    for(int i = numeroDeRegistros; i >= 0; i--){
        item.chave = i - 1;
        //dado1 aleatorio
        item.dado1 = item.chave + 1000;
        //dado2 aleatorio
        for(int j = 0; j < TAMANHOSTRING - 1; j++){
            item.dado2[j] = rand()%26 + 65;
        }
        item.dado2[TAMANHOSTRING - 1] = '\0';
        fwrite(&item, sizeof(TipoRegistro), 1, arq);
    }
    fclose(arq);
}


void gerarArquivoDesordenado(int numeroDeRegistros)
{

    FILE* arq; 
    TipoRegistro item;
    int* chaves = malloc(numeroDeRegistros * sizeof(int));

    srand(time(NULL));

    for(int i = 0; i < numeroDeRegistros; i++){
        chaves[i] = i;
    }

    for(int k = 0; k < 1000; k++){
        for (int i = numeroDeRegistros - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            int temp = chaves[i];
            chaves[i] = chaves[j];
            chaves[j] = temp;
        }
    }

    for(int i = 0; i < numeroDeRegistros; i++){
        if(chaves[i] < 100){
            printf("\n%d   ,   %d", chaves[i], i);
        }
    }

    arq = fopen("arqDes.bin", "wb");
    for(int i = 0; i < numeroDeRegistros; i++){
        item.chave = chaves[i];
        item.dado1 = item.chave + 1000;
        for(int j = 0; j < TAMANHOSTRING - 1; j++){
            item.dado2[j] = rand()%26 + 65;
        }
        item.dado2[TAMANHOSTRING - 1] = '\0';
        fwrite(&item, sizeof(TipoRegistro), 1, arq);
    }
    fclose(arq);
}