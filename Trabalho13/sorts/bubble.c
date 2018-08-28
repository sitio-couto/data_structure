#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define BI 10E9

int *vet, *aux;
int size;
void bubbleSort( void );
struct timespec set, lap;

int main( void ){
	int i, j;
	long long time;
	
	scanf(" %i", &size );
	vet = malloc( sizeof( int )*size );
	aux = malloc( sizeof( int )*size );
	for( i=0 ; i<size ; ++i ){
		scanf(" %i", &vet[i] );
	}
	
	for( j=0 ; j<1 ; ++j ){
		clock_gettime( CLOCK_PROCESS_CPUTIME_ID , &set );
		bubbleSort( );
		clock_gettime( CLOCK_PROCESS_CPUTIME_ID , &lap );
		time += (lap.tv_sec - set.tv_sec)*BI + (lap.tv_nsec - set.tv_nsec); 
		for( i=0 ; i<size-1 ; ++i ){
			if( vet[i] > vet[i+1] ) return;
			vet[i] = aux[i];
		}
		vet[size-1] = aux[size-1];
	}
	
	printf("bubble -> %.9lf", (double)time/BI );
	
	return 0;
}


void bubbleSort( void ){
	int i, temp, check;
	
	do{
		check = 0;
		for( i=0 ; i<(size - 1) ; ++i ){							
			if( vet[i] > vet[i+1] ){							
				check = 1;
				temp = vet[i+1];
				vet[i+1] = vet[i];
				vet[i] = temp;
			}
		}
	}while(check);
	
	return;
}
