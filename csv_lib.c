//Guilherme Bastos de Oliveira

#include "csv_lib.h"
#include <stdlib.h>
#include <string.h>

#define maxCampo 256

unsigned char *leCampo(FILE *arq){
	//lê campo, salva o valor em uma string alocada e retorna o ponteiro para essa string
	unsigned char ch = fgetc(arq);
	unsigned char *valor = (unsigned char *)malloc(255 * sizeof(unsigned char));
	int i = 0, fim = 0;
	if((ch == ',') || (ch == '\n') || (ch == EOF)){
		fseek(arq, -1, SEEK_CUR);
		return valor;
	}
	if(ch == '"'){
		while(!fim){
			ch = fgetc(arq);
			if(ch == '"'){
				char virg = fgetc(arq);
				if((virg == ',') || (virg == '\n') || (virg == EOF)){
					fim = 1;
				} else{
					fseek(arq, -1, SEEK_CUR);
				}
			}
			if((ch == '\n') && !fim){
				ch = ' ';
			}
			if(!fim){
				valor[i] = ch;
				i++;
			}
		}
	} else {
		do {
			if(ch == '"'){
				ch = '\'';
			}
			valor[i] = ch;
			i++;
			ch = fgetc(arq);
		} while((ch != ',') && (ch != '\n') && (!feof(arq)));
	}
	fseek(arq, -1, SEEK_CUR);
	valor[i+1] = '\0';
	return valor;
}

void imprimeCSV(FILE *arq, celula tabela[100][26]){
	rewind(arq);
	for(int i = 0; i < 100; i++){
		for(int j = 0; j < 25; j++){
			int v = 0;
			//verifica o tipo de celula e imprime de acordo
			switch(tabela[i][j].tipo){
				case 's':
				case 'f':
					for(unsigned int k = 0; k < strlen((const char *)tabela[i][j].str); k++){
						if((tabela[i][j].str[k] == ',') != (tabela[i][j].str[k] == '"')){
							v = 1;
						}
					}
					if(v){
						fprintf(arq, "\"%s\",", tabela[i][j].str);
					} else {
						fprintf(arq, "%s,", tabela[i][j].str);
					}
					break;
				case 'i':
					fprintf(arq, "%lld,", tabela[i][j].inteiro);
					break;
				case 'l':
					fprintf(arq, "%f,", tabela[i][j].pflu);
					break;
				case 'n':
					fprintf(arq, ",");
					break;
			}
		}
		int v = 1;
		//imprime o ultimo elemento de cada linha para evitar virgula extra
		switch(tabela[i][25].tipo){
			case 's':
			case 'f':
				for(unsigned int k = 0; k < strlen((const char *)tabela[i][25].str); k++){
					if((tabela[i][25].str[k] == ',') != (tabela[i][25].str[k] == '"')){
						v = 1;
					}
				}
				if(v){
					fprintf(arq, "\"%s\"", tabela[i][25].str);
				} else {
					fprintf(arq, "%s", tabela[i][25].str);
				}
				break;
			case 'i':
				fprintf(arq, "%lld", tabela[i][25].inteiro);
				break;
			case 'l':
				fprintf(arq, "%f", tabela[i][25].pflu);
				break;
		}
		fprintf(arq, "\n");
	}
}

void leCSV(FILE *fi, celula tabela[100][26]){
	char ch = 0, tipo;
	int lin = 0, col = 0;

	//lê arquivo csv na memória
	while(ch != EOF){
		fseek(fi, -1, SEEK_CUR);
		unsigned char *campo;
		campo = leCampo(fi);
		tipo = tipoCelula(campo, strlen((const char *)campo));
		tabela[lin][col].tipo = tipo;
		switch (tipo) {
			case 's':
			case 'f':
				strcpy((char*)tabela[lin][col].str,(const char*)campo);
				break;
			case 'i':
				tabela[lin][col].inteiro = atoll((const char *)campo);
				break;
			case 'l':
				tabela[lin][col].pflu = atof((const char *)campo);
				break;
		}
		memset(campo,0,strlen((const char*)campo));
		ch = fgetc(fi);

		//atualiza indices de acordo com o ultima char lido
		if(ch == ','){
			col++;
		}
		if(ch == '\n'){
			lin++;
			col = 0;
		}
		free(campo);
		ch = fgetc(fi);
	}
}
