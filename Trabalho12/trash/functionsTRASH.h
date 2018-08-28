#ifndef _FUNCTIONS
#define _FUNCTIONS

data *initializeData( void ){
	int i;
	data *elements = malloc( sizeof( data ) );
	
	scanf(" %i", &elements->amount );
	
	elements->entry = malloc( sizeof( node* )*elements->amount );
	elements->maxRow = -1;
	for( i=0 ; i<elements->amount ; ++i ){
		elements->entry[i] = malloc( sizeof( node ) );
		scanf(" %i", &elements->entry[i]->row );
		scanf(" %i", &elements->entry[i]->colunm );
		scanf(" %i", &elements->entry[i]->value );
		if( elements->entry[i]->row > elements->maxRow ){
			elements->maxRow = elements->entry[i]->row;
		}
	}
	
	return elements;
}

data *adjustEntry( void ){
	int i, start = 0, end;
	
	data *elements = initializeData( );
	
	mergeSort( elements->entry , 0 , ((elements->amount-1)/2) , (elements->amount - 1) , 'R' );
	
	for( i=1 ; i<elements->amount ; ++i ){
		if( elements->entry[i]->row != elements->entry[start]->row ){
			mergeSort( elements->entry , start , ((i-start)/2)+start , (i-1) , 'C' );
			start = i;
		}
	}
	mergeSort( elements->entry , start , ((i-start)/2)+start , (elements->amount - 1) , 'C' );
	
	return elements;
}

int compare( char test , int rs , int i , node **entry ){
	if( test == 'R' ){ return (entry[rs]->row < entry[i]->row); }
	if( test == 'C' ){ return (entry[rs]->colunm < entry[i]->colunm); }
}

void mergeSort( node **entry , int start , int endLeft , int endRight , char test ){
	int i, j, rightStart = (endLeft+1);
	node *temp;
	
	if( start < endLeft ){
		mergeSort( entry , start , ((endLeft-start)/2)+start , endLeft , test );
	}
	if( rightStart < endRight ){
		mergeSort( entry , rightStart , ((endRight-endLeft)/2)+endLeft , endRight , test );
	}
	
	while( rightStart <= endRight ){
		for( i=start ; i<=endLeft ; ++i ){
			if( compare( test , rightStart , i , entry ) ){
				temp = entry[rightStart];
				for( j=endLeft ; j>=i ; --j ){
					entry[j+1] = entry[j];
				}
				entry[i] = temp;
				start = (i+1);
				endLeft = rightStart;
				break;
			}
		}
		++rightStart;
	}
	
	return;	
}

csr *setCSRMatrix( data *elements ){
	int i, j, newRow = -1;
	
	csr *matrix = malloc( sizeof( csr ) );
	matrix->values = malloc( sizeof( int )*elements->amount );
	matrix->colunms = malloc( sizeof( int )*elements->amount );
	matrix->rows = calloc( sizeof( int ) , elements->maxRow + 2 );
	matrix->amount = elements->amount;
	matrix->maxRow = elements->maxRow;
	
	for( i=0 ; i<elements->amount ; ++i ){
		matrix->values[i] = elements->entry[i]->value;
		matrix->colunms[i] = elements->entry[i]->colunm;
	}
	
	for( i=0 ; i<elements->amount ; ++i ){
		if( elements->entry[i]->row != newRow ){
			for( j=(newRow+1) ; j<=(elements->entry[i]->row) ; ++j ){
				matrix->rows[j+1] += matrix->rows[j];
			}
			newRow = elements->entry[i]->row;
		}
		++matrix->rows[newRow+1];
	}
	
	return matrix;
}

data *freeElements( data *elements ){
	int i;
	
	for( i=0 ; i<elements->amount ; ++i ){
		free( elements->entry[i] );
	}
	free( elements->entry );
	free( elements );
	
	return NULL;
}

void search( int row , int colunm , csr *matrix ){
	int i, startSearch;

	if( row <= matrix->maxRow ){
		for( i=matrix->rows[row] ; i<matrix->rows[row+1] ; ++i ){
			if( matrix->colunms[i] == colunm ){
				printf("(%i,%i) = %i\n", row , colunm , matrix->values[i] );
				return;
			}
		}
	}
	
	printf("(%i,%i) = 0\n", row , colunm );
	
	return;
}

csr *freeCSR( csr *matrix ){
	free( matrix->rows );
	free( matrix->colunms );
	free( matrix->values );
	free( matrix );
	
	return NULL;
}

#endif

