//VINICIUS COUTO ESPINDOLA
//RA: 188115
#include<stdio.h>
#include<stdlib.h>

#include<types.h>
#include<functions.h>

int main( void ){
	int i, timestamp = 0;
	
	list data = initList( );
	
	for( i=0 ; i<data.vertices ; ++i ){
		if( !data.marks[i] ) dfs( data , &timestamp , i );
	}
	
	sortTimestamps( data );
	
	seekCycle( data );
	
	release( data );
	
	return 0;
}

















