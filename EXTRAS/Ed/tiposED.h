#ifndef _PRE_DEFINICOES
#define _PRE_DEFINICOES

typedef struct no{
	int i;
	int j;
	struct no *prox;
}no;

typedef struct fila{
	no *comeco;
	no *fim;
}fila;

typedef struct dados{
	int **matR;
	char **matM;
	int colunas;
	int linhas;
}dados;

void inicializarFila( fila *Q );
int filaVazia( fila *Q );
void inserirNo( fila *Q , int i , int j );
void removerNo( fila *Q );

char **criar_matM( int linhas , int colunas );
int **criar_matR( int linhas , int colunas );
void rotular( dados *info , fila *Q );
void componente( fila *Q , dados *info , int i , int j , int r );
void adjacente( fila *Q , dados *info , int i , int j , int r );
int dentroDoLimite( dados *info , int i , int  j );
void imprimir( dados *info );

#endif
