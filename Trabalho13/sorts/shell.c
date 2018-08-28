#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define BI 10E9

int *vet, *aux;
int size;
void shellSort( void );
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
		shellSort( );
		clock_gettime( CLOCK_PROCESS_CPUTIME_ID , &lap );
		time += (lap.tv_sec - set.tv_sec)*BI + (lap.tv_nsec - set.tv_nsec); 
		for( i=0 ; i<size-1 ; ++i ){
			if( vet[i] > vet[i+1] ) return;
			vet[i] = aux[i];
		}
		vet[size-1] = aux[size-1];
	}

	printf("\n\n-->time = %.9lf \n", (double)time/BI );
	
	return;
}

void shellSort( void ){
	int temp, i, j, aux, gap;
	
	for( gap=(size/2) ; gap>=1 ; gap=(gap/2) ){
		for( i=gap ; i<size ; ++i ){ 												
			if( vet[i] < vet[i-gap] ){		
				aux = i;
				do{
					temp = vet[aux];
					vet[aux] = vet[aux-gap];
					vet[aux-gap] = temp;
					aux = aux - gap;
					if( (aux - gap) < 0 ) break;
				}while( vet[aux] < vet[aux-gap] );
			}
		}
	}
	
	return;
}
