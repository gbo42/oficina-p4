//Guilherme Bastos de Oliveira

#include "prints.h"
#include "formulas.h"
#include "comandos.h"
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define CTRL(x) ((x) & 037)
#define ENTER 10

int main(int argc, char **argv){
	int selx=0, sely=0,ix=0,iy=0,ancx=0,ancy=0,anc=0, cpx, cpy, ctrlc, ctrlx, i = 0, fim = 0;
	celula tabela[100][26], cp[100][26];
	for(int i = 0; i < 100; i++){
		for(int j = 0; j < 26; j++){
			tabela[i][j].tipo = 'n';
		}
	}

	//tenta abrir arquivo
	FILE *fi;
	if(argc == 2){
		fi = fopen(argv[1], "r+");
		if(!fi){
			perror("ERRO: Não foi possível abrir arquivo");
			exit(1);
		}
		leCSV(fi, tabela);
	}

	//inicializações do ncurses
	initscr();
	raw();
	noecho();
	keypad(stdscr, TRUE);
	start_color();
	int y, x;
	getmaxyx(stdscr,y,x);
	curs_set(0);
	assume_default_colors(COLOR_WHITE, COLOR_CYAN);
	init_pair(1, COLOR_CYAN, COLOR_WHITE);
	init_pair(2, COLOR_WHITE, COLOR_CYAN);
	getmaxyx(stdscr,y,x);
	printConteudo(y,x,ix,iy,tabela);
	printBorda(y,x,ix,iy);
	printSeletor(selx, sely, ix, iy, x, y, tabela);
	refresh();

	while(!fim){
		//calcula indices para copia/corte/cola
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
		//espera input de tecla, cada input realiza uma ação
		switch (getch()) {
			//teclas de movimento
			case KEY_LEFT:
				selx = (selx-1)>=0?selx-1:0;
				break;
			case KEY_RIGHT:
				selx = (selx+1)<=25?selx+1:25;
				break;
			case KEY_DOWN:
				sely = (sely+1)<=99?sely+1:99;
				break;
			case KEY_UP:
				sely = (sely-1)>=0?sely-1:0;
				break;
			//tecla de edição de campo
			case ENTER:
				anc = 0;
				editar(selx, sely, x, y, tabela);
				break;
			//tecla para sair do programa
			case CTRL('q'):
				attron(COLOR_PAIR(1));
				move(y-1, 0);
				printw("Deseja salvar(S/n)?");
				if(getch() != 'n'){
					salvar(&fi, tabela, x, y);
				}
				fim = 1;
				break;
			//tecla para salvar aquivo
			case CTRL('s'):
				anc = 0;
				salvar(&fi, tabela, x, y);
				break;
			//tecla para abrir novo arquivo
			case CTRL('r'):
				anc = 0;
				abrir(&fi, tabela, x, y);
				break;
			//tecla para definir ancora
			case CTRL(' '):
				if(!anc){
					ancx = selx;
					ancy = sely;
					anc = 1;
				} else {
					anc = 0;
				}
				break;
			//tecla para copiar area
			case CTRL('c'):
				copia(sely, selx, ancy, ancx, 0, 0, tabela, cp);
				cpx = ax-sx;
				cpy = ay-sy;
				anc = 0;
				ctrlc = 1;
				break;
			//tecla para cortar area
			case CTRL('x'):
				copia(sely, selx, ancy, ancx, 0, 0, tabela, cp);
				cpx = ax-sx;
				cpy = ay-sy;
				anc = 0;
				for(int i = 0; i <= ax-sx; i++){
					for(int j = 0; j <= ay-sy; j++){
						tabela[j+sy][i+sx].tipo = 'n';
					}
				}
				ctrlx = 1;
				break;
			//tecla para colar area
			case CTRL('v'):
				if(ctrlc || ctrlx){
					copia(0, 0, cpy, cpx, sely, selx, cp, tabela);
					ctrlc = 0;
					ctrlx = 0;
				}
				break;
		}
		if(sely > iy+y-4){
			iy++;
		}
		if(sely < iy){
			iy--;
		}

		if(selx > ix+(x/8)-2){
			ix++;
		}
		if(selx < ix){
			ix--;
		}

		if(!anc){
			ancx = selx;
			ancy = sely;
		}

		//imprime a tela
		getmaxyx(stdscr,y,x);
		printConteudo(y,x,ix,iy,tabela);
		printBorda(y,x,ix,iy);
		printSeletor(selx, sely, ix, iy, x, y, tabela);
		if(anc){
			printAncora(selx, sely, ancx, ancy, ix, iy, x, y, tabela);
		}
		refresh();
		i++;
	}

	endwin();
	return 0;
}
