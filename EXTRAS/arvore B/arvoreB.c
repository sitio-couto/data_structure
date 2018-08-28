#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
	int qnt;
	int key[2];
	struct node *child[3];
}node;

void split( node *r , int id );
void splitRoot( node *r );
int compare( const void *a , const void *b );
int input( node *r , int value );
int search( node *r , int value );
void press( node *r );

int pivot;
node *aux, *newPage = NULL;

int main( void ){	
	char command[15];
	int i, lines, value;
	node *root = calloc( 1 , sizeof( node ) );
	
	scanf(" %i", &lines );
	for( i=0 ; i<lines ; ++i ){
		scanf(" %s", command );
		if( !strcmp( command , "buscar" ) ){
			scanf(" %i", &value );
			if( search( root , value ) ){
				printf(":)\n");
			}else{
				printf(":(\n");
			}
		}else if( !strcmp( command , "inserir" ) ){
			scanf(" %i", &value );
			if( input( root , value ) == -1 ){
				newPage = calloc( 1 , sizeof( node ) );
				++newPage->qnt;
				newPage->key[0] = pivot;
				newPage->child[0] = root;
				newPage->child[1] = aux;
				root = newPage;
			}
			newPage = NULL;
		}else if( !strcmp( command , "imprimir" ) ){
			if( !root->qnt ){
				printf("vazia");	
			}else{
				press( root );
			}
			printf("\n");
		}
		newPage = NULL;
	}
	
	return 0;
}

int input( node *r , int value ){
	int i, check;
	if( !r ) return 0;
	
	for( i=0 ; i<r->qnt ; ++i ){
		if( r->key[i] == value ) return 1;
		if( r->key[i] > value ) break;
	}
	
	check = input( r->child[i] , value );
	//printf("\nDONE\n");
	switch( check ){
		case 0:
			if( r->qnt < 2 ){
				++r->qnt;
				if( i == 0 ){
					r->key[1] = r->key[0];
					r->key[0] = value;
				}else{
					r->key[1] = value;
				}
				return 1;
			}else{
				pivot = value;
				split( r , 0 );
				return -1;
			}
		case 1:
			return 1;
		case -1:
			if( r->qnt < 2 ){
				++r->qnt;
				if( pivot < r->key[0] ){
					r->key[1] = r->key[0];
					r->child[2] = r->child[1];
					r->key[0] = pivot;
					r->child[1] = newPage;
				}else{
					r->key[1] = pivot;
					r->child[2] = newPage;
				}
				return 1;
			}else{
				split( r , 1 );
				return -1;
			}
	}
	
	
}

int compare( const void *a , const void *b ){
	return ( *(int*)a - *(int*)b );
}

void split( node *r , int id ){
	int i, vet[3] = { r->key[0] , r->key[1] , pivot };
	newPage = calloc( 1 , sizeof( node ) );
	
	if( id ){
		if( pivot < r->key[0] ){
			newPage->child[0] = r->child[1];
			newPage->child[1] = r->child[2];
			r->child[1] = aux;			
		}else if(  pivot < r->key[1] ){
			newPage->child[0] = aux;
			newPage->child[1] = r->child[2];
		}else{
			newPage->child[0] = r->child[2];
			newPage->child[1] = aux;
		}
		r->child[2] = NULL;
	}
	
	qsort( vet , 3 , sizeof(int) , compare );
	
	--r->qnt;
	r->key[0] = vet[0];
	r->key[1] = 0;
	++newPage->qnt;
	newPage->key[0] = vet[2];
	pivot = vet[1];
	
	aux = newPage;
	
	return;
}

int search( node *r , int value ){
	int i;
	if( (r == NULL) || (r->qnt == 0 ) ) return 0;
	
	for( i=0 ; i<r->qnt ; ++i ){
		if( r->key[i] == value ) return 1;
		if( r->key[i] > value ) break;
	}
	
	return search( r->child[i] , value );
}

void press( node *r ){
	int i;
	if( !r ) return;
	printf("( ");
	
	for( i=0 ; i<r->qnt ; ++i ){
		press( r->child[i] );
		printf("%i ", r->key[i] );
	}
	press( r->child[i] );
	
	printf(") ");
}




