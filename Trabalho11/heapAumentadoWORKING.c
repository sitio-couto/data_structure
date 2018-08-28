#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct pair{
	long long int key;
	long long int cost;
}pair;

typedef struct vectors{
	pair *heap;
	long long int *heapKeys;
	long long int usedNodes;
	long long int size;
}vectors;

void initialize_heap( vectors *data );
void insertPair( vectors *data , long long int key , long long int cost );
void fixOrderFromBottom( vectors *data , long long int child );
int exchangeData( vectors *data , long long int father , long long int child );
void removeMinimum( vectors *data );
void fixOrderFromTop( vectors *data , long long int father );
void decreaseCost( vectors *data , long long int key , long long int cost );
void debug( vectors *data );


int main( void ){
	char command;
	long long int key, cost, i;
	
	vectors data;
	initialize_heap( &data );
	
	while( 1 ){
		scanf(" %c", &command );
		if( command == 'i' ){
			scanf(" %lli %lli", &key, &cost );
			insertPair( &data , key , cost );
		}else if( command == 'm' ){
			removeMinimum( &data );
		}else if( command == 'd' ){
			scanf(" %lli %lli", &key, &cost );
			decreaseCost( &data , key , cost );
		}else if( command == 't' ){
			free( data.heap );
			free( data.heapKeys );
			break;
		}else if( command == '?' ){
			debug( &data );
		}
	}
	
	return 0;
}

void initialize_heap( vectors *data ){
	long long i;
	scanf(" %lli", &data->size );
	
	data->heap = malloc( sizeof( pair )*data->size );
	if( !data->heap ) return;
	data->heapKeys = malloc( sizeof( long long int )*data->size );
	if( !data->heapKeys ) return;
	for( i=0 ; i<data->size ; ++i ){ 
		data->heapKeys[i] = -1 ;
		data->heap[i].key = -1 ;
		data->heap[i].cost = 0;
	}
	data->usedNodes = 0;
	
	return;
}

void insertPair( vectors *data , long long int key , long long int cost ){
	if( data->heapKeys[key] != -1 ){ return; }
	data->heapKeys[key] = data->usedNodes;
	data->heap[data->usedNodes].cost = cost;
	data->heap[data->usedNodes].key = key;
	++data->usedNodes;
	
	fixOrderFromBottom( data , (data->usedNodes-1) );
}

void fixOrderFromBottom( vectors *data , long long int child ){
	int father;
	
	while( child != 0 ){
		if( child%2 != 0 ){
			father = (child-1)/2 ;
		}else{
			father = (child-2)/2 ;
		}
		
		if( data->heap[father].cost <= data->heap[child].cost ){ break; }
		
		child = exchangeData( data , father , child );	
	}
	
	return;
}

int exchangeData( vectors *data , long long int father , long long int child ){
	long long int temp;
	
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
		printf("minimo {%lli,%lli}\n", data->heap[0].key , data->heap[0].cost );
		data->heapKeys[data->heap[0].key] = -1;
		data->heap[0].key = data->heap[data->usedNodes-1].key ;
		data->heap[0].cost = data->heap[data->usedNodes-1].cost;
		data->heap[data->usedNodes-1].key = -1 ;
		--data->usedNodes;
		
		fixOrderFromTop( data , 0 );
	}
	
	return;
}

void fixOrderFromTop( vectors *data , long long int father ){
	long long int chosenChild;
	
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

void decreaseCost( vectors *data , long long int key , long long int cost ){
	
	data->heap[data->heapKeys[key]].cost = cost;
	fixOrderFromBottom( data , data->heapKeys[key] );
	
	return;
}

void debug( vectors *data ){
	long long int i;
	printf("\n-------------------------------------------------------\n");
	printf("Heaps info:\n Size: %i \n Used parts: %i \n", data->size, data->usedNodes);
	printf("Current elements in heap:\n " );
	for( i=0 ; i<data->usedNodes ; ++i ){
		printf("{%i;%i} ", data->heap[i].key , data->heap[i].cost );
	}
	printf("\n");
	printf("Current elements in heapKeys:\n " );
	for( i=0 ; i<data->size ; ++i ){
		if( data->heapKeys[i] != -1 ){
			printf("{%i;%i} ", i , data->heapKeys[i] );
		}
	}
	printf("\n");
	printf("Base element Key: %i", data->heap[data->usedNodes].key );
	printf("\n-------------------------------------------------------\n");
	
	return;
}



