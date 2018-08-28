#include<stdio.h>
#include<stdlib.h>

typedef struct node{
	int row;
	int colunm;
	int value;
}node;

typedef struct CSR{
	int *values;
	int *colunms;
	int *rowStart;
	int maxRow;
}CSR;

node **createEntry( int *k );
void insertionSort( node **data , int *size );
CSR *buildCSR( int *k , node **coordinates );
void search( int i , int j , CSR *matrix , int k );

int main( void ){
	
	int i, j, k;
	node **coordinates = createEntry( &k );
	CSR *matrix = buildCSR( &k , coordinates );
	coordinates = NULL;
	
	while( 1 ){
		scanf(" %i %i", &i , &j );
		if( (i == -1)||(j == -1) ){ break; }
		search( i , j , matrix , k );
	}
	
	free( matrix->rowStart );
	free( matrix->colunms );
	free( matrix->values );
	free( matrix );
	matrix = NULL;
}

node **createEntry( int *k ){
	int i, qntLines = 0;
	
	scanf(" %i", k );
	node **data = malloc( sizeof( node* )*(*k) );

	for( i=0 ; i<(*k) ; ++i ){
		data[i] = malloc( sizeof( node ) );
		scanf(" %i %i %i", &data[i]->row, &data[i]->colunm, &data[i]->value );
		if( data[i]->row > qntLines ){ qntLines = data[i]->row; }
	}
	
	insertionSort( data ,  k );
	
	return data;
}

void insertionSort( node **data , int *size ){
	int leftLimit = 0 , rightLimit = (*size) - 1 ;
	int i, j, k;
	node *insertion; 
	
	for( i=(leftLimit+1) ; i<=rightLimit ; ++i ){
		for( j=leftLimit ; j<i ; ++j ){
			if( data[i]->row < data[j]->row ){
				insertion = data[i]; 
				for( k=(i-1) ; k>=j ; --k ){
					data[k+1] = data[k];
				}
				data[j] = insertion;
				break;
			}
		}
	}
	
	rightLimit = -1;
	
	do{
		leftLimit = ++rightLimit;
		rightLimit = (*size) - 1 ;
		
		for( i=(leftLimit+1) ; i<(*size) ; ++i ){
			if( data[i]->row != data[leftLimit]->row){
				rightLimit = (i-1);
				break;
			}
		}
		
		for( i=(leftLimit+1) ; i<=rightLimit ; ++i ){
			for( j=leftLimit ; j<i ; ++j ){
				if( data[i]->colunm < data[j]->colunm ){
					insertion = data[i]; 
					for( k=(i-1) ; k>=j ; --k ){
						data[k+1] = data[k];
					}
					data[j] = insertion;
					break;
				}
			}
		}	
	}while( rightLimit < ((*size) - 1) );
	/*
	for(i=0;i<(*size);++i){
		printf("(%i;%i)>%i ", data[i]->row , data[i]->colunm , data[i]->value );
	}
	printf("\n");
	*/
	return;
}

CSR *buildCSR( int *k , node **coordinates ){
	int i, aux;
	
	CSR *matrix = malloc( sizeof( CSR )*(*k) );
	matrix->values = malloc( sizeof( int )*(*k) ); 
	matrix->colunms = malloc( sizeof( int )*(*k) );
	matrix->maxRow = 0;
	
	for( i=0 ; i<(*k) ; ++i ){
		matrix->values[i] = coordinates[i]->value;
		matrix->colunms[i] = coordinates[i]->colunm;
		if( coordinates[i]->row > matrix->maxRow ){
			matrix->maxRow = coordinates[i]->row;
		}
	}
	
	matrix->rowStart = malloc( sizeof( int )*(matrix->maxRow + 1) );
	for( i=0 ; i<(matrix->maxRow+2) ; ++i ){
		matrix->rowStart[i] = -1;
	}
	
	aux = -1;
	for( i=0 ; i<(*k) ; ++i ){
		if( coordinates[i]->row != aux ){
			aux = coordinates[i]->row; 
			matrix->rowStart[aux] = i;
		}
	}
	
	for( i=1 ; i<(*k) ; ++i ){
		free( coordinates[i] );
	}
	free( coordinates );
	/*
	for(i=0;i<(*k);++i){
		printf("(X;%i)>%i ", matrix->colunms[i] , matrix->values[i] );
	}
	printf("\n");
	
	for(i=0;i<(matrix->maxRow+1);++i){
		printf("%i|", matrix->rowStart[i] );
	}
	*/
	return matrix;
}

void search( int i , int j , CSR *matrix , int k ){
	int current, end;
	
	if( i <= matrix->maxRow ){
		current = matrix->rowStart[i]; end = i+1;
	}
	
	if( (i <= matrix->maxRow) && (current > -1) ){
		while( 1 ){
			if( end > (matrix->maxRow + 1) ){
				end = k;
				break;
			}else if( matrix->rowStart[end] > -1 ){
				end = matrix->rowStart[end]; 
				break; 
			}
			++end;
		}
		
		while( current != end ){
			if( matrix->colunms[current] == j ){ 
				printf("(%i,%i) = %i\n", i, j, matrix->values[current] );
				return;
			}
			++current;
		}
	}

	printf("(%i,%i) = 0\n", i, j );
	
	return;
}




