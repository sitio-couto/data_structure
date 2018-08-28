#ifndef _TYPES
#define _TYPES

typedef struct pair{
	int key;
	int cost;
}pair;

typedef struct vectors{
	pair *heap;
	int *heapKeys;
	int usedNodes;
	int size;
}vectors;

void initialize_heap( vectors *data );
void insertPair( vectors *data , int key , int cost );
void fixOrderFromBottom( vectors *data , int child );
int exchangeData( vectors *data , int father , int child );
void removeMinimum( vectors *data );
void fixOrderFromTop( vectors *data , int father );
void decreaseCost( vectors *data , int key , int cost );

#endif
