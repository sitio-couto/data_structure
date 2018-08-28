#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define BI 1000000000

int *vet;
int size;
void radixSort( void );
struct timespec set, lap;

int main( void ){
	int i;
	
	scanf(" %i", &size );
	vet = malloc( sizeof( int )*size );
	for( i=0 ; i<size ; ++i ){
		scanf(" %i", &vet[i] );
		if( vet[i] < 0 ){
			printf("\n-----\nERROR: radix denies negative values\n-----\n"); 
			return;
		}
	}
	
	clock_gettime( CLOCK_PROCESS_CPUTIME_ID , &set );
	radixSort( );
	clock_gettime( CLOCK_PROCESS_CPUTIME_ID , &lap );
	long long int time = (lap.tv_sec - set.tv_sec)*BI + (lap.tv_nsec - set.tv_nsec);
	
	for( i=0 ; i<(size-1) ; ++i ){
		if( vet[i] > vet[i+1] ){
			printf("\n\nFUKKKKKKFUFUFUFFKFKFUFUUF\n\n");	
		}
	}
	
	printf("\n\nTIME---> %.9lf ", (double)time/BI );
	
	return 0;
}


void radixSort( void ){
	int j, i, biggest = -1, bucket[10];
	int *temp, *newVet = malloc( sizeof( int )*size );
	int pos( int i , int j ){
		return (vet[i]%(j*10) - vet[i]%j)/j ;
	}
	
	for( i=0 ; i<size ; ++i ){
		if( vet[i] > biggest ){ biggest = vet[i]; }
	}
	
	for( j=1 ; j<=biggest ; j*=10 ){												
		for( i=0 ; i<10 ; ++i ){ bucket[i] = 0; }
		
		for( i=0 ; i<size ; ++i ){												
			++bucket[pos( i , j )];														
		}
		
		for( i=1 ; i<10 ; ++i ){														
			bucket[i] += bucket[i-1];
		}
		
		for( i=(size-1) ; i>=0 ; --i ){																								
			newVet[ --bucket[pos( i , j )] ] = vet[i];
		}
		
		temp = vet;
		vet = newVet;
		newVet = temp;
	}
	free( newVet );
	
	return;
}
