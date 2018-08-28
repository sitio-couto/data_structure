#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define BI 10E9

int *vet, *aux;
int size;
void selectionSort( void );
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
		selectionSort( );
		clock_gettime( CLOCK_PROCESS_CPUTIME_ID , &lap );
		time += (lap.tv_sec - set.tv_sec)*BI + (lap.tv_nsec - set.tv_nsec); 
		for( i=0 ; i<size-1 ; ++i ){
			if( vet[i] > vet[i+1] ) return;
			vet[i] = aux[i];
		}
		vet[size-1] = aux[size-1];
	}
	
	printf("selection -> %.9lf", (double)time/BI );
	
	return 0;
}

void selectionSort( void ){
	int i, min, temp, place = 0;
	
	for( place=0 ; place<(size-1) ; ++place ){
		min = place;
		for( i=(place+1) ; i<size ; ++i ){
			if( vet[i] < vet[min] ){ min = i; }	
		}	
		temp = vet[place];
		vet[place] = vet[min];
		vet[min] = temp;
	}
	
	return;
}
