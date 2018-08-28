//VINICIUS COUTO ESPINDOLA
//RA: 188115
#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	double n;
	struct node *A;
	struct node *B;
}node;

node* insertNode( node *HEAD );
void printList( node *HEAD );
node *revertNodes( node *HEAD );
node* endNfree( node *HEAD );

int main(void){
	char command;
	int check = 1;
	node *HEAD = NULL;
	
	while(check){
		scanf(" %c", &command );
		switch(command){
			case 'i':
				HEAD = insertNode( HEAD );
				break;
			case 'p':
				printList( HEAD );
				break;
			case 'v':
				HEAD = revertNodes( HEAD );
				break;
			default:
				HEAD = endNfree( HEAD );
				check = 0;
				break;
		}
	}
	
	return 0;
}

//INSERIR.
node* insertNode( node *HEAD ){
	int i, position;
	double valor;
	scanf(" %i %lf", &position, &valor );
	node **auxiliar = &HEAD, *left = NULL, *right = HEAD;

	for( i=0 ; i<=position ; ++i ){
		if( right == NULL || i == position ){
			(*auxiliar) = malloc(sizeof(node));
			(**auxiliar).n = valor;
			(**auxiliar).A = left;
			if( right == NULL ){
				(**auxiliar).B = NULL;
			}else{
				(**auxiliar).B = right;
				if( (*right).A == left ){
					(*right).A = (*auxiliar);
				}else{
					(*right).B = (*auxiliar);
				}
			}
			break;
		}else{
			if( (*right).B != left ){
				auxiliar = &(*right).B;
			}else{
				auxiliar = &(*right).A;
			}
			left = right;
			right = (*auxiliar);
		}
		
	}

	return HEAD;	
}

//IMPRIMIR.
void printList( node *HEAD ){
	node *current = HEAD, *previous = NULL;

	while( current != NULL ){
		printf("%.4lf ", current->n );
		if( (*current).B != previous ){
			previous = current;
			current = (*current).B;
		}else{
			previous = current;
			current = (*current).A;
		}
	}
	printf("\n");
	
} 

//REVERTER NOS.
node *revertNodes( node *HEAD ){
	int i, start, finish;
	scanf(" %i %i", &start, &finish );
	node *left = NULL, **auxLeft = &HEAD, **begin, *startNode = HEAD;
	node *endNode, **end, **auxRight, *right;
	node *trash = NULL;
	
	if( (start != finish) && (HEAD != NULL) ){
		for( i=0 ; i<start ; ++i ){
			if( (*startNode).B != left ){
				auxLeft = &(*startNode).B;
				left = startNode;
				startNode = (*startNode).B;
			}else{
				auxLeft = &(*startNode).A;
				left = startNode;
				startNode = (*startNode).A;
			}
		}
		
		if( (*startNode).A == left ){
			begin = &(*startNode).A;
		}else{
			begin = &(*startNode).B;
		}
		
		right = startNode;
		endNode = left;
		
		for( i=i ; i<=finish ; ++i ){
			if( (*right).B != endNode ){
				endNode = right;
				end = &(*right).B;
				right = (*right).B;
			}else{
				endNode = right;
				end = &(*right).A;
				right = (*right).A;
			}
		}
		
		if( right == NULL ){
			auxRight = &trash;
		}else if( (*right).A == endNode ){
			auxRight = &(*right).A;
		}else{
			auxRight = &(*right).B;
		}
		
		(*begin) = right;
		(*end) = left;
		(*auxLeft) = endNode;
		(*auxRight) = startNode;
	}
	
	return HEAD;
}

//LIBERAR MEMORIA.
node* endNfree( node *HEAD ){
	node *current = HEAD, *following, *previous = NULL;
	
	while( current != NULL ){
		if( (*current).B != previous ){
			following = (*current).B;
		}else{
			following = (*current).A;
		}
		previous = current;
		free( current );
		current = following;
	}

	return NULL;
}









