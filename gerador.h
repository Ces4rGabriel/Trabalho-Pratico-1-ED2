#ifndef GERADOR_H
#define GERADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define tam_str 50
typedef struct{
    int chave;
    long dado1;
    char dado2[50]; 
}registros;

void gerador(int, int);

void crescente(int);

void descrescente(int);

#endif