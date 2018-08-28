//VINICIUS COUTO ESPINDOLA
//RA: 188115
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "data.h"

int main( void ){
	dcv *sequence = init_dcv( ) ;
	char command[15];
	
	while( 1 ){
		scanf(" %s", command );
		if( !strcmp( command , "unshift" ) ){
			unshift( sequence );
			update_dcv_size( sequence );
		}else if( !strcmp(command , "shift") ){
			shift( sequence );
			if( sequence->vector != NULL ){
				update_dcv_size( sequence );	
			}
		}else if( !strcmp( command , "print-first" ) ){
			print_first( sequence );
		}else if( !strcmp( command , "push" ) ){
			push( sequence );
			update_dcv_size( sequence );
		}else if( !strcmp( command , "pop" ) ){
			pop( sequence );
			if( sequence->vector != NULL ){
				update_dcv_size( sequence );	
			}
		}else if( !strcmp( command , "print-last" ) ){
			print_last( sequence );
		}else if( !strcmp( command , "is-empty" ) ){
			is_empty( sequence );	
		}else if( !strcmp( command , "exit" ) ){
			sequence = end( sequence );
			break;
		}
	}
	
	return 0;
}



