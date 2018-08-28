#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define BI 10E9

int *vet, *aux;
int size;
void heapSort( void );
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
		heapSort( );
		clock_gettime( CLOCK_PROCESS_CPUTIME_ID , &lap );
		time += (lap.tv_sec - set.tv_sec)*BI + (lap.tv_nsec - set.tv_nsec); 
		for( i=0 ; i<size-1 ; ++i ){
			if( vet[i] > vet[i+1] ) return;
			vet[i] = aux[i];
		}
		vet[size-1] = aux[size-1];
	}
	
	printf("heap -> %.9lf", (double)time/BI );
	
	return 0;
}

void heapSort( void ){
	int i, j, temp, aux = 1;
	
	for( i=1 ; i<size ; ++i ){
		for( j=i ; j>0 ; j=(j-1)/2 ){														
			if( vet[j] > vet[(j-1)/2] ){	
				temp = vet[j];
				vet[j] = vet[(j-1)/2];
				vet[(j-1)/2] = temp;
			}
		}
	}
	for( i=(size-1) ; i>0 ; --i ){
		temp = vet[0];
		vet[0] = vet[i];
		vet[i] = temp;
		for( j=0 ; (j*2+1)<i ; j=aux ){					
			aux = 2*j + 1;
			if( ((2*j + 2) < i) && (vet[aux] < vet[2*j+2]) )
				aux = 2*j + 2; 
			if( vet[j] >= vet[aux] ) break;								
			temp = vet[j];
			vet[j] = vet[aux];
			vet[aux] = temp;
		}
	}
	
	return;
}

