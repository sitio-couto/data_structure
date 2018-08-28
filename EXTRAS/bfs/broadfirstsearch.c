//VINICIUS COUTO ESPINDOLA
//RA: 188115
#include<stdio.h>
#include<stdlib.h>

#include "types.h"
#include "functions.h"

int main( void ){
	
	list data = initList( );
	
	while( data.searchLine ){
		bfs( data , (data.searchLine->adjacent-1) );
		removeFromLine( &data.searchLine );
	}
	
	results( data );
	
	release( data );
	
	return 0;
}
