#ifndef GERADOR_H
#define GERADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct{
    int chave;
    long dado1;
    char dado2[50]; 
}registros;

void gerador(int, int );


#endif