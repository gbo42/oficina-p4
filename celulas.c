//Guilherme Bastos de Oliveira

#include "celulas.h"

char tipoCelula(unsigned char *valor, int tam){
	//se str tiver tamanho zero é do tipo nulo
	if(!tam){
		return 'n';
	}
	//tipo base é string
	char tipo = 's', num = 1, pontos = 0;
	for(int i = 0; i < tam; i++){
		if(valor[i] == '.'){
			pontos++;
		} else if((valor[i] > 57) || (valor [i] < 48)){
			num = 0;
		}
	}

	if(num){
		if(!pontos){
			//se tiver só numeros é inteiro
			tipo = 'i';
		//se tiver só numeros e 1 ponto é float
		} else if (pontos == 1){
			tipo = 'l';
		}
	}

	//se começar com = é função
	if(valor[0] == '='){
		tipo = 'f';
	}

	return tipo;
}
