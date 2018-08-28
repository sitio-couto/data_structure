//VINICIUS COUTO ESPINDOLA
//RA: 188115
#include<stdio.h>
#include<stdlib.h>

#include "typesHashing.h"
#include "functionsHashing.h"

int main( void ){
	char command;
	hashNode **hashTable = calloc( sizeof( hashNode* ) , HASH_SIZE );
	uli key;
	int value;
	
	while( 1 ){
		
		scanf(" %c", &command );
		if( command == 'i' ){
			scanf(" %lu %i", &key , &value );
			insert( hashTable , key , value );			
		}else if( command == 'b' ){
			scanf(" %lu", &key );
			seek( hashTable , key );
		}else if( command == 'r' ){
			scanf(" %lu", &key );
			discard( hashTable , key );
		}else if( command == 'f' ){
			releaseMemory( hashTable );
			hashTable = NULL;
			break;
		}
	}
	
	return 0;
}


