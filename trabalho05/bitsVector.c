//VINICIUS COUTO ESPINDOLA
//RA: 188115
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef char string[15];
typedef unsigned char uc;
typedef unsigned char *ucp;

typedef struct vectorStruct {
	int elements;
	ucp bitsVector;
} vectorStruct;

void createBitVector( vectorStruct *vectorData );
void addElement( vectorStruct *vectorData );
void removeElement( vectorStruct *vectorData );
void testIn( vectorStruct *vectorData );
void selecting( vectorStruct *vectorData );
void ranking( vectorStruct *vectorData );
void print( vectorStruct *vectorData );
void rangeCounting( vectorStruct *vectorData );
vectorStruct *end( vectorStruct *vectorData );

int main( void ) {
	vectorStruct *vectorData = malloc( sizeof( vectorStruct ) );
	vectorData->elements = 0; vectorData->bitsVector = NULL;
	int check = 1;
	string command;

	while( check ) {
		scanf(" %s", command );
		if( !strcmp( command , "create" ) ){
			createBitVector( vectorData );
		}else if( !strcmp( command , "add" ) ){
			addElement( vectorData );
		}else if( !strcmp( command , "remove" ) ){
			removeElement( vectorData );
		}else if( !strcmp( command , "in" ) ){
			testIn( vectorData );
		}else if( !strcmp( command , "rank" ) ){
			ranking( vectorData );
		}else if( !strcmp( command , "select" ) ) {
			selecting( vectorData );
		}else if( !strcmp( command , "rangecount" ) ) {
			rangeCounting( vectorData );
		}else if( !strcmp( command , "print" ) ) {
			print( vectorData );
		}else if( !strcmp( command , "exit" ) ) {
			vectorData = end( vectorData );
			check = 0;
		}
	}

return 0;
}

void createBitVector( vectorStruct *vectorData ) {
	scanf(" %i", &vectorData->elements );
	if( vectorData->bitsVector != NULL ){
		free( vectorData->bitsVector );
	}

	if( !(vectorData->elements%8) && (vectorData->elements != 0 ) ) {
		vectorData->bitsVector = calloc( sizeof( char ),(vectorData->elements/8) );
	}else  if( vectorData->elements != 0 ){
		vectorData->bitsVector = calloc( sizeof( char ),(vectorData->elements/8 + 1 ) );
	}else{
		vectorData->bitsVector = NULL;
	}

}

void addElement( vectorStruct *vectorData ) {
	int position;
	scanf(" %i", &position );
	vectorData->bitsVector[(position-1)/8] |= 0x1 << ((position-1)%8);
}

void removeElement( vectorStruct *vectorData ){// IF NO ELEMENT IN POS??
	int position;
	scanf(" %i", &position );
	vectorData->bitsVector[(position-1)/8] ^= 0x1 << ((position-1)%8);
}

void testIn( vectorStruct *vectorData ){
	int position;
	scanf(" %i", &position );
	uc mask = 0x1<<((position-1)%8);
	if( vectorData->bitsVector == NULL ){
		printf("belongs(%i) = false\n", position );
		return;
	}
	
	if( ((vectorData->bitsVector[(position-1)/8]) & mask) != 0 ){
		printf("belongs(%i) = true\n", position );
	}else{
		printf("belongs(%i) = false\n", position );
	}
	
}

void ranking( vectorStruct *vectorData ){
	int value, byte, bit, rank = 0;
	scanf(" %i", &value );
	uc mask;
	
	if( value <= vectorData->elements ){
		int byteLimit = (value-1) / 8 ;
		int bitsLimit = ((value-1)%8);
		for( byte=0 ; byte<=byteLimit ; ++byte ){
			for( bit=0 ; bit<8 ; ++bit ){
				mask = 0x1;
				if( ( (vectorData->bitsVector[byte]) & (mask<<bit) ) != 0 ){
					++rank;
				}
				if( (byte == byteLimit) && ( bit == bitsLimit ) ){
					printf("rank(%i) = %i\n", value, rank );
					return;
				}	
			}
		}
	}
	
	printf("rank(%i) = 0\n", value );
}

void selecting( vectorStruct *vectorData ){
	int position, byte, bit, value, aux;
	scanf(" %i", &position );
	value = position;
	uc mask;
	if( vectorData->bitsVector == NULL ){ printf("select(%i) = 0\n", value ); return; }
	
	int byteLimit = (vectorData->elements-1) / 8 ;
	int bitsLimit = ((vectorData->elements-1)%8);
	for( byte=0 ; byte<=byteLimit ; ++byte ){
		for( bit=0 ; bit<8 ; ++bit ){
			mask = 0x1;
			if( ( (vectorData->bitsVector[byte]) & (mask<<bit) ) != 0 ){
				--position;
			}
			if( (position <= 0) || ((byte==byteLimit) && ( bit==bitsLimit )) ){
				if( position != 0 ){ 
					printf("select(%i) = 0\n", value ); 
					return;	
				}
				aux = ( (byte*8) + (bit+1) );
				printf("select(%i) = %i\n", value, aux );
				return;
			}	
		}
	}
	
}

void rangeCounting( vectorStruct *vectorData ){
	int bit, byte, firstBit, lastBit, inGap = 0, check = 1;
	scanf(" %i %i", &firstBit, &lastBit );
	int byteLimit = (vectorData->elements-1)/8 ;
	int bitsLimit = ((vectorData->elements-1)%8);
	uc mask;
	
	for( byte=(firstBit-1)/8 ; byte<=byteLimit ; ++byte ){
		for( bit=0 ; bit<8 ; ++bit ){
			if( check ){ bit = (firstBit-1)%8 ; --check; }
			mask = 0x1;
			if( ( (vectorData->bitsVector[byte]) & (mask<<bit) ) != 0 ){
				++inGap;
			}
			if( (bit == (lastBit-1)%8 ) && (byte == (lastBit-1)/8) ){
				printf("rangecount(%i,%i) = %i\n",firstBit,lastBit,inGap);
			}
		}
	}
	
}

void print( vectorStruct *vectorData ){
	int byte, bit, check = 0;
	int byteLimit = (vectorData->elements-1) / 8 ;
	int bitsLimit = ((vectorData->elements-1)%8);
	uc mask;

	printf("S = {");
	if( vectorData->elements != 0 ){
		for( byte=0 ; byte<=byteLimit ; ++byte ){
			for( bit=0 ; bit<8 ; ++bit ){
				mask = 0x1;
				if( ( (vectorData->bitsVector[byte]) & (mask<<bit) ) != 0 ){
					if(check){ printf(","); }
					printf("%i", ( (byte*8)+(bit+1) ) );
					check = 1 ;
				}
			}
		}
	}
	printf("}\n");
	
}

vectorStruct *end( vectorStruct *vectorData ){
	if( vectorData->bitsVector != NULL ){
		free( vectorData->bitsVector );
	}
	free( vectorData );
	
	return NULL;
}

