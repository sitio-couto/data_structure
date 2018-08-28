#include<stdio.h>
#include<stdlib.h>

typedef struct no{
	int numero;
	struct no *proximo;
	struct no *anterior;
}no;

no* criarLista(void);

int main(void){
	no *cabeca;
	
	cabeca = criarLista();
	
	return 0;
}


no* criarLista(void){
	int i, qntElementos;
	no *cabeca, *auxiliar;
	cabeca = malloc(sizeof(no));
	cabeca->numero = 1;
	cabeca->anterior = NULL;
	auxiliar = cabeca;
	
	scanf(" %i", &qntElementos);
	for( i=2 ; i<=qntElementos ; ++i ){
		auxiliar->proximo = malloc(sizeof(no));
		auxiliar->proximo->anterior = auxiliar;
		auxiliar = auxiliar->proximo;
		auxiliar->numero = i;
	}
	auxiliar->proximo = NULL;
	
	return cabeca;
}
