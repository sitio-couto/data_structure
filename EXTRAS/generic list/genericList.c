//VINICIUS COUTO ESPINDOLA
//RA: 188115
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "genericList.h"

int main( void ){
	char command;
	list *l;
	int check = TRUE, structType;
	void *data;
	scanf(" %i", &structType );

	if( structType == 1 ){
		l = initList( &free_1 , &compare_1 , &print_1 );
		while ( check ){
			scanf(" %c", &command );
			switch( command ){
				case 'I':
					data = malloc( sizeof( int ) );
					scanf(" %i", data );
					insertList( l , data );
					break;
				case 'R':
					data = malloc( sizeof( int ) );
					scanf(" %i", data );
					removeList( l , data );
					break;
				case 'P':
					printList( l );
					free( data );
					printf("\n");
					l = NULL; data = NULL;
					check = FALSE;
					break;
			}
		}
	}else if( structType == 2 ){
		l = initList( &free_2 , &compare_2 , &print_2 );
		while ( check ){
			scanf(" %c", &command );
			switch( command ){
				case 'I':
					data = malloc( sizeof( nameNode ) );
					scanf(" %i %[^\n]", &((nameNode*)data)->age, ((nameNode*)data)->name );
					insertList( l , data );
					break;
				case 'R':
					data = malloc( sizeof( nameNode ) );
					scanf(" %[^\n]", ((nameNode*)data)->name );
					removeList( l , data );
					break;
				case 'P':
					printList( l );
					free( data );
					printf("\n");
					l = NULL; data = NULL;
					check = FALSE;
					break;
			}
		}
	}

	return 0;
}

//GENERIC FUNCTIONS//
list *initList
(
	void (*freeData)( void * ),
	int (*compareData)( void * , void *),
	void (*printData)( void * )
)
{
	list *l = malloc( sizeof( list ) );
	l->head = NULL;
	l->freeData = freeData;
	l->compareData = compareData;
	l->printData = printData;

	return l;
}

void insertList( list *l , void* data ){
	node *newNode = malloc( sizeof( node ) );
	newNode->data = data; newNode->nodeProx = NULL;
	node **auxiliar = &l->head;
	
	while( (*auxiliar) != NULL ){
		auxiliar = &(*auxiliar)->nodeProx;
	}
	
	(*auxiliar) = newNode;
}

void removeList( list *l , void *data ){
	node *aux, **current = &l->head;

	while( (*current) != NULL ){
		if( l->compareData( (*current)->data , data ) ){
			l->freeData( (*current)->data );
			aux = (*current)->nodeProx;
			free( (*current) );
			(*current) = aux;
		}
		if( (*current) == NULL ){ break; }
   	current = &(*current)->nodeProx;
	}

}

void printList( list *l ){
  node **current = &l->head;
  
  while( (*current) != NULL ){
		l->printData( (*current)->data );
		current = &(*current)->nodeProx;
	}
	
	freeList( l );
}

void freeList( list *l ){
  node *aux, **current = &l->head;

	while( 1 ){
		l->freeData( (*current)->data );
		aux = (*current)->nodeProx;
		free( (*current) );
		(*current) = aux;
		if( (*current) == NULL ){ break; }
		current = &(*current)->nodeProx;
	}

}

//CASE-1 FUCTIONS//main
void free_1( void *data ){
  free( data );
}

int compare_1( void *element , void *input ){
	return (*(int*)element) == (*(int*)input);
}

void print_1( void *data ){
	printf("%i\n", *(int*)data );
}

//CASE-2 FUNCTIONS//main
void free_2( void *data ){
	free( data );
}

int compare_2( void *element , void *input ){
	return !strcmp( ((nameNode*)element)->name , ((nameNode*)input)->name ); 
}

void print_2( void *data ){
	printf("%i, %s\n", ((nameNode*)data)->age, ((nameNode*)data)->name );
}
