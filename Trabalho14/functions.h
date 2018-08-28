#ifndef _FUNCTIONS
#define _FUNCTIONS

list initList( void ){
	int i, pos;
	node *newNode;
	list data;
	
	scanf(" %i", &data.vertices );
	data.array = calloc( data.vertices , sizeof( vector ) );
	data.marks = calloc( data.vertices , sizeof( int ) );
	while( 1 ){
		newNode = calloc( 1 , sizeof( node ) );
		scanf(" %i, %i", &pos , &newNode->adjacent );
		if( pos == 0 ) break;
		newNode->prox = data.array[pos-1].prox;
		data.array[pos-1].prox = newNode; 
	}
	free( newNode );
	
	for( i=0 ; i<data.vertices ; ++i ) data.array[i].value = (i+1);
	
	return data;
}

void dfs( list data , int *timestamp , int origin ){
	node *temp = data.array[origin].prox;
	data.marks[origin] = 1;
	
	data.array[origin].timeIn = ++(*timestamp);
	while( temp ){
		if( !data.marks[temp->adjacent-1] ){
			dfs( data , timestamp , (temp->adjacent-1) );
		}
		temp = temp->prox;
	}
	data.array[origin].timeOut = ++(*timestamp);
	
	return;
}

void sortTimestamps( list data ){
	int i, j, aux, gap;
	vector temp;
	
	for( gap=(data.vertices/2); gap>=1 ; gap=(gap/2) ){
		for( i=gap ; i<data.vertices ; ++i ){ 												
			if( data.array[i].timeIn < data.array[i-gap].timeIn ){		
				aux = i;
				do{
					temp = data.array[aux];
					data.array[aux] = data.array[aux-gap];
					data.array[aux-gap] = temp;
					aux = aux - gap;
					if( (aux - gap) < 0 ) break;
				}while( data.array[aux].timeIn < data.array[aux-gap].timeIn );
			}
		}
	}
	
	for( i=0 ; i<data.vertices ; ++i ){
		printf("%i ", data.array[i].value );
		printf("[%i,%i]\n", data.array[i].timeIn, data.array[i].timeOut );
	}
	
	return;
}

void seekCycle( list data ){
	int i;
	node *temp;
	
	printf("aciclico: ");
	for( i=0 ; i<data.vertices ; ++i ){
		temp = data.array[i].prox;
		while( temp ){
			if( data.array[temp->adjacent-1].timeIn < data.array[i].timeIn ){
			if( data.array[temp->adjacent-1].timeOut > data.array[i].timeOut ){
				printf("nao\n"); return;
			}}
			temp = temp->prox;
		}
	}
	printf("sim\n");
	
	return;
}

void release( list data ){
	int i;
	node *temp, *aux;
	
	for( i=0 ; i<data.vertices ; ++i ){
		temp = data.array[i].prox;
		while( temp ){
			aux = temp->prox;
			free( temp );
			temp = aux;
		}
	}
	free( data.array );
	free( data.marks );
	
	return;
}

#endif
