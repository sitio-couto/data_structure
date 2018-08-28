#ifndef _FUNCTIONS
#define _FUNCTIONS

void initialize_heap( vectors *data ){
	int i;
	scanf(" %i", &data->size );
	
	data->heap = malloc( sizeof( pair )*data->size );
	data->heapKeys = malloc( sizeof( int )*data->size );
	for( i=0 ; i<data->size ; ++i ){ 
		data->heapKeys[i] = -1 ;
		data->heap[i].key = -1 ;
		data->heap[i].cost = 0;
	}
	data->usedNodes = 0;
	
	return;
}

void insertPair( vectors *data , int key , int cost ){
	if( data->heapKeys[key] != -1 ){ return; }
	data->heapKeys[key] = data->usedNodes;
	data->heap[data->usedNodes].cost = cost;
	data->heap[data->usedNodes].key = key;
	++data->usedNodes;
	
	fixOrderFromBottom( data , (data->usedNodes-1) );
}

void fixOrderFromBottom( vectors *data , int child ){
	int father;
	
	while( child != 0 ){
		father = (child-1)/2 ;
		
		if( data->heap[father].cost <= data->heap[child].cost ){ break; }
		
		child = exchangeData( data , father , child );	
	}
	
	return;
}

int exchangeData( vectors *data , int father , int child ){
	int temp;
	
	temp = data->heap[father].cost;
	data->heap[father].cost = data->heap[child].cost;
	data->heap[child].cost = temp;
	temp = data->heapKeys[data->heap[father].key];
	data->heapKeys[data->heap[father].key] = data->heapKeys[data->heap[child].key];
	data->heapKeys[data->heap[child].key] = temp;
	temp = data->heap[father].key;
	data->heap[father].key = data->heap[child].key;
	data->heap[child].key = temp;
	
	return father;
}


void removeMinimum( vectors *data ){
	
	if( data->heap[0].key < 0 ){
		printf("vazio\n");
	}else{
		printf("minimo {%i,%i}\n", data->heap[0].key , data->heap[0].cost );
		data->heapKeys[data->heap[0].key] = -1;
		data->heap[0].key = data->heap[data->usedNodes-1].key ;
		data->heap[0].cost = data->heap[data->usedNodes-1].cost;
		data->heap[data->usedNodes-1].key = -1 ;
		--data->usedNodes;
		
		fixOrderFromTop( data , 0 );
	}
	
	return;
}

void fixOrderFromTop( vectors *data , int father ){
	int chosenChild;
	
	while( (2*father + 1) < data->usedNodes ){
		
		chosenChild = ( 2*father + 1 );
		if( (2*father + 2) < data->usedNodes ){
			if( data->heap[2*father+2].cost < data->heap[chosenChild].cost ){
				chosenChild = ( 2*father + 2 ) ;
			}
		}
		
		if( data->heap[chosenChild].cost >= data->heap[father].cost ){ break; }
		
		father = exchangeData( data , chosenChild , father );		
	}

	return;
}

void decreaseCost( vectors *data , int key , int cost ){
	
	data->heap[data->heapKeys[key]].cost = cost;
	fixOrderFromBottom( data , data->heapKeys[key] );
	
	return;
}

#endif
