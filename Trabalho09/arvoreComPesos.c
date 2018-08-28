#include<stdio.h>
#include<stdlib.h>
#include "dadosAcP.h"
#include "funcoesAcP.h"

int main( void ){
	node *root = NULL;
	char currentChar;
	
	while( 1 ){
		scanf(" %c", &currentChar );
		if( feof( stdin ) ){ break; }
		
		root = createTree( &currentChar );
	
		printf("%.3lf\n", pathFinder( root ) );
		
		root = cutDownTree( root );
	}

	return 0;
}


