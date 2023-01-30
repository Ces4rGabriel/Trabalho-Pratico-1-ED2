#include "header.h"

int main()
{
    TipoDadosRecolhidos* dadosPesquisa = malloc(sizeof(TipoDadosRecolhidos));
    TipoEntradaTerminal entrada;

    entrada.chaveDesejada = 120999;
    entrada.metodoDePesquisa = 3;
    entrada.quantidadeDeRegistros = 10;
    entrada.situacaoDoArquivo = 1;

    chamadaConvercao(entrada, dadosPesquisa);
    buscaBinariaMain(entrada, dadosPesquisa);

    free(dadosPesquisa);
    return 0;
}

void chamadaConvercao(TipoEntradaTerminal entrada, TipoDadosRecolhidos* dadosPesquisa)
{
    FILE* arq;
    FILE* arqAvrEscrita;
    int checagem;

    geradorMain(entrada);
    if(entrada.situacaoDoArquivo != 3){
        printf("\nDeseja converter arqCre.bin (Arquivo crescente) para um arquivo em forma de arvore binaria (gera o arquivo arqCreArvBin.bin)? \n(1 - sim/0 - não) ");
        scanf("%d", &checagem);

        if(checagem != 0)
        {
            arq = fopen("arqCre.bin","rb");
            arqAvrEscrita = fopen("arqCreArvBin.bin", "w+b");
            if(arq == NULL || arqAvrEscrita == NULL)
                printf("\nErro ao abrir os arquivos");
            converteArquivoParaBinario(&arq, &arqAvrEscrita, entrada, dadosPesquisa);
            fclose(arq);
            fclose(arqAvrEscrita);
        }

        printf("\nDeseja converter arqDec.bin (Arquivo decrescente) para um arquivo em forma de arvore binaria (gera o arquivo arqDecArvBin.bin)? \n(1 - sim/0 - não) ");
        scanf("%d", &checagem);

        if(checagem != 0)
        {
            arq = fopen("arqDec.bin","rb");
            arqAvrEscrita = fopen("arqDecArvBin.bin", "w+b");
            if(arq == NULL || arqAvrEscrita == NULL)
                printf("\nErro ao abrir os arquivos");
            converteArquivoParaBinario(&arq, &arqAvrEscrita, entrada, dadosPesquisa);
            fclose(arq);
            fclose(arqAvrEscrita);
        }
    }
    else if(entrada.situacaoDoArquivo == 3){
        printf("\nDeseja converter arqDes.bin (Arquivo desordenado) para um arquivo em forma de arvore binaria (gera o arquivo arqDesArvBin.bin)? \n(1 - sim/0 - não) ");
        scanf("%d", &checagem);

        if(checagem != 0)
        {
            arq = fopen("arqDes.bin","rb");
            arqAvrEscrita = fopen("arqDesArvBin.bin", "w+b");
            if(arq == NULL || arqAvrEscrita == NULL)
                printf("\nErro ao abrir os arquivos");
            converteArquivoParaBinario(&arq, &arqAvrEscrita, entrada, dadosPesquisa);
            fclose(arq);
            fclose(arqAvrEscrita);
        }
    }
}


void converteArquivoParaBinario(FILE** arq, FILE** arqAvrEscrita, TipoEntradaTerminal entrada, TipoDadosRecolhidos* dadosPesquisa)
{
    if(entrada.situacaoDoArquivo != 3)
    {
        printf("Convertendo crescente/decrescente para arvore binaria\nAguarde...");
        TipoRegistro* itensOriginais = malloc(10000 * sizeof(TipoRegistro));
        TipoRegistroAux* itensAuxiliares = malloc(NUMERODEREGISTROS * sizeof(TipoRegistroAux));
        TipoRegistroBinario* itensBinarios = malloc(10000 * sizeof(TipoRegistroBinario));

        int primeiraIteracao = 1;
        int percorreAuxiliares = 1;
        int percorreAuxiliaresEscritaFinal = 0;
        int raiz = 0;
        int cond = 1;
        int aux = 1;

        for(int i = 0; i < NUMERODEREGISTROS/10000; i++)
        {
            fread(itensOriginais, sizeof(TipoRegistro), 10000, *arq);
            for(int j = 0; j < 10000; j++)
            {
                if(primeiraIteracao)
                {
                    itensAuxiliares[0].apontadorDir = -1;
                    itensAuxiliares[0].apontadorEsq = -1;
                    itensAuxiliares[0].chave = itensOriginais[0].chave;
                    primeiraIteracao = 0;
                    itensBinarios[0].chave = itensOriginais[0].chave;
                    itensBinarios[0].dado1 = itensOriginais[0].dado1;
                    strcpy(itensBinarios[0].dado2, itensOriginais[0].dado2);

                }
                else
                {
                    itensAuxiliares[percorreAuxiliares].apontadorDir = -1;
                    itensAuxiliares[percorreAuxiliares].apontadorEsq = -1;
                    itensAuxiliares[percorreAuxiliares].chave = itensOriginais[j].chave;

                    itensBinarios[j].chave = itensOriginais[j].chave;
                    itensBinarios[j].dado1 = itensOriginais[j].dado1;
                    strcpy(itensBinarios[j].dado2, itensOriginais[j].dado2);

                    while(cond)
                    {
                        if(itensOriginais[j].chave >= itensAuxiliares[raiz].chave)
                        {
                            if(itensAuxiliares[raiz].apontadorDir == -1)
                            {
                                itensAuxiliares[raiz].apontadorDir = percorreAuxiliares;
                                cond = 0;
                            }
                            else
                                raiz = itensAuxiliares[raiz].apontadorDir;
                        }
                        else
                        {
                            if(itensAuxiliares[raiz].apontadorEsq == -1)
                            {
                                itensAuxiliares[raiz].apontadorEsq = percorreAuxiliares;
                                cond = 0;
                            }
                            else
                                raiz = itensAuxiliares[raiz].apontadorEsq;
                        }
                    }
                    cond = 1;
                    percorreAuxiliares++;
                    raiz = 0;
                }
            }
        }
        fseek(*arq, 0*sizeof(TipoRegistro), SEEK_SET);
        for(int i = 0; i < entrada.quantidadeDeRegistros/10000; i++)
        {
            fread(itensOriginais, sizeof(TipoRegistro), 10000, *arq);
            for(int j = 0; j < 10000; j++)
            {
                itensBinarios[j].apontadorDir = itensAuxiliares[percorreAuxiliaresEscritaFinal].apontadorDir;
                itensBinarios[j].apontadorEsq = itensAuxiliares[percorreAuxiliaresEscritaFinal].apontadorEsq;
                itensBinarios[j].chave = itensAuxiliares[percorreAuxiliares].chave;
                itensBinarios[j].chave = itensOriginais[j].chave;
                itensBinarios[j].dado1 = itensOriginais[j].dado1;
                strcpy(itensBinarios[j].dado2, itensOriginais[j].dado2);
                percorreAuxiliaresEscritaFinal++;
                
            }
            fwrite(itensBinarios, sizeof(TipoRegistroBinario), 10000, *arqAvrEscrita);
            printf("10000 itens anexados\n");
        }
        free(itensOriginais);
        free(itensAuxiliares);
    }
    else if(entrada.situacaoDoArquivo == 3)
    {
        printf("\nConvertendo arquivo desordenado\nESSE PROCESSO É O MAIS DEMORADO!!! \nAguarde...");
        TipoRegistro* itensOriginais = malloc(100 * sizeof(TipoRegistro));
        TipoRegistroAux* itensAuxiliares = malloc(entrada.quantidadeDeRegistros * sizeof(TipoRegistroAux));
        TipoRegistroBinario* itensBinarios = malloc(100 * sizeof(TipoRegistroBinario));

        int primeiraIteracao = 1;
        int percorreAuxiliares = 1;
        int percorreAuxiliaresEscritaFinal = 0;
        int raiz = 0;
        int cond = 1;

        for(int i = 0; i < entrada.quantidadeDeRegistros/100; i++)
        {
            fread(itensOriginais, sizeof(TipoRegistro), 100, *arq);
            for(int j = 0; j < 100; j++)
            {
                if(primeiraIteracao)
                {
                    itensAuxiliares[0].apontadorDir = -1;
                    itensAuxiliares[0].apontadorEsq = -1;
                    itensAuxiliares[0].chave = itensOriginais[0].chave;
                    primeiraIteracao = 0;
                    itensBinarios[0].chave = itensOriginais[0].chave;
                    itensBinarios[0].dado1 = itensOriginais[0].dado1;
                    strcpy(itensBinarios[0].dado2, itensOriginais[0].dado2);

                }
                else
                {
                    itensAuxiliares[percorreAuxiliares].apontadorDir = -1;
                    itensAuxiliares[percorreAuxiliares].apontadorEsq = -1;
                    itensAuxiliares[percorreAuxiliares].chave = itensOriginais[j].chave;

                    while(cond)
                    {
                        if(itensOriginais[j].chave >= itensAuxiliares[raiz].chave)
                        {
                            if(itensAuxiliares[raiz].apontadorDir == -1)
                            {
                                itensAuxiliares[raiz].apontadorDir = percorreAuxiliares;
                                cond = 0;
                            }
                            else
                                raiz = itensAuxiliares[raiz].apontadorDir;
                        }
                        else
                        {
                            if(itensAuxiliares[raiz].apontadorEsq == -1)
                            {
                                itensAuxiliares[raiz].apontadorEsq = percorreAuxiliares;
                                cond = 0;
                            }
                            else
                                raiz = itensAuxiliares[raiz].apontadorEsq;
                        }
                    }
                    cond = 1;
                    percorreAuxiliares++;
                    raiz = 0;
                }
            }
        }
        fseek(*arq, 0*sizeof(TipoRegistro), SEEK_SET);
        for(int i = 0; i < entrada.quantidadeDeRegistros/100; i++)
        {
            fread(itensOriginais, sizeof(TipoRegistro), 100, *arq);
            for(int j = 0; j < 100; j++)
            {
                itensBinarios[j].apontadorDir = itensAuxiliares[percorreAuxiliaresEscritaFinal].apontadorDir;
                itensBinarios[j].apontadorEsq = itensAuxiliares[percorreAuxiliaresEscritaFinal].apontadorEsq;
                itensBinarios[j].chave = itensAuxiliares[percorreAuxiliares].chave;
                itensBinarios[j].chave = itensOriginais[j].chave;
                itensBinarios[j].dado1 = itensOriginais[j].dado1;
                strcpy(itensBinarios[j].dado2, itensOriginais[j].dado2);
                percorreAuxiliaresEscritaFinal++;
                
            }
            fwrite(itensBinarios, sizeof(TipoRegistroBinario), 100, *arqAvrEscrita);
            printf("100 anexados \n");
        }
        free(itensOriginais);
        free(itensAuxiliares);
    }
}

void buscaBinariaMain(TipoEntradaTerminal entrada, TipoDadosRecolhidos* dadosPesquisa)
{
    FILE* arq;

    switch (entrada.situacaoDoArquivo)
    {
    case 1:
        arq = fopen("arqCreArvBin.bin", "rb");
        if(arq == NULL)
            printf("\nErro ao abrir arquivo");
        dadosPesquisa->itemRetornado = localizaElementoNoArquivo(&arq,  entrada, dadosPesquisa);
        printf("\nArquivo com %d registros.\nChave e registro retornados: %d - %ld\nNumero de acessos ao arquivo: %d\nNumero de comparacoes dadosPesquisa: %d\nTempo de execucao: %lf", entrada.quantidadeDeRegistros, dadosPesquisa->itemRetornado.chave, dadosPesquisa->itemRetornado.dado1, dadosPesquisa->numeroDeAcessos, dadosPesquisa->numeroDeComparacoes, dadosPesquisa->tempoDecorrido);
        break;
    case 2:
        arq = fopen("arqDecArvBin.bin", "rb");
        if(arq == NULL)
            printf("\nErro ao abrir arquivo");
        dadosPesquisa->itemRetornado = localizaElementoNoArquivo(&arq,  entrada, dadosPesquisa);
        printf("\nArquivo com %d registros.\nChave e registro retornados: %d - %ld\nNumero de acessos ao arquivo: %d\nNumero de comparacoes dadosPesquisa: %d\nTempo de execucao: %lf", entrada.quantidadeDeRegistros, dadosPesquisa->itemRetornado.chave, dadosPesquisa->itemRetornado.dado1, dadosPesquisa->numeroDeAcessos, dadosPesquisa->numeroDeComparacoes, dadosPesquisa->tempoDecorrido);
        break;
    case 3:
        arq = fopen("arqDesArvBin.bin", "rb");
        if(arq == NULL)
            printf("\nErro ao abrir arquivo");
        dadosPesquisa->itemRetornado = localizaElementoNoArquivo(&arq,  entrada, dadosPesquisa);
        printf("\nArquivo com %d registros.\nChave e registro retornados: %d - %ld\nNumero de acessos ao arquivo: %d\nNumero de comparacoes dadosPesquisa: %d\nTempo de execucao: %lf", entrada.quantidadeDeRegistros, dadosPesquisa->itemRetornado.chave, dadosPesquisa->itemRetornado.dado1, dadosPesquisa->numeroDeAcessos, dadosPesquisa->numeroDeComparacoes, dadosPesquisa->tempoDecorrido);
    break;
    default:
        break;
    }
}

TipoRegistro localizaElementoNoArquivo(FILE** arq, TipoEntradaTerminal entrada, TipoDadosRecolhidos* dadosPesquisa)
{
    TipoRegistro itemObtido;
    TipoRegistroBinario itemRaiz;
    
    clock_t start, end;
    int posicao = 0;
    int condicional = 1;

    dadosPesquisa->numeroDeAcessos = 0;
    dadosPesquisa->numeroDeComparacoes = 0;
    dadosPesquisa->tempoDecorrido = 0;

    start = clock();
    while(condicional)
    {
        fseek(*arq, posicao * sizeof(TipoRegistroBinario), SEEK_SET);
        fread(&itemRaiz, sizeof(TipoRegistroBinario), 1, *arq);
        dadosPesquisa->numeroDeAcessos++;
        if(entrada.chaveDesejada == itemRaiz.chave)
        {
            dadosPesquisa->numeroDeComparacoes++;
            itemObtido.chave = itemRaiz.chave;
            itemObtido.dado1 = itemRaiz.dado1;
            strcpy(itemObtido.dado2, itemRaiz.dado2);
            end = clock();
            dadosPesquisa->tempoDecorrido =  ((double) (end - start)) / CLOCKS_PER_SEC;
            return itemObtido;
        }
        else if(entrada.chaveDesejada > itemRaiz.chave)
        {
            dadosPesquisa->numeroDeComparacoes++;
            if(itemRaiz.apontadorDir != -1)
                posicao = itemRaiz.apontadorDir;
            else
            {
                itemObtido.chave = -1;
                end = clock();
                dadosPesquisa->tempoDecorrido =  ((double) (end - start)) / CLOCKS_PER_SEC;
                return itemObtido;
            }
        }
        else if(entrada.chaveDesejada < itemRaiz.chave)
        {
            dadosPesquisa->numeroDeComparacoes++;
            if(itemRaiz.apontadorEsq != -1)
                posicao = itemRaiz.apontadorEsq;
            else
            {
                itemObtido.chave = -1;
                end = clock();
                dadosPesquisa->tempoDecorrido =  ((double) (end - start)) / CLOCKS_PER_SEC;
                return itemObtido;
            }
        }
    }  
    itemObtido.chave = -2;
    return itemObtido;
}

