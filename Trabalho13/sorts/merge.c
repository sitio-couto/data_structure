#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define BI 10E9

int size;
void mergeSort( int *vet , int start , int end );
struct timespec set, lap;

int main( void ){
	int i, j;
	long long time;
	int *vet, *aux;
	
	scanf(" %i", &size );
	vet = malloc( sizeof( int )*size );
	aux = malloc( sizeof( int )*size );
	for( i=0 ; i<size ; ++i ){
		scanf(" %i", &vet[i] );
		aux[i] = vet[i];
	}
	
	for( j=0 ; j<5 ; ++j ){
		clock_gettime( CLOCK_PROCESS_CPUTIME_ID , &set );
		mergeSort( vet , 0 , (size-1) );
		clock_gettime( CLOCK_PROCESS_CPUTIME_ID , &lap );
		time += (lap.tv_sec - set.tv_sec)*BI + (lap.tv_nsec - set.tv_nsec); 
		for( i=0 ; i<size-1 ; ++i ){
			if( vet[i] > vet[i+1] ) printf("\nERROR\n");
			vet[i] = aux[i];
		}
		vet[size-1] = aux[size-1];
	}
	printf("merge-> %.9lf\n", (double)time/(BI*5) );	
	
	return 0;
}

void mergeSort( int *vet , int start , int end ){
	int i, reff, j = 0, *temp, half = (start+end)/2, k = (half+1);
	i = reff = start;
	
	if( start >= end ) return;
	mergeSort( vet , start , half );												
	mergeSort( vet , (half+1) , end );
	
	temp = calloc( sizeof( int ) , (end-start+1) );
	for( j=0 ; j<(end-start+1) ; ++j ){
		for( i=reff ; i<=half ; ++i ){
			if(  )
			temp[j] = vet[i]; 
			++i;
		}
		reff = i;
		else if{
			
		} 
	}
	
	for( i=start ; i<=end ; ++i ){
		vet[i] = temp[i];
		printf("%i|", vet[i] );
	}printf("\n");
	free( temp );
	
	return;	
}


