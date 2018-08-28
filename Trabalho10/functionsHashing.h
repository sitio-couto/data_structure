//VINICIUS COUTO ESPINDOLA
//RA: 188115
#ifndef _FUNCTIONS
#define _FUNCTIONS

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
			printf("valor para %lu: %i\n", locale->key, locale->value );
			return;
		}
		locale = locale->prox;
	}
	
	printf("%lu nao existe\n", key );
	
	return;
}

void discard( hashNode **hashTable , uli key ){
	hashNode *aux, **locale = &hashTable[hashing( key )];
	
	while( (*locale) != NULL ){
		
		if( (*locale)->key == key ){
			aux = (*locale)->prox;
			free( *locale );
			(*locale) = aux;
		}else{
			locale = &(*locale)->prox;
		}
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
			}while( aux != NULL );
		}
	}
	
	free( hashTable );
	
	return;
}

#endif
