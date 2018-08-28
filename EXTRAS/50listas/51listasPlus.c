//VINICIUS COUTO ESPINDOLA
//RA: 188115

#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	double x;
	struct node *nodeProx;
}node;

node* insertNode( node *HEAD );
node* removeNode( node *HEAD );
node* free_end( node *HEAD );
node* invertList( node *HEAD );
node* transposeList( node *HEAD );
void printList( node *HEAD );

int main( void ){
	char command;
	int check = 0;
	node *HEAD = NULL;
	
	while(!check){
		scanf(" %c", &command );
		switch(command){
			case 'i':
				HEAD = insertNode( HEAD );
				break;
			case 'r':
				HEAD = removeNode( HEAD );
				break;
			case 'p':
				printList( HEAD );
				break;
			case 'v':
				HEAD = invertList( HEAD );
				break;
			case 'x':
				HEAD = transposeList( HEAD );
				break;
			default:
				HEAD = free_end( HEAD );
				check = 1;
				break;
		}
	}
	
	return 0;
}

node* insertNode( node *HEAD ){
	int i, posicao;
	double valor;
	scanf(" %i %lf", &posicao, &valor );
	node **auxPosicao, *auxTemporaria;
	auxPosicao = &HEAD;

	for( i=0 ; i<=posicao ; ++i ){
		if( *auxPosicao == NULL ){
			while( (*auxPosicao) == NULL ){
				*auxPosicao = malloc(sizeof(node));
			}
			(**auxPosicao).x = valor;
			(**auxPosicao).nodeProx = NULL;
			break;
		}else if( i == posicao ){
			auxTemporaria = *auxPosicao;
			(*auxPosicao) = NULL;
			while( (*auxPosicao) == NULL ){
				*auxPosicao = malloc(sizeof(node));
			}
			(**auxPosicao).x = valor;
			(**auxPosicao).nodeProx = auxTemporaria;
		}else{
			auxPosicao = &(**auxPosicao).nodeProx;
		}
	}
	
	return HEAD;
}

node* removeNode( node *HEAD ){
	int posicao, i;
	scanf(" %i", &posicao );
	node **auxPosicao, *auxTemporaria;
	auxPosicao = &HEAD;
	
	for( i=0 ; i<=posicao ; ++i ){
		if( *auxPosicao == NULL ){
			break;
		}else if( i == posicao ){
			auxTemporaria = (**auxPosicao).nodeProx;
			free(*auxPosicao);
			(*auxPosicao) = auxTemporaria;
			break;
		}else{
			auxPosicao = &(**auxPosicao).nodeProx;
		}
	}
	
	return HEAD;
}

void printList( node *HEAD ){
	node *auxPrint = HEAD;
	
	if( auxPrint == NULL ){
		printf("\n");
	}else{
		while( auxPrint != NULL ){
			printf("%.2lf ", (*auxPrint).x );
			auxPrint = (*auxPrint).nodeProx;
		}
		printf("\n");
	}
	
}

node* free_end( node *HEAD ){
	node *auxApagador;
	
	while( HEAD != NULL ){
		auxApagador = (*HEAD).nodeProx;
		free( HEAD );
		HEAD = auxApagador;
	}

	return HEAD;	
}

node* transposeList( node *HEAD ){
	int i = 0, inicio, termino, posicao;
	short int check1, check2, check3;
	scanf(" %i %i %i", &inicio, &termino, &posicao );
	node **auxPosicao, **auxAtual, **auxAnterior, *auxInicio, *auxFim;
	auxPosicao = &HEAD; auxAtual = &HEAD;

	if( posicao<inicio || posicao>(termino+1) && HEAD!=NULL ){
		while( check1==0 || check2==0 || check3==0 ){
			if( i==posicao ){
				++check1;
			}else if( check1==0 ){
				auxPosicao = &(**auxPosicao).nodeProx;
			}
			
			if( i==inicio && i!=termino ){
				auxInicio = (*auxAtual);
				auxAnterior = auxAtual;
				++check2;
			}else if( i==termino && i!=inicio ){
				auxFim = (**auxAtual).nodeProx;
				++check3;
			}else if( i==inicio && i==termino){
				auxInicio = (*auxAtual);
				auxAnterior = auxAtual;
				auxFim = (*auxAtual);
				++check2;
				++check3;
			}else if( check2==0 || check3==0 ){
				auxAtual = &(**auxAtual).nodeProx;
			}
			
			++i;
		}
	
	
		(*auxAnterior) = (*auxFim).nodeProx;
		(*auxFim).nodeProx = (*auxPosicao);
		(*auxPosicao) = auxInicio;
	}
	
	return HEAD;
}

node* invertList( node *HEAD ){
	int inicio, termino, i;
	scanf(" %i %i", &inicio, &termino );
	
	if( HEAD!=NULL && inicio!=termino ){
		node **auxInicio = &HEAD, *auxFim, *auxEsquerda, *auxAtual, *auxDireita; 
		auxEsquerda = HEAD; auxAtual = (*HEAD).nodeProx;
		auxDireita = (*HEAD).nodeProx->nodeProx;
	
		for( i=0 ; i<=termino ; ++i){
			if( i==inicio ){
				for( i=(i+1) ; i<termino ; ++i ){
					(*auxAtual).nodeProx = auxEsquerda;
					auxEsquerda = auxAtual;
					auxAtual = auxDireita;
					auxDireita = (*auxDireita).nodeProx;
				}
				(*auxAtual).nodeProx = auxEsquerda;
				(**auxInicio).nodeProx = auxDireita;
				(*auxInicio) = auxAtual;
				break;
			}else{
				auxInicio = &(**auxInicio).nodeProx;
				auxEsquerda = (*auxEsquerda).nodeProx;
				auxAtual = (*auxAtual).nodeProx;
				auxDireita = (*auxDireita).nodeProx;
			}
		}
	}
	
	return HEAD;
}






















