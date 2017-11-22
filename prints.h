//Guilherme Bastos de Oliveira

#include "csv_lib.h"

//imprime campo na tela
void printCampo(int px, int py, int y, int x, celula tabela[100][26]);

//imprime seletor na tela
void printSeletor(int x, int y, int ix, int iy, int telax, int telay, celula tabela[100][26]);

//imprime os indices na tela
void printBorda(int y, int x, int posx, int posy);

//imprime o conteudo salvo na memória
void printConteudo(int y, int x, int ix, int iy, celula tabela[100][26]);

//imprime area selecionada pela ancora
void printAncora(int selx, int sely, int ancx, int ancy, int ix, int iy, int x, int y, celula tabela[100][26]);
