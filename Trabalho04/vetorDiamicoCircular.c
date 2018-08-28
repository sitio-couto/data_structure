//VINICIUS COUTO ESPINDOLA
//RA: 188115
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/////DATA .H/////

typedef struct dinamicCircularVector{
	double memoryUsed;
	double totalMemory;
	int firstChain;
	int lastChain;
	char **vector;
}dcv;

void debug( dcv *sequence );

typedef char superString[5000];

dcv* init_dcv( );
void create_vector( dcv *sequence );
void update_dcv_size( dcv *sequence );
void erase_vector( dcv *sequence );
void test_empty( superString buffer );

void unshift( dcv *sequence );
void shift( dcv *sequence );
void print_first( dcv *sequence );
void push( dcv *sequence );
void pop( dcv *sequence );
void print_last( dcv *sequence );
void is_empty( dcv *sequence );
dcv* end( dcv *sequence );

/////MAIN .C/////

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
		}else if( !strcmp( command , "debug" ) ){
			debug( sequence );	
		}else if( !strcmp( command , "exit" ) ){
			sequence = end( sequence );
			break;
		}
	}
	
	return 0;
}


/////NEXT .C/////

//Funcoes auxiliares para o fluxo de dados do vetor.
dcv* init_dcv( ){
	dcv *sequence = malloc( sizeof( dcv ) );
	(*sequence).memoryUsed = 0;
	(*sequence).totalMemory = 0;
	(*sequence).firstChain = 0;
	(*sequence).lastChain = 0;
	(*sequence).vector = NULL;
	
	return sequence;
}

void create_vector( dcv *sequence ){
	(*sequence).totalMemory = 2;
	(*sequence).vector = malloc( sizeof(char*)*2 );
	(*sequence).firstChain = 0;
	(*sequence).lastChain = 0;
}

void erase_vector( dcv *sequence ){
	(*sequence).memoryUsed = 0;
	(*sequence).totalMemory = 0;
	free( (*sequence).vector );
	(*sequence).vector = NULL;
}

void update_dcv_size( dcv *sequence ){ 
	int check = 0, j, i = (*sequence).firstChain;
	//abaixo, macros para compactar a escrita.
	double allMem = (*sequence).totalMemory, memInUse = (*sequence).memoryUsed;
	char **copy;
	
	if( ( memInUse == allMem ) && ( allMem != 0 ) ){
		copy = malloc( sizeof(char*)*(allMem)*2 );
		sequence->totalMemory *= 2 ;
 		check = 1;
	}else if( memInUse <= ( allMem/4 ) ){
		copy = malloc( sizeof(char*)*(allMem/2) );
		sequence->totalMemory /= 2 ;
		check = 1;
	}
	
	if( check == 1 ){
		for( j=0 ; j < memInUse ; ++j ){
			if( i == allMem ){ i = 0; };
			copy[j] = sequence->vector[i];
			++i;
		}
		free( sequence->vector );
		(*sequence).firstChain = 0;
		(*sequence).lastChain = (j-1);
		sequence->vector = copy;
	}
}

//Funcoes de INSERCAO de dados.
void unshift( dcv *sequence ){
	int i;
	superString buffer;
	scanf("%[^\n]", buffer );
	test_empty( buffer );
	
	if( (*sequence).totalMemory == 0 ){
		create_vector( sequence );
		(*sequence).vector[0] = malloc( sizeof(char)*(strlen( buffer ) + 1) );
		strcpy( (*sequence).vector[0] , buffer );
		++(*sequence).memoryUsed;
	}else{
		i = (*sequence).firstChain - 1 ;
		if( i < 0 ){ 
			i = (*sequence).totalMemory - 1 ; 
		}
		(*sequence).vector[i] = malloc( sizeof(char)*(strlen( buffer ) + 1) );
		strcpy( (*sequence).vector[i] , buffer );
		(*sequence).firstChain = i;
		++(*sequence).memoryUsed;
	}
	
}

void push( dcv *sequence ){
	int i;
	superString buffer;
	scanf("%[^\n]", buffer );
	test_empty( buffer );
	
	if( (*sequence).totalMemory == 0 ){
		create_vector( sequence );
		(*sequence).vector[0] = malloc( sizeof(char)*(strlen( buffer ) + 1) );
		strcpy( (*sequence).vector[0] , buffer );
		++(*sequence).memoryUsed;
	}else{
		i = (*sequence).lastChain + 1 ;
		if( i == (*sequence).totalMemory ){ 
			i = 0; 
		}
		(*sequence).vector[i] = malloc( sizeof(char)*(strlen( buffer ) + 1) );
		strcpy( (*sequence).vector[i] , buffer );
		(*sequence).lastChain = i;
		++(*sequence).memoryUsed;
	}
	
}

//Funcoes de REMOCAO de dados.
void shift( dcv *sequence ){
	int aux;
	
	if( sequence->vector != NULL ){
		aux = sequence->firstChain + 1 ;
		if( aux == sequence->totalMemory ){ 
			aux = 0 ; 
		}
		free( sequence->vector[sequence->firstChain] );
		sequence->firstChain = aux;
		--sequence->memoryUsed;
		
		if( (sequence->memoryUsed == 0) && (sequence->totalMemory != 0) ){
			erase_vector( sequence );
		}
	}
	
	
}

void pop( dcv *sequence ){
	int aux;
	
	if( sequence->vector != NULL ){
		aux = sequence->lastChain - 1 ;
		if( aux < 0 ){ 
			aux = sequence->totalMemory - 1 ; 
		}
		free( sequence->vector[sequence->lastChain] );
		sequence->lastChain = aux;
		--sequence->memoryUsed;
		
		if( (sequence->memoryUsed == 0) && (sequence->totalMemory != 0) ){
			erase_vector( sequence );
		}
	}
	
}

//Feedback simples sobre as cadeias e os elementos.
void print_first( dcv *sequence ){
	if( sequence->memoryUsed != 0 ){
		printf("%s\n", sequence->vector[sequence->firstChain] );	
	}
}

void print_last( dcv *sequence ){
	if( sequence->memoryUsed != 0 ){
		printf("%s\n", sequence->vector[sequence->lastChain] );	
	}
}

void is_empty( dcv *sequence ){
	if( sequence->memoryUsed == 0 ){
		printf("yep\n");
	}else{
		printf("nope\n");
	}
}

//Confere a entrada por espacos reorganizando-a.
void test_empty( superString buffer ){
	int i, j, k = 0, length = strlen( buffer );
	char *aux;
	
	for( i=0 ; i<length ; ++i ){
		if( buffer[i] != ' ' ){
			for( j=(length-1) ; j>=0 ; --j ){
				if( buffer[j] != ' ' ){
					for( i=i ; i<=j ; ++i ){
						buffer[k] = buffer[i];
						++k;
					}
					buffer[k] = '\0';
					break;
				}
			}
			break;
		}else if( i == (length-1) ){
			strcpy( buffer , "" );
			break;	
		} 
	}
	
}

//Finaliza o programa e libera a memoria.
dcv* end( dcv *sequence ){
	int i, start = sequence->firstChain, finish = sequence->lastChain;
	
	if( sequence->vector != NULL ){
		
		for( i=start ; i!=finish ; ++i ){
			if( i == sequence->totalMemory ){ i = 0; }
			free( sequence->vector[i] );
		}
		free( sequence->vector[i] );
		free( sequence->vector );
	}
	free( sequence );
	
	return NULL;
}

//DEBUG!!!
void debug( dcv *sequence ){
	int i;
	
	printf("\n------------------------\n");
	printf("M. total -> %.0lf(char*)\n", sequence->totalMemory);
	printf("M. used -> %.0lf(char*)\n", sequence->memoryUsed);
	if( sequence->vector != NULL ){
		printf("first(%i:%s) & last(%i:%s)", sequence->firstChain, sequence->vector[sequence->firstChain], sequence->lastChain, sequence->vector[sequence->lastChain]);
		printf("\n------------------------\n");
		for( i=(sequence->firstChain) ; i!=sequence->lastChain ; ++i ){
			if( i == sequence->totalMemory ){ i = 0 ; }
			printf("%i->%s<-\n", i, sequence->vector[i]);
		}
		printf("%i->%s<-\n", i, sequence->vector[sequence->lastChain]);
	}else{
		printf("the DCV is NULL!\n");
	}
	printf("------------------------\n");
}

