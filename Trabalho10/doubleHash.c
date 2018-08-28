#include<stdio.h>
#include<stdlib.h>
#define VDD 1
#define FAKE 0
#define SIZE 529489
#define SIZE_2 7151
#define VAZIO -1
#define TIRADO -2

typedef struct dado{
	long long int chave;
	int valor;
}dado;

dado *criaHash( );
int hashDuplo( int j , long long int chave );
int hash_um( long long int chave );
int hash_dois( long long int chave );
void insere( dado hash[] , long long int chave , int valor );
void remover( dado hash[] , long long int chave , int valor );
void busca( dado hash[] , long long int chave );

int main(void){
	dado *hash = criaHash();
	char comando;
	long long int chave;
	int valor, check = VDD;
	
	while(check){
		scanf(" %c", &comando );
		if( comando == 'i' ){
			scanf(" %llu %i", &chave , &valor );
			insere( hash , chave , valor );		
		}else if( comando == 'b' ){
			scanf(" %llu", &chave );
			busca( hash , chave );
		}else if( comando == 'r' ){
			scanf(" %llu", &chave );
			remover( hash , chave , valor );
		}else if( comando == 'f' ){
			free( hash );
			check = FAKE;
		}
	}
	
	return 0;
}

dado *criaHash( ){
	int i;
	dado *hash = malloc( sizeof(dado)*SIZE );
	for( i=0 ; i<SIZE ; ++i ){
		hash[i].chave = VAZIO;
	}
	
	return hash;
}

int hashDuplo( int j , long long int chave ){
	return  ( hash_um( chave ) + j*hash_dois( chave ) )%SIZE ;
}

int hash_um( long long int chave ){
	return (chave%SIZE);
}

int hash_dois( long long int chave ){
	return (chave%SIZE_2);
}

void insere( dado *hash , long long int chave , int valor ){
	int check = VDD, j = -1;
	int posicao; 
	
	while(check){
		++j;
		posicao = hashDuplo( j , chave );
		if( (hash[posicao].chave == chave) || (hash[posicao].chave == VAZIO) ){
			hash[posicao].chave = chave;
			hash[posicao].valor = valor;
			check = FAKE;
		}
	}
	
}

void remover( dado *hash , long long int chave , int valor ){
	int check = VDD, j = -1;
	int posicao;
	
	while(check){
		++j;
		posicao = hashDuplo( j , chave );
		if( hash[posicao].chave == VAZIO ){
			check = FAKE;
		}else if( hash[posicao].chave == chave ){
			hash[posicao].chave = TIRADO;
			check = FAKE;
		}
	}
	
}

void busca( dado *hash , long long int chave ){
	int check = VDD, j = -1;
	int posicao;
	
	while(check){
		++j;
		posicao = hashDuplo( j , chave );
		if( hash[posicao].chave == chave ){
			printf("valor para %lu: %i\n", chave, hash[posicao].valor );
			return;
		}else if( hash[posicao].chave == VAZIO ){
			check = FAKE;
		}
	}
	
	printf("%lu nao existe\n", chave );
	
}








