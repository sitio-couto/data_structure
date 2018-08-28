#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int const size = 1000;
int count = 0;

void createVet( int vet[] ){
	int i;
	
	for( i=0 ; i<size ; ++i ){
		vet[i] = i;
	}
	
	return;
}

int searchBin( int vet[] , int k , double base , double limit ){
	int reference = ( (limit-base) / 2 ) + base ;
	printf("\n->%i<-\n", reference );
	
	++count;
	if( k == vet[reference] ){
		return;
	}else if( k < vet[reference] ){
		limit = reference;
		searchBin( vet , k , base , limit );
	}else if( k > vet[reference] ){
		base = reference;
		searchBin( vet , k , base , limit );
	}
	
}

int main( void ){
	int vet[size], k;
	
	createVet( vet );
	
	while( 1 ){
		scanf(" %i", &k );
		double limit = size , base = 0;
			
		searchBin( vet , k , base , limit );
		
		printf("\n|||%i|||\n\n", count );
		count = 0;
	}
	
	return 0;
}


