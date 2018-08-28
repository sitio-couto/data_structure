//VINICIUS COUTO ESPINDOLA
//RA: 188115
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "data.h"
#include "functions.h"

int main( void ){
	node *root = NULL, **stack = NULL;
	int value, end = FALSE;
	string command;
	
	while( !end ){
		scanf(" %s", command );
		
		if( !strcmp( command , "inserir" ) ){
			scanf(" %i", &value );
			insertNode( &root , value );
		}else if( !strcmp( command , "excluir" ) ){
			scanf(" %i", &value );
			removeNode( &root , value );
		}else if( !strcmp( command , "buscar" ) ){
			scanf(" %i", &value );
			search( root , value );
		}else if( !strcmp( command , "minimo" ) ){
			if( !empty( root ) ){ minimum( root ); }
		}else if( !strcmp( command , "maximo" ) ){
			if( !empty( root ) ){ maximum( root ); }
		}else if( !strcmp( command , "pos-ordem" ) ){
			if( !empty( root ) ){ 
				postOrder( root ); 
				printf("\n"); 
			}
		}else if( !strcmp( command , "em-ordem" ) ){
			if( !empty( root ) ){ 
				inOrder( root ); 
				printf("\n"); 
			}
		}else if( !strcmp( command , "pre-ordem" ) ){
			if( !empty( root ) ){ 
				preOrder( root ); 
				printf("\n"); 
			}
		}else if( !strcmp( command , "largura" ) ){
			if( !empty( root ) ){
				stack = malloc( sizeof(node*)*totalNodes( root ) );
				stack[0] = root;
				levelOrder( stack , 0 , 1 );  
				printf("\n");
				free( stack );
			}
		}else if( !strcmp( command , "terminar")){
			freeTree( root ); root = NULL;
			end = TRUE;
		}	
	}
	
	return 0;
}



