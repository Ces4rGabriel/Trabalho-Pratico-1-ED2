#include <stdio.h>
#define STRTAM 50
typedef struct{
    int chave;
    long dado1;
    char dado2[STRTAM]; 
}tipoitem;

int main() {
    tipoitem vetor[500];
    FILE *arq = fopen("arq.bin", "rb");
    fread(vetor, sizeof(tipoitem), 500, arq);
    fclose(arq);

    for (int i = 0; i < 500; i++) {
        printf("Chave: %d\n", vetor[i].chave);
    }
    return 0;
}