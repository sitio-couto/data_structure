#ifndef _TYPES
#define _TYPES

typedef struct node{
	int adjacent;
	struct node *prox;
}node;

typedef struct vector{
	int range;
	node *prox;
}vector;

typedef struct list{
	int vertices;
	int origin;
	vector *array;
	node *searchLine;
}list;

list initList( void );
void bfs( list data , int origin );
void insertInLine( node *temp , int value );
void removeFromLine( node **temp );
void results( list data );
void release( list data );

#endif
