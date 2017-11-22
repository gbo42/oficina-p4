//Guilherme Bastos de Oliveira

#ifndef CELULASH
#define CELULASH
#include "celulas.h"
#endif

#define CTRL(x) ((x) & 037)
#define ENTER 10

//função para editar campo
void editar(int x, int y, int telax, int telay, celula tabela[100][26]);

//função para salvar arquivo
void salvar(FILE **fi, celula tabela[100][26], int telax, int telay);

//função para abrir novo arquivo
void abrir(FILE **fi, celula tabela[100][26], int telax, int telay);

//função para copiar dados de uma tabela para outra
int copia(int selx, int sely, int ancx, int ancy, int dx, int dy, celula tabela[100][26], celula destino[100][26]);
