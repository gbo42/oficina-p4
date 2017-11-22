//Guilherme Bastos de Oliveira

#include <stdio.h>

//struct de célula
typedef struct {
	char tipo;
	union {
		long long int inteiro;
		double pflu;
		unsigned char str[256];
	} ;
} celula;

//retorna o tipo da celula
char tipoCelula(unsigned char *valor, int tam);
