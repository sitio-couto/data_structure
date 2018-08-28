#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int n;
	struct node *nodeProx;
}node;

int main(void){
	int i, tamanho = 10;
	node *HEAD = NULL, *defeito;
	node **auxiliar = &HEAD;
	
	for( i=1 ; i<=tamanho ; ++i ){
		(*auxiliar) = malloc(sizeof(node));
		if( i == 10 ){
			defeito = (*auxiliar);
		}
		(**auxiliar).n = i;
		auxiliar = &(**auxiliar).nodeProx;
	}
	(*auxiliar) = defeito;

	node *auxPrint = HEAD;
	int count = 0;
	do{
		printf("%i ", (*auxPrint).n );
		auxPrint = (*auxPrint).nodeProx;
		++count;
		if( count == 25 ){ break; }
	}while( auxPrint != HEAD );
	printf("\n");
	
	int j, k;
	node *aux = HEAD, **vetor = malloc( sizeof(node*) );
	
	for( j=1 ; j>0 ; ++j ){
		vetor = realloc( vetor , sizeof(node*)*j );
		aux = (*aux).nodeProx;
		vetor[j-1] = aux;
		for( k=0 ; k<j ; ++k ){
			if( (*aux).nodeProx == vetor[k] ){
				(*aux).nodeProx = HEAD;
				j = -1;
				break;
			}
		}	
	}
	
	auxPrint = HEAD;
	count = 0;
	do{
		printf("%i ", (*auxPrint).n );
		auxPrint = (*auxPrint).nodeProx;
		++count;
		if( count == 25 ){ break; }
	}while( auxPrint != HEAD );
	printf("\n");
	
	return 0;
}
