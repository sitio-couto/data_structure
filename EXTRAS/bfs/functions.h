#ifndef _FUNCTIONS
#define _FUNCTIONS

list initList( void ){
	int i;
	node *newNode, *newNode2;
	list data;
	
	scanf(" %i", &data.vertices );
	data.array = calloc( data.vertices , sizeof( vector ) );
	for( i=0 ; i<data.vertices ; ++i ) data.array[i].range = -1;
	
	while( 1 ){
		newNode = calloc( 1 , sizeof( node ) );
		newNode2 = calloc( 1 , sizeof( node ) );
		scanf(" %i, %i", &newNode2->adjacent, &newNode->adjacent );
		if( newNode2->adjacent == 0 ) break;
		newNode->prox = data.array[newNode2->adjacent-1].prox;
		data.array[newNode2->adjacent-1].prox = newNode; 
		newNode2->prox = data.array[newNode->adjacent-1].prox;
		data.array[newNode->adjacent-1].prox = newNode2; 
	}
	free( newNode2 );
	
	scanf(" %i", &data.origin );
	data.array[data.origin-1].range = 0;
	data.searchLine = newNode;
	newNode->adjacent = data.origin;
	
	return data;
}

void insertInLine( node *temp , int value ){
	node *newNode = calloc( 1 , sizeof( node ) );
	newNode->adjacent = value;
	
	while( temp->prox ) temp = temp->prox;
	temp->prox = newNode;
	
	return;
}

void removeFromLine( node **temp ){
	node *aux = (*temp);
	(*temp) = aux->prox;
	free( aux );
	
	return;
}

void bfs( list data , int origin ){
	node *temp = data.array[origin].prox;
	int range = data.array[origin].range + 1;
	
	while( temp ){
		if( data.array[temp->adjacent-1].range < 0 ){
			insertInLine( data.searchLine , temp->adjacent );
			data.array[temp->adjacent-1].range = range;
		}
		temp = temp->prox;
	}
	
	return;
}

void results( list data ){
	int i, rangeSeek = 0;
	
	printf("Origem da busca: %i\n", data.origin );
	printf("Vertices alcancados e distancias:\n");
	while( rangeSeek < data.vertices ){
		for( i=0 ; i<data.vertices ; ++i ){
			if( data.array[i].range == rangeSeek )
				printf("%i %i \n", (i+1), data.array[i].range );
		}
		++rangeSeek;
	}
	
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
	
	return;
}

#endif
