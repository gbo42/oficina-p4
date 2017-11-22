//Guilherme Bastos de Oliveira

#include <stdio.h>
#ifndef CELULASH
#define CELULASH
#include "celulas.h"
#endif

//função que lê campo de arquivo csv
unsigned char *leCampo(FILE *arq);

//função que lê arquivo de campo csv para a memória
void leCSV(FILE *fi, celula tabela[100][26]);

//função que escreve no arquivo os dados csv
void imprimeCSV(FILE *arq, celula tabela[100][26]);
