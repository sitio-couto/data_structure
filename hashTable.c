#include<stdio.h>
#include<stdlib.h>
#define HASH_SIZE 499

typedef unsigned long int uli;

typedef struct hashNode{
	uli key;
	int value;
	struct hashNode *prox;
}hashNode;

int main( void ){
	char command;
	hashNode **hashTable = calloc( sizeof( hashNode* ) , HASH_SIZE );
	uli key;
	int value;
	
	while( 1 ){
		
		scanf(" %c", &command );
		if( command == 'i' ){
			scanf(" %uli %i", &key , &value );
			insert( key , value );			
		}else if( command == 'b' ){
			scanf(" %uli", &key );
			seek( key );
		}else if( command == 'r' ){
			scanf(" %uli", &key );
			discard( hashTable , key );
		}else{
			releaseMemory( hashTable );
			hashTable = NULL;
			break;
		}
	}
	
	return 0;
}

hashNode* alloc( uli key , int value , hashNode *chain ){
	hashNode *newNode = malloc( sizeof( hashNode ) );
	newNode->key = key;
	newNode->value = value;
	newNode->prox = chain;
	
	return newNode;
}

int hashing( uli key ){
	return (key % HASH_SIZE);
}

void insert( hashNode **hashTable , uli key , int value ){
	hashNode *chain = NULL;
	
	if( hashTable[hashing( key )] != NULL ){
		chain = hashTable[hashing( key )];
	}
	
	hashTable[hashing( key )] = alloc( key , value , chain );
	
	return;
}

void seek( hashNode **hashTable , uli key ){
	hashNode *locale = hashTable[hashing( key )];
	
	while( locale != NULL ){
		if( locale->key == key ){
			printf("valor para %uli: %i\n", locale->key, locale->value );
			return;
		}
		locale = locale->prox;
	}
	
	printf("%uli nao existe\n", key );
	
	return;
}

void discard( hashNode **hashTable , uli key ){
	hashNode *aux, **locale = &hashTable[hashing( key )];
	
	while( (*locale) != NULL ){
		if( (*locale)->key == key ){
			aux = (*locale)->prox;
			free( *locale );
			(*locale) = aux;
		}
		locale = &(*locale)->prox;
	}
	
	return;
}

void releaseMemory( hashNode **hashTable ){
	hashNode *aux, *temp;
	int i;
	
	for( i=0 ; i<HASH_SIZE ; ++i ){
		if( hashTable[i] != NULL ){
			aux = hashTable[i];
			hashTable[i] = NULL;
			do{
				temp = aux->prox;
				free( aux );
				aux = temp;
			}while( aux != NULL )
		}
	}
	
	free( hashTable );
	
	return;
}




