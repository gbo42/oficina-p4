//Guilherme Bastos de Oliveira

#include "comandos.h"
#include <string.h>
#include <ncurses.h>
#include <stdlib.h>
#include "csv_lib.h"

void editar(int x, int y, int telax, int telay, celula tabela[100][26]){
	unsigned char ch, valor[255];
	memset(valor, 0, 255 * sizeof(char));
	int i = 0;

	attron(COLOR_PAIR(1));
	mvprintw(telay-1,0,"Edição: ");

	ch = getch();

	//lê entrada a ser salva no campo
	while(ch != ENTER){
		if(ch == CTRL('G')){
			attron(COLOR_PAIR(1));
			i = (i-1)>=0?i-1:0;
			valor[i] = '\0';
		} else {
			valor[i] = ch;
			i++;
		}

		move(telay-1, 9);
		attron(COLOR_PAIR(2));
		for(int i = 9; i < telax; i++){
			printw(" ");
		}

		attron(COLOR_PAIR(1));
		move(telay-1, 0);
		printw("Edição: %s", valor);
		ch = getch();

	}

	//descobri tipo do campo digitado
	char tipo = tipoCelula(valor, strlen((const char *)valor));

	//salva o tipo
	tabela[y][x].tipo = tipo;
	//salva o dado de acordo com o tipo
	switch (tipo) {
		case 's':
		case 'f':
			strcpy((char*)tabela[y][x].str,(const char*)valor);
			break;
		case 'i':
			tabela[y][x].inteiro = atoll((const char *)valor);
			break;
		case 'l':
			tabela[y][x].pflu = atof((const char *)valor);
			break;
	}

	move(telay-1, 0);
	attron(COLOR_PAIR(2));
	for(int i = 0; i < telax; i++){
		printw(" ");
	}
}

void salvar(FILE **fi, celula tabela[100][26], int telax, int telay){
	//caso não exista arquivo pede por nome de um novo arquivo
	if(!*fi){
		attron(COLOR_PAIR(1));
		mvprintw(telay-1,0,"Nome do arquivo a ser criado: ");

		unsigned char ch = getch(), valor[255];
		memset(valor, 0, 255 * sizeof(char));
		int i = 0;

		//lê nome do arquivo a ser criado
		while(ch != ENTER){
			if(ch == CTRL('G')){
				i = (i-1)>=0?i-1:0;
				valor[i] = '\0';
			} else {
				valor[i] = ch;
				i++;
			}

			move(telay-1, 9);
			attron(COLOR_PAIR(2));
			for(int i = 9; i < telax; i++){
				printw(" ");
			}

			attron(COLOR_PAIR(1));
			move(telay-1, 0);
			printw("Nome do arquivo a ser criado: %s", valor);
			ch = getch();

		}
		*fi = fopen((const char*)valor, "w+");
	}

	move(telay-1, 0);
	attron(COLOR_PAIR(2));
	for(int i = 0; i < telax; i++){
		printw(" ");
	}

	//imprime os dados no arquivo
	imprimeCSV(*fi, tabela);
}

void abrir(FILE **fi, celula tabela[100][26], int telax, int telay){
	attron(COLOR_PAIR(1));
	mvprintw(telay-1,0,"Nome do arquivo a ser aberto: ");

	unsigned char ch = getch(), valor[255];
	memset(valor, 0, 255 * sizeof(char));
	int i = 0;

	//lê nome do arquivo a ser aberto
	while(ch != ENTER){
		if(ch == CTRL('G')){
			valor[i] = '\0';
			i = (i-1)>=0?i-1:0;
		} else {
			valor[i] = ch;
			i++;
		}

		move(telay-1, 9);
		attron(COLOR_PAIR(2));
		for(int i = 9; i < telax; i++){
			printw(" ");
		}

		attron(COLOR_PAIR(1));
		move(telay-1, 0);
		printw("Nome do arquivo a ser aberto: %s", valor);
		ch = getch();

	}
	if(*fi){
		fclose(*fi);
	}
	*fi = fopen((const char*)valor, "r+");

	//se não foi possível abrir o arquivo dá erro
	if(!*fi){
		endwin();
		perror("ERRO: Não foi possível abrir arquivo");
		exit(1);
	}
	for(int i = 0; i < 100; i++){
		for(int j = 0; j < 26; j++){
			tabela[i][j].tipo = 'n';
		}
	}

	//lê arquivo na memória
	leCSV(*fi, tabela);

	move(telay-1, 0);
	attron(COLOR_PAIR(2));
	for(int i = 0; i < telax; i++){
		printw(" ");
	}
}

int copia(int selx, int sely, int ancx, int ancy, int dx, int dy, celula tabela[100][26], celula destino[100][26]){
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

	//se a area não couber, não faz nada
	if((ax-sx + dx > 100) || (ay-sy + dy > 26)){
		return 0;
	}

	//copia os dados de uma area de uma tabela para outra
	for(int i = 0; i <= ax-sx; i++){
		for(int j = 0; j <= ay-sy; j++){
			destino[i+dx][j+dy].tipo = tabela[i+sx][j+sy].tipo;
			switch (destino[i+dx][j+dy].tipo) {
				case 'f':
				case 's':
					strcpy((char *)destino[i+dx][j+dy].str,(const char *)tabela[i+sx][j+sy].str);
					break;
				case 'i':
					destino[i+dx][j+dy].inteiro = tabela[i+sx][j+sy].inteiro;
					break;
				case 'l':
					destino[i+dx][j+dy].pflu = tabela[i+sx][j+sy].pflu;
					break;
			}
		}
	}

	return 0;
}
