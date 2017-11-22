//Guilherme Bastos de Oliveira

#include "prints.h"
#include "formulas.h"
#include <ncurses.h>

void printCampo(int px, int py, int y, int x, celula tabela[100][26]) {
	//imprime campo de acordo com seu tipo
	switch(tabela[x][y].tipo){
		case 'f':
			if(valida(x, y, tabela)){
				mvprintw(py,px, "%8.2f", calcFormula(x, y, tabela));
			} else {
				mvprintw(py, px, "    ERRO");
			}
			break;
		case 's':
			mvprintw(py,px, "%8s", tabela[x][y].str);
			break;
		case 'i':
			mvprintw(py,px, "%8d", tabela[x][y].inteiro);
			break;
		case 'l':
			mvprintw(py,px, "%8.2f", tabela[x][y].pflu);
			break;
		case 'n':
			mvprintw(py,px, "        ");
			break;
	}
}

void printSeletor(int x, int y, int ix, int iy, int telax, int telay, celula tabela[100][26]){
	attron(COLOR_PAIR(1));
	printCampo((1+x-ix)*8, y+1-iy, x, y, tabela);
}

void printBorda(int y, int x, int posx, int posy){
	//imprime as bordas da planilha (indices A-Z, 1-100)
	attron(COLOR_PAIR(1));
	int i = 0;
	for(i = 0; (i < (x/8)-1) && (i+posx < 26); i++){
		mvprintw(0,(i+1)*8,"   %c    ",i+65+posx);
	}

	for(int i = 1; i < y-2 && i < 100; i++){
		mvprintw(i,0,"%7d ",i+posy);
	}

	//limpa duas ultimas linhas da tela
	attron(COLOR_PAIR(2));
	move(y-1, 0);
	for(int i = 0; i < x; i++){
		printw(" ");
	}
	move(y-2, 0);
	for(int i = 0; i < x; i++){
		printw(" ");
	}
}

void printConteudo(int y, int x, int ix, int iy, celula tabela[100][26]){
	attron(COLOR_PAIR(2));
	//imprime os campos salvos na memória
	for(int i = 0; i < (x/8)-1; i++){
		for(int j = 1; j < y-2; j++){
			printCampo((i+1)*8, j, i+ix, j-1+iy, tabela);
		}
	}
}

void printAncora(int selx, int sely, int ancx, int ancy, int ix, int iy, int x, int y, celula tabela[100][26]){
	int sx, sy, ax, ay;
	if(ancx < selx){
		ax = selx;
		sx = ancx;
	} else {
		ax = ancx;
		sx = selx;
	}

	if(ancy < sely){
		ay = sely;
		sy = ancy;
	} else {
		ay = ancy;
		sy = sely;
	}

	//imprime area selecionada pela ancora
	for(int i = 0; i <= ax-sx; i++){
		for(int j = 0; j <= ay-sy; j++){
			printSeletor(i+sx, j+sy, ix, iy, x, y, tabela);
		}
	}
}
