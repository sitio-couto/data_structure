#ifndef _TYPES
#define _TYPES

typedef struct node{
	int adjacent;
	struct node *prox;
}node;

typedef struct vector{
	int value;
	int timeIn;
	int timeOut;
	node *prox;
}vector;

typedef struct list{
	int vertices;
	vector *array;
	int *marks;
}list;

list initList( void );
void dfs( list data , int *timestamp , int origin );
void seekCycle( list data );
void sortTimestamps( list data );
void release( list data );

#endif
