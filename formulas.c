//Guilherme Bastos de Oliveira

#include "formulas.h"
#include <string.h>
#include <stdlib.h>

int valida(int x, int y, celula tabela[100][26]){
	//realiza varios teste para identificar se a formula é valida ou não

	unsigned char a[127], b[127], op;
	memset(a, 0, 127 * sizeof(unsigned char));
	memset(b, 0, 127 * sizeof(unsigned char));

	int i = 1, j, len = strlen((const char *) tabela[x][y].str);
	int xa, xb, ya, yb, numba = 0, numbb = 0;

	//encontra primeiro operando
	while(!((tabela[x][y].str[i] == '+') || (tabela[x][y].str[i] == '-') || (tabela[x][y].str[i] == '/') || (tabela[x][y].str[i] == '*'))){
		a[i-1] = tabela[x][y].str[i];
		if(a[i-1] >= 48 && a[i-1] <=  57){
			numba = 1;
		}
		if(i > len){
			return 0;
		}
		i++;
	}

	op = tabela[x][y].str[i];
	i++;
	j = i;

	//encontra segundo
	while(j < len){
		b[j-i] = tabela[x][y].str[j];
		if(b[j-i] >= 48 && b[i-1] <=  57){
			numbb = 1;
		}
		j++;
	}

	if((!numbb) || (!numba)){
		return 0;
	}

	if(a[0] >= 65 && a[0] <= 90){
		ya = a[0] - 65;
		a[0] = a[1];
		a[1] = a[2];
		a[2] = a[3];
		xa = atoi((const char *)a)-1;
		if((ya ==y && xa == x) || !xa){
			return 0;
		}
		//testa o tipo de celula apontada
		if(!((tabela[xa][ya].tipo == 'l') || (tabela[xa][ya].tipo == 'i') || (tabela[xa][ya].tipo == 'f'))){
			return 0;
		}
	}


	if(b[0] >= 65 && b[0] <= 90){
		yb = b[0] - 65;
		b[0] = b[1];
		b[1] = b[2];
		b[2] = b[3];
		xb = atoi((const char *)b)-1;
		if((yb ==y && xb == x) || !xb){
			return 0;
		}
		//testa o tipo de celula apontada
		if(!((tabela[xb][yb].tipo == 'l') || (tabela[xb][yb].tipo == 'i') || (tabela[xb][yb].tipo == 'f'))){
			return 0;
		}
	}

	//caso não encontre o operador é invalida
	switch(op){
		case '+':
		case '-':
		case '/':
		case '*':
			break;
		default:
			return 0;
			break;
	}

	//caso não tenha segundo operando é invalida
	if(j == i){
		return 0;
	}

	return 1;
}

float calcFormula(int x, int y, celula tabela[100][26]){
	unsigned char a[127], b[127], op;
	memset(a, 0, 127 * sizeof(unsigned char));
	memset(b, 0, 127 * sizeof(unsigned char));

	int i = 1, j, len = strlen((const char *) tabela[x][y].str);
	int xa, xb, ya, yb;
	float va = 0, vb = 0, ca = 0, cb = 1;

	tabela[x][y].tipo = 'n';

	//encontra primeiro operando
	while(!((tabela[x][y].str[i] == '+') || (tabela[x][y].str[i] == '-') || (tabela[x][y].str[i] == '/') || (tabela[x][y].str[i] == '*'))){
		a[i-1] = tabela[x][y].str[i];
		i++;
	}

	//salva operador
	op = tabela[x][y].str[i];
	i++;
	j = i;

	//encontra segundo operando
	while(j < len){
		b[j-i] = tabela[x][y].str[j];
		j++;
	}

	//encontra coordenados ou valor
	if(a[0] >= 65 && a[0] <= 90){
		ya = a[0] - 65;
		a[0] = a[1];
		a[1] = a[2];
		a[2] = a[3];
		ca = 1;
		xa = atoi((const char *)a)-1;
	} else {
		va = atof((const char *) a);
	}

	//encontra coordenados ou valor
	if(b[0] >= 65 && b[0] <= 90){
		yb = b[0] - 65;
		b[0] = b[1];
		b[1] = b[2];
		b[2] = b[3];
		cb = 1;
		xb = atoi((const char *)b)-1;
	} else {
		vb = atof((const char *) b);
	}

	//encontra o valor das celulas apontadas
	if(ca && tabela[xa][ya].tipo == 'l'){
		va = tabela[xa][ya].pflu;
	} else if(ca && tabela[xa][ya].tipo == 'i'){
		va = (float)tabela[xa][ya].inteiro;
	}else if(ca && tabela[xa][ya].tipo == 'f'){
		va = calcFormula(xa, ya, tabela);
	}

	if(cb && tabela[xb][yb].tipo == 'l'){
		vb = tabela[xb][yb].pflu;
	} else if(cb && tabela[xb][yb].tipo == 'i'){
		vb = (float)tabela[xb][yb].inteiro;
	} else if(cb && tabela[xb][yb].tipo == 'f'){
		vb = calcFormula(xb, yb, tabela);
	}

	//realiza operação referente ao operador
	switch(op){
		case '+':
			va = va + vb;
			break;
		case '-':
			va = va - vb;
			break;
		case '/':
			va = va / vb;
			break;
		case '*':
			va = va * vb;
			break;
	}

	tabela[x][y].tipo = 'f';

	return va;
}
