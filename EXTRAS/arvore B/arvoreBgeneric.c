#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "types.h"
#include "functions.h"

int main( void ){
	char command[20];
	int value, lines;
	node *root = NULL;
	insertTools *tool = calloc( 1 , sizeof( insertTools ) );
	
	scanf(" %i", &lines );
	for( lines=lines ; lines>0 ; --lines ){
		scanf(" %s", command );
		if( !strcmp( "inserir" , command ) ){
			scanf(" %i", &value );
			if( !root ) root = initTree( value );
			else if( insert( root , value , tool ) == -1 ) 
				root = upGrowth( root , tool );	
		}else if( !strcmp( "buscar" , command ) ){
			scanf(" %i", &value );
			found( search( root , value ) );
		}else if( !strcmp( "imprimir", command ) ){
			if( !root->qnt ) printf("vazia");
			else printing( root );
			printf("\n");
		}
		tool->newPage = NULL;
	}
	
	return 0;
}

