#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define BI 10E9

int *vet, *aux;
int size;
void quickSort( void );
struct timespec set, lap;


typedef struct limits{
	long int start;
	long int end;
	struct limits *next;
}limits;

int main( void ){
	int i, j;
	long long time;
	
	scanf(" %i", &size );
	vet = malloc( sizeof( int )*size );
	aux = malloc( sizeof( int )*size );
	for( i=0 ; i<size ; ++i ){
		scanf(" %i", &vet[i] );
		aux[i] = vet[i];
	}
	
	for( j=0 ; j<5 ; ++j ){
		clock_gettime( CLOCK_REALTIME , &set );
		quickSort( );
		clock_gettime( CLOCK_REALTIME , &lap );
		time += (lap.tv_sec - set.tv_sec)*BI + (lap.tv_nsec - set.tv_nsec); 
		for( i=0 ; i<size-1 ; ++i ){
			if( vet[i] > vet[i+1] ) return;
			vet[i] = aux[i];
		}
		vet[size-1] = aux[size-1];
	}
	printf("quick-> %.9lf\n", (double)time/(BI*5) );
	
	return 0;
}

void quickSort( void ){
	int i, j, start, end, temp, pivot = 0;								
	limits *aux, *list = malloc( sizeof( limits ) );
	list->start = 0;
	list->end = (size - 1);
	list->next = NULL;					
										
	while( list != NULL ){
		start = list->start;
		end = list->end;
		aux = list;
		list = list->next;
		free( aux );
		
		pivot = start;
		for( i=(pivot+1) ; i<=end ; ++i ){							
			if( vet[pivot] > vet[i] ){
				temp = vet[i];
				for( j=(i-1) ; j >= pivot ; --j ){
					vet[j+1] = vet[j];
				}
				vet[pivot] = temp;
				++pivot;															
			}
		}
		
		if( start < (pivot-1) ){
			aux = malloc( sizeof( limits ) );
			aux->start = start;
			aux->end = (pivot - 1);
			aux->next = list;
			list = aux;
		}
		if( (pivot + 1) < end ){
			aux = malloc( sizeof( limits ) );
			aux->start = (pivot + 1);
			aux->end = end;
			aux->next = list;
			list = aux;
		}
	}
	
	return;
}

