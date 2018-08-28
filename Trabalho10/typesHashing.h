//VINICIUS COUTO ESPINDOLA
//RA: 188115
#ifndef _TYPES
#define _TYPES
#define HASH_SIZE 523

typedef unsigned long int uli;

typedef struct hashNode{
	uli key;
	int value;
	struct hashNode *prox;
}hashNode;

hashNode* alloc( uli key , int value , hashNode *chain );
int hashing( uli key );
void insert( hashNode **hashTable , uli key , int value );
void seek( hashNode **hashTable , uli key );
void discard( hashNode **hashTable , uli key );
void releaseMemory( hashNode **hashTable );

#endif
