#include "header.h"

//Funcao usada para selecionar as situacoes de convercao do arquivo para arvore binaria
void chamadaConvercao(TipoEntradaTerminal entrada, TipoDadosRecolhidos* dadosPesquisa)
{
    FILE* arq;
    FILE* arqAvrEscrita;
    int checagem;

    //Chamando o gerador. O uso principal dessa chamada e para criar o arquivo desordenado dinamicamente
    geradorMain(entrada);

    //Caso a situacao nao seja a 3. Serve para a primeira inicializacao do programa e para gerar os primeiros documentos convertidos para arvore binaria caso nao exista
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
    //Caso a situacao seja 3, nao ha necessidade de perguntar e gerar os outros 2 arquivos
    else if(entrada.situacaoDoArquivo == 3){
        printf("\nDeseja converter arqDes.bin (Arquivo crescente) para um arquivo em forma de arvore binaria (gera o arquivo arqDesArvBin.bin)? \n(1 - sim/0 - não) ");
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


//Funcao responsavel por converter o arquivo original para um arquivo estruturado como arvore binaria
void converteArquivoParaBinario(FILE** arq, FILE** arqAvrEscrita, TipoEntradaTerminal entrada, TipoDadosRecolhidos* dadosPesquisa)
{
    int aux = 0;
    //E necessario separar a execucao em duas diferentes: uma para o decrescente e crescente
    //Ja que nao ha problemas em navegar pelo arquivo original, que sempre possui o maior tamanho possivel
    //O que permite buscar e armazenar de 10000 em 10000, visando tornar esse processo um pouco menos demorado
    if(entrada.situacaoDoArquivo != 3)
    {
        printf("Convertendo crescente/decrescente para arvore binaria\nAguarde...");
        TipoRegistroNormal* itensOriginais = malloc(10000 * sizeof(TipoRegistroNormal));//ItensOriginais armazena 10000 registros que fora gerados no arqCre/Dec pelo nosso gerador
        TipoRegistroAux* itensAuxiliares = malloc(NUMERODEREGISTROS * sizeof(TipoRegistroAux));//itensAuxiliares eh um vetor de tamanho maximo, armazena os apontadores para a direita, esquerda e a chave, mais detalhes no relatorio
        TipoRegistroBinario* itensBinarios = malloc(10000 * sizeof(TipoRegistroBinario));//itensBinarios armazena o resultado final da escrita, 10000 Registros com seus respectivos apontadores

        int primeiraIteracao = 1;
        int percorreAuxiliares = 1;//Percorre o vetor itensAuxiliares, gravando as chaves nesse vetor
        int percorreAuxiliaresEscritaFinal = 0;//Percorre novamente o itensAuxiliares, porem agora recolhendo seus dados e armazenando no itensBinarios
        int raiz = 0;//A raiz, responsavel por percorrer o vetor e determinar onde o apontador de um item ira apontar
        int cond = 1;

        for(int i = 0; i < NUMERODEREGISTROS/10000; i++)
        {
            fread(itensOriginais, sizeof(TipoRegistroNormal), 10000, *arq);
            for(int j = 0; j < 10000; j++)
            {
                if(primeiraIteracao)//Gravando a primeira raiz do itens
                {
                    itensAuxiliares[0].apontadorDir = -1;
                    itensAuxiliares[0].apontadorEsq = -1;
                    itensAuxiliares[0].chave = itensOriginais[0].chave;
                    primeiraIteracao = 0;

                }
                else//Gravando a chave e setando os apontadores
                {
                    itensAuxiliares[percorreAuxiliares].apontadorDir = -1;
                    itensAuxiliares[percorreAuxiliares].apontadorEsq = -1;
                    itensAuxiliares[percorreAuxiliares].chave = itensOriginais[j].chave;
                    while(cond)//Nesse while eh realizado uma simples pesquisa e atribuicao no vetor itensAuxiliares
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
        //Parte responsavel por atribuir os valores finals ao vetor itensBinarios e escrever esse vetor no arquivo final em forma de arvore
        fseek(*arq, 0*sizeof(TipoRegistroNormal), SEEK_SET);
        for(int i = 0; i < NUMERODEREGISTROS/10000; i++)
        {
            fread(itensOriginais, sizeof(TipoRegistroNormal), 10000, *arq);
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
            printf("%d itens anexados no arquivo final %d\n", aux, entrada.situacaoDoArquivo);
            aux += 10000;
        }
        free(itensOriginais);
        free(itensAuxiliares);
    }





    //O funcionamento dessa parte eh praticamente identica a da anterior, com a unica diferenca sendo a quantidade de registros sendo lidos e gravados
    else if(entrada.situacaoDoArquivo == 3)
    {
        printf("\nConvertendo arquivo desordenado\nESSE PROCESSO É O MAIS DEMORADO!!! \nAguarde...");
        TipoRegistroNormal* itensOriginais = malloc(100 * sizeof(TipoRegistroNormal));
        TipoRegistroAux* itensAuxiliares = malloc(entrada.quantidadeDeRegistros * sizeof(TipoRegistroAux));
        TipoRegistroBinario* itensBinarios = malloc(100 * sizeof(TipoRegistroBinario));

        int primeiraIteracao = 1;
        int percorreAuxiliares = 1;
        int percorreAuxiliaresEscritaFinal = 0;
        int raiz = 0;
        int cond = 1;

        for(int i = 0; i < entrada.quantidadeDeRegistros/100; i++)
        {
            fread(itensOriginais, sizeof(TipoRegistroNormal), 100, *arq);
            for(int j = 0; j < 100; j++)
            {
                if(primeiraIteracao)
                {
                    itensAuxiliares[0].apontadorDir = -1;
                    itensAuxiliares[0].apontadorEsq = -1;
                    itensAuxiliares[0].chave = itensOriginais[0].chave;
                    primeiraIteracao = 0;
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
        fseek(*arq, 0*sizeof(TipoRegistroNormal), SEEK_SET);
        for(int i = 0; i < entrada.quantidadeDeRegistros/100; i++)
        {
            fread(itensOriginais, sizeof(TipoRegistroNormal), 100, *arq);
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
            printf("%d itens anexados no arquivo final %d\n", aux, entrada.situacaoDoArquivo);
            aux += 100;
        }
        free(itensOriginais);
        free(itensAuxiliares);
    }
}


//Essa funcao realiza a busca de acordo com a situacao passada pelo terminal
void buscaArvoreBinariaMain(TipoEntradaTerminal entrada, TipoDadosRecolhidos* dadosPesquisa)
{
    FILE* arq;
    switch (entrada.situacaoDoArquivo)
    {
    case 1:
        arq = fopen("arqCreArvBin.bin", "rb");
        if(arq == NULL)
            printf("\nErro ao abrir arquivo");
        dadosPesquisa->itemRetornado = localizaElementoNoArquivo(&arq,  entrada, dadosPesquisa);
        printf("\nPesquisa realizada!");
        if(dadosPesquisa->itemRetornado.chave < 0)
            printf("\nA chave requisitada nao foi encontrada no arquivo!");
        printf("\nQuantidade de acessos ao arquivo: %d", dadosPesquisa->numeroDeAcessos);
        printf("\nQuantidade de comparacoes entre chaves: %d", dadosPesquisa->numeroDeComparacoes);
        printf("\nTempo de busca: %.10lf", dadosPesquisa->tempoDecorrido);
        if(entrada.argOpcional)
            printf("\nA chave requisitada foi %d, a encontrada foi %d, que contem como dado1 %ld", entrada.chaveDesejada, dadosPesquisa->itemRetornado.chave, dadosPesquisa->itemRetornado.dado1);
        break;
    case 2:
        arq = fopen("arqDecArvBin.bin", "rb");
        if(arq == NULL)
            printf("\nErro ao abrir arquivo");
        dadosPesquisa->itemRetornado = localizaElementoNoArquivo(&arq,  entrada, dadosPesquisa);
        printf("\nPesquisa realizada!");
        if(dadosPesquisa->itemRetornado.chave < 0)
            printf("\nA chave requisitada nao foi encontrada no arquivo!");
        printf("\nQuantidade de acessos ao arquivo: %d", dadosPesquisa->numeroDeAcessos);
        printf("\nQuantidade de comparacoes entre chaves: %d", dadosPesquisa->numeroDeComparacoes);
        printf("\nTempo de busca: %.10lf", dadosPesquisa->tempoDecorrido);
        if(entrada.argOpcional)
            printf("\nA chave requisitada foi %d, a encontrada foi %d, que contem como dado1 %ld", entrada.chaveDesejada, dadosPesquisa->itemRetornado.chave, dadosPesquisa->itemRetornado.dado1);
        break;
    case 3:
        arq = fopen("arqDesArvBin.bin", "rb");
        if(arq == NULL)
            printf("\nErro ao abrir arquivo");
        dadosPesquisa->itemRetornado = localizaElementoNoArquivo(&arq,  entrada, dadosPesquisa);
        printf("\nPesquisa realizada!");
        if(dadosPesquisa->itemRetornado.chave < 0)
            printf("\nA chave requisitada nao foi encontrada no arquivo!");
        printf("\nQuantidade de acessos ao arquivo: %d", dadosPesquisa->numeroDeAcessos);
        printf("\nQuantidade de comparacoes entre chaves: %d", dadosPesquisa->numeroDeComparacoes);
        printf("\nTempo de busca: %.10lf", dadosPesquisa->tempoDecorrido);
        if(entrada.argOpcional)
            printf("\nA chave requisitada foi %d, a encontrada foi %d, que contem como dado1 %ld", entrada.chaveDesejada, dadosPesquisa->itemRetornado.chave, dadosPesquisa->itemRetornado.dado1);
        break;
    default:
        break;
    }
}



//A pesquisa em si, nao muito complexa
TipoRegistroNormal localizaElementoNoArquivo(FILE** arq, TipoEntradaTerminal entrada, TipoDadosRecolhidos* dadosPesquisa)
{
    TipoRegistroNormal itemObtido;
    TipoRegistroBinario itemRaiz;
    
    clock_t start, end;
    int posicao = 0;
    int condicional = 1;

    dadosPesquisa->numeroDeAcessos = 0;
    dadosPesquisa->numeroDeComparacoes = 0;
    dadosPesquisa->tempoDecorrido = 0;

    //Como uma arvore binaria qualquer, ela pesquisa na raiz, caso a chave desejada seja maior, busca o elemento do apontador a direita para realizar a comparacao
    //Caso menor, busca o da esquerda, até que esbarre em um -1, que representa o valor NULL
    //Esbarrando no -1, retorna o elemento caso as chaves sejam iguais ou o valor -1 como chave, caso o elemento não esteja presente
    start = clock();
    while(condicional)
    {
        fseek(*arq, posicao * sizeof(TipoRegistroBinario), SEEK_SET);
        fread(&itemRaiz, sizeof(TipoRegistroBinario), 1, *arq);
        if(entrada.situacaoDoArquivo == 1)
        {
            if(itemRaiz.chave >= entrada.quantidadeDeRegistros)
            {
                itemObtido.chave = -1;
                end = clock();
                dadosPesquisa->tempoDecorrido =  ((double) (end - start)) / CLOCKS_PER_SEC;
                return itemObtido;
            }
        }
        else if(entrada.situacaoDoArquivo == 2)
        {
            if(itemRaiz.chave < NUMERODEREGISTROS - entrada.quantidadeDeRegistros - 1)
            {
                itemObtido.chave = -1;
                end = clock();
                dadosPesquisa->tempoDecorrido =  ((double) (end - start)) / CLOCKS_PER_SEC;
                return itemObtido;
            }
        }
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

