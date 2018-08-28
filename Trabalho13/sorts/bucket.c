#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
#define OVERTIME 30

typedef struct vector{
	int size;
	int *vet;
	int *auxVet;
}vector;

void bucketSort( vector dummy );

int main( void ){
	vector dummy; 
	int i;
	
	scanf(" %i", &dummy.size );
	dummy.vet = malloc( sizeof( int )*dummy.size );
	dummy.auxVet = malloc( sizeof( int )*dummy.size );
	for( i=0 ; i<dummy.size ; ++i ){
		scanf(" %i", &dummy.auxVet[i] );
		dummy.vet[i] = dummy.auxVet[i];
	}
	
	bucketSort( dummy );
	
	for( i=0 ; i<dummy.size-1 ; ++i ){
		if( dummy.vet[i] > dummy.vet[i+1] ){
			printf("\nERROR\n"); return;
		}
	}
	
	return;
}

typedef struct bucketNode{
	int value;
	struct bucketNode *next;
}bucketNode;

void bucketSort( vector dummy ){
	int i, pos = 0;
	bucketNode *node, *prox, **temp, **bucket = calloc(sizeof(bucketNode*) , 2*dummy.size );
	int place( int value ){
		if( value < 0 ){ return (value%dummy.size) + (dummy.size-1); }
		else{ return (value*dummy.size)/; }
	}
	
	
	for( i=0 ; i<dummy.size ; ++i ){
		temp = &bucket[ place( dummy.vet[i] ) ];
		node = malloc( sizeof( bucketNode ) );
		node->value = dummy.vet[i];
		node->next = NULL;
		while( 1 ){
			if( (*temp) == NULL ){
				(*temp) = node; 
				break; 
			}else if( (*temp)->value > node->value ){
				node->next = (*temp);
				(*temp) = node;
				break;
			}
			temp = &(*temp)->next;
		}
	}
	
	for( i=0 ; i<(2*dummy.size - 1) ; ++i ){
		node = bucket[i];
		while( node != NULL ){
			prox = node->next;
			dummy.vet[pos] = node->value;
			++pos;
			free( node );
			node = prox;
		}
	}
	free( bucket );
	
	return;
}




