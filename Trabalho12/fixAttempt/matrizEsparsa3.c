//VINICIUS COUTO ESPINDOLA
//RA: 188115
#include<stdio.h>
#include<stdlib.h>

#include "types3.h"
#include "functions3.h"

int main( void ){
	int row, colunm;
	
	data *elements = adjustEntry( );
	
	csr *matrix = setCSRMatrix( elements );
	elements = freeElements( elements );
	
	while( 1 ){
		scanf(" %i %i", &row , &colunm );
		if( (row<0)||(colunm<0) ){ break; }
		search( row , colunm , matrix );
	}
	
	matrix = freeCSR( matrix );
	
	return 0;
}

