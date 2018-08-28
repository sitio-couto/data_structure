//VINICIUS COUTO ESPINDOLA
//RA: 188115
#include<stdio.h>
#include<stdlib.h>

#include "types.h"
#include "functions.h"

int main( void ){
	char command;
	int key, cost, i;
	
	vectors data;
	initialize_heap( &data );
	
	while( 1 ){
		scanf(" %c", &command );
		if( command == 'i' ){
			scanf(" %i %i", &key, &cost );
			insertPair( &data , key , cost );
		}else if( command == 'm' ){
			removeMinimum( &data );
		}else if( command == 'd' ){
			scanf(" %i %i", &key, &cost );
			decreaseCost( &data , key , cost );
		}else if( command == 't' ){
			free( data.heap );
			free( data.heapKeys );
			break;
		}
	}
	
	return 0;
}




